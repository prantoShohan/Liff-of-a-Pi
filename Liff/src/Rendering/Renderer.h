﻿#pragma once
#include "liffpch.h"

#include <map>



#include "Camera.h"
#include "ShaderLibrery.h"
#include "Shapes/Shapes.h"
#include "VertexArray.h"

namespace liff {
	
	class DrawCall {
	public:
		BufferData buffer;
		std::string shaderName;

		DrawCall(){}
		DrawCall(BufferData data, std::string shader)
			:buffer(data), shaderName(shader){}

		DrawCall operator + (const DrawCall& data) {
			if(shaderName == data.shaderName) {
				return DrawCall(buffer + data.buffer, shaderName);
			}else {
				__debugbreak();
			}
		}
	};

	
	class Renderer: public EventListener {
	private:
		std::map<std::string, DrawCall> drawList;
		std::shared_ptr<Camera> camera;
		
	public:
		Renderer(const Renderer&) = delete;
		static Renderer& get() {
			static Renderer renderer_instance = Renderer();
			return renderer_instance;
		}

		void submit(const DrawCall& data) {
			if(drawList.find(data.shaderName) == drawList.end()) {
				//drawList[data.shaderName] = data;
				drawList.insert({ data.shaderName, data });
			}
			else {
				drawList[data.shaderName] = drawList[data.shaderName] + data;
			}
		}

		void render() {
			for (auto const& drawCall : drawList) {
				ShaderLibrary::get().get_shader_instance(drawCall.first).bind();
				//TODO note glm::ortho must take float value. int gets wrong results
				ShaderLibrary::get().get_shader_instance(drawCall.first).set_view_projection_matrix(camera->get_viewProjection());
				auto vao = VertexArray(drawCall.second.buffer);
				vao.bind();
				int size = drawCall.second.buffer.indexBuffer.size();
				glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
				vao.deleteVAO();
			}
			//drawList.clear();
		}

		void set_camera(std::shared_ptr<Camera> cam) {
			camera = cam;
		}

		void on_event(liff::Event& e) override {
			camera->on_event(e);
		};
	private:
		Renderer(){}
	};
}
