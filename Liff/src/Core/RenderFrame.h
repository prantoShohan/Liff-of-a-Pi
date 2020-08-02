#pragma once
#include "liffpch.h"

#include "glm/vec2.hpp"
#include "Interfaces.h"

namespace liff {

	class RenderFrame : public EventListener, public Rectangle {
	protected:
		std::shared_ptr<RenderFrame> m_renderFrame = nullptr;
		virtual void render() = 0;

	public:
		RenderFrame(Rectangle* parent) : Rectangle::Rectangle(parent->get_position(), parent->get_size()) {}

		virtual void init() {};

		virtual void destroy() {};

		virtual void update() final {
			if (m_renderFrame) {
				m_renderFrame->update();
			}
			render();
		};

		bool on_resize(WindowResizeEvent& e) {
			set_size(glm::vec2(e.get_width(), e.get_height()));
			//std::cout << "Risizing on Renderframe level" << e.get_width() << " " << e.get_height() << std::endl;
			return true;
		}

		void on_event(liff::Event& e) override {
			EventDispatcher dispatcher(e);
			dispatcher.dispatch<WindowResizeEvent>(std::bind(&RenderFrame::on_resize, this, std::placeholders::_1));
		}
	};
	
	class LayerStack final : public RenderFrame {
	private:
		std::vector<std::shared_ptr<RenderFrame>> m_stack;
		
		void render() override {
			for (const std::shared_ptr<RenderFrame>& l : m_stack) {
				l->update();
			}
		};

	public:
		LayerStack(Rectangle* parent): RenderFrame::RenderFrame(parent) {}
		
		virtual void push_layer(const std::shared_ptr<RenderFrame>& layer) {
			m_stack.push_back(layer);
			layer->init();
		};
		
		virtual std::vector<std::shared_ptr<RenderFrame>>::iterator begin() {
			return m_stack.begin();
		}
		virtual std::vector<std::shared_ptr<RenderFrame>>::iterator end() {
			return m_stack.end();
		}


		void on_event(liff::Event& e) override {
			RenderFrame::on_event(e);
			for (const std::shared_ptr<RenderFrame>& l : m_stack) {
				l->on_event(e);
			}
			std::cout <<"On layerstack "<< get_size().x << " " << get_size().y << std::endl;
		};
	};

	class RenderFrameLayout : public RenderFrame {
		
	};

	
}
