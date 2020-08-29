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
	private:
		BufferData data;
		VertexArray va;
		std::string shaderName;
		std::shared_ptr<Shader> shader;

		int max_quad_count = 500;
		bool prepared = false;

	public:
		DrawCall(const BufferData& d, std::string sn) : va(max_quad_count * 10), data(d), shaderName(sn), shader(ShaderLibrary::get().get_shader_instance(sn)){}
		DrawCall(const DrawData& d): va(max_quad_count*10), data(d.get_buffer_data()), shaderName(d.get_shader_name()), shader(ShaderLibrary::get().get_shader_instance(d.get_shader_name()))  {}
		BufferData get_buffer_data() const { return data; }
		std::string get_shader_name() const { return shaderName; }
		void set_data(BufferData d) { data = d; }
		void add_data(BufferData d) { data = data + d; }
		void clear_data() { data = BufferData(); }
		void prepare() { va.submit_data(data); prepared = true; }
		void bind() {
			if (!prepared) __debugbreak();
			else {
				va.bind();
				shader->bind();
			}
		}
		void camera_update(std::shared_ptr<Camera> cam) {shader->set_view_projection_matrix(cam->get_viewProjection());}
		void call() { glDrawElements(GL_TRIANGLES, data.indexBuffer.size(), GL_UNSIGNED_INT, 0); }
		
		DrawCall operator + (const DrawCall& dcall) const{
			if (shaderName == dcall.get_shader_name()) {
				return DrawCall(get_buffer_data() + dcall.get_buffer_data(), shaderName);
			}
			else {
				__debugbreak();
				return DrawCall({}, "");
			}
		}
		void add(DrawCall d) { set_data(get_buffer_data() + d.get_buffer_data()); }
	};

	class DrawCallManager {
	public:
		virtual ~DrawCallManager() = default;
		virtual void submit(const DrawData&) = 0;
		virtual void draw_all(std::shared_ptr<Camera>) = 0;
		virtual void flush() = 0;
	};

	class UnsortedDrawCallManager: public DrawCallManager {
	private:
		std::vector<DrawCall> drawCallList;
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
				drawCallList.push_back(DrawCall(lastSubmit));
				lastSubmitShaderName = d.get_shader_name();
				lastSubmit = d;
			}
		}
		void draw_all(std::shared_ptr<Camera> cam) override {
			for (auto drawCall : drawCallList) {
				drawCall.prepare();
				drawCall.bind();
				drawCall.camera_update(cam);
				drawCall.call();
			}
		}
		void flush() override {
			drawCallList = {};
			lastSubmitShaderName = "-1";
			lastSubmit = {};
		}
	};

	class SortedDrawCallManager: public DrawCallManager {
	private:
		std::map<std::string, DrawData> drawList;
		std::vector<DrawCall> drawCallList;

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
				drawCallList.push_back(DrawCall(drawdata.second));
			}
		}
		
		void draw_all(std::shared_ptr<Camera> cam) override {
			create_draw_call_list();
			for (auto drawCall : drawCallList) {
				drawCall.prepare();
				drawCall.bind();
				drawCall.camera_update(cam);
				drawCall.call();
			}
		}
		void flush() override {
			drawCallList.clear();
			drawList.clear();
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

		void begin(std::shared_ptr<Camera> cam, std::shared_ptr<DrawCallManager> dm) { drawCallManager = dm; camera = cam; }

		void end() { render(); }
		
		void submit(const DrawData& data) { drawCallManager->submit(data); }

		void render() {
			drawCallManager->draw_all(camera);
			drawCallManager->flush();
		}

		void on_event(liff::Event& e) override {
			if (camera) camera->on_event(e);
		};
	private:
		Renderer(){}
	};
}
