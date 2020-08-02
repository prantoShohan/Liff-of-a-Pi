#pragma once
#include "liffpch.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Interfaces.h"

namespace liff {
	class Layer: public EventListener {
	public:
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void destroy() = 0;
	};


	class LayerStack {
	private:
		std::vector<std::shared_ptr<Layer>> m_stack;

	public:
		LayerStack() = default;
		virtual ~LayerStack() = default;
		
		virtual void push_layer(std::shared_ptr<Layer> layer) {
			m_stack.push_back(layer);
			layer->init();
			
		};
		virtual void update() {
			for (std::shared_ptr<Layer> l: m_stack) {
				l->update();
			}
		}
		virtual std::vector<std::shared_ptr<Layer>>::iterator begin() {
			return m_stack.begin();
		}
		virtual std::vector<std::shared_ptr<Layer>>::iterator end() {
			return m_stack.end();
		}
	};

	
}
