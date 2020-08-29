#pragma once
#include "liffpch.h"

#include <map>



#include "Camera.h"
#include "ShaderLibrery.h"
#include "Shapes/Shapes.h"
#include "VertexArray.h"

namespace liff {
	
	class DrawData {
	public:
		BufferData data;
		std::string shaderName;

		~DrawData() = default;
		DrawData(){}
		DrawData(BufferData d, std::string shader)
			:data(d), shaderName(shader){}

		BufferData get_buffer_data() const { return data; }
		std::string get_shader_name() const { return shaderName; }
		void set_data(BufferData d) { data = d; }
		void add(DrawData d) { set_data(get_buffer_data() + d.get_buffer_data()); }
		DrawData operator + (const DrawData& d) {
			if(shaderName == d.shaderName) {
				return DrawData(data + d.data, shaderName);
			}else {
				__debugbreak();
			}
		}
	};

	class DrawCall {
	public:
		int max_quad_count = 500;
		bool prepared = false;

		BufferData data;
		VertexArray va;
		std::string shaderName;
		std::shared_ptr<Shader> shader;

	public:
		
		~DrawCall() = default;
		DrawCall() { std::cout << "created fuvk" << std::endl; }
		DrawCall(std::string sn) : va(max_quad_count * 10), shaderName(sn), shader(ShaderLibrary::get().get_shader_instance(sn)) { std::cout << "created fuvk" << std::endl; }
		DrawCall(const BufferData& d, std::string sn) : va(max_quad_count * 10), data(d), shaderName(sn), shader(ShaderLibrary::get().get_shader_instance(sn)){ std::cout << "created fuvk" << std::endl; }
		DrawCall(const DrawData& d): va(max_quad_count*10), data(d.get_buffer_data()), shaderName(d.get_shader_name()), shader(ShaderLibrary::get().get_shader_instance(d.get_shader_name()))  { std::cout << "created fuvk" << std::endl; }
		BufferData get_buffer_data() const { return data; }
		std::string get_shader_name() const { return shaderName; }
		void set_data(DrawData d) { data = d.get_buffer_data(); }
		void add_data(DrawData d) { data = data + d.get_buffer_data(); }
		void clear_data() { data = BufferData(); }
		void prepare() { va.bind(); va.submit_data(data); prepared = true; }
		void bind() {
			if (!prepared) __debugbreak();
			else {
				va.bind();
				shader->bind();
			}
		}
		void camera_update(std::shared_ptr<Camera> cam) {shader->set_view_projection_matrix(cam->get_viewProjection());}
		void call() { glDrawElements(GL_TRIANGLES, data.indexBuffer.size(), GL_UNSIGNED_INT, 0); }
	};

	class DrawCallManager {
	public:
		virtual ~DrawCallManager() = default;
		virtual void submit(const DrawData& d) = 0;
		virtual void draw_all(std::shared_ptr<Camera>) = 0;
		virtual void flush() = 0;
	};

	class UnsortedDrawCallManager: public DrawCallManager {
	private:
		std::map<std::string, DrawCall> drawCallList;
		std::string lastSubmitShaderName = "-1";
		DrawData lastSubmit;
	public:
		void submit(const DrawData& d) override {
			if(lastSubmitShaderName == "-1") {
				lastSubmitShaderName = d.get_shader_name();
				lastSubmit = d;
				return;
			}
			if(lastSubmitShaderName == d.get_shader_name()) {
				lastSubmit = lastSubmit + d;
			}
			else {
				if(drawCallList.find(d.get_shader_name()) == drawCallList.end()) {
					drawCallList[d.get_shader_name()]=DrawCall(lastSubmit);
				}else {
					drawCallList[d.get_shader_name()].add_data(d);
				}

				lastSubmitShaderName = d.get_shader_name();
				lastSubmit = d;
			}
		}
		void draw_all(std::shared_ptr<Camera> cam) override {
			if (drawCallList.find(lastSubmit.get_shader_name()) == drawCallList.end()) {
				drawCallList[lastSubmit.get_shader_name()] = DrawCall(lastSubmit);
			}
			else {
				drawCallList[lastSubmit.get_shader_name()].add_data(lastSubmit);
			}
			for (auto& drawCall : drawCallList) {
				drawCall.second.prepare();
				drawCall.second.bind();
				drawCall.second.camera_update(cam);
				drawCall.second.call();
			}
		}
		void flush() override {
			//drawCallList = {};
			lastSubmitShaderName = "-1";
			lastSubmit = {};
		}
	};

	class SortedDrawCallManager: public DrawCallManager {
	private:
		std::map<std::string, DrawData> drawList;
		std::map<std::string, DrawCall> drawCallList;

	public:
		void submit(const DrawData& data) override {
			if (drawList.find(data.get_shader_name()) == drawList.end()) {
				//drawList[data.shaderName] = data;
				drawList.insert({ data.get_shader_name(), data });
			}
			else {
				drawList[data.get_shader_name()].add(data);
			}
		}

		void create_draw_call_list() {
			for (auto drawdata : drawList) {
				if (drawCallList.find(drawdata.second.get_shader_name()) == drawCallList.end()) {
					drawCallList[drawdata.second.get_shader_name()] = DrawCall(drawdata.second);
				}
				else {
					drawCallList[drawdata.second.get_shader_name()].add_data(drawdata.second);
				}
			}
		}
		void draw_all(std::shared_ptr<Camera> cam) override {
			create_draw_call_list();
			for (auto& drawCall : drawCallList) {
				drawCall.second.prepare();
				drawCall.second.bind();
				drawCall.second.camera_update(cam);
				drawCall.second.call();
			}
		}
		void flush() override {
			drawList = {};
		}
	};
	
	class Renderer: public EventListener {
	private:
		std::shared_ptr<DrawCallManager> drawCallManager;
		std::shared_ptr<Camera> camera;
		
	public:
		Renderer(const Renderer&) = delete;
		static Renderer& get() {
			static Renderer renderer_instance = Renderer();
			return renderer_instance;
		}

		void initialize(std::shared_ptr<Camera> cam, std::shared_ptr<DrawCallManager> dm) { drawCallManager = dm; camera = cam; }

		void end() {}
		
		void submit(const DrawData& data) { drawCallManager->submit(data); }

		void render() {
			drawCallManager->draw_all(camera);
			drawCallManager->flush();
		}

		void on_event(liff::Event& e) override {
			camera->on_event(e);
		};
	private:
		Renderer(){}
	};
}
