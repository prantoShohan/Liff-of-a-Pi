#pragma once
#include "liffpch.h"

#include "glm/vec2.hpp"
#include "Interfaces.h"

namespace liff {

	class RenderFrame : public EventListener, public Rectangle {
	protected:
		std::shared_ptr<RenderFrame> m_child = nullptr;
		virtual void render() = 0;
		Rectangle* m_parent;

	public:
		RenderFrame(Rectangle* parent) :m_parent(parent), Rectangle::Rectangle(parent) {}

		virtual void init() {};

		virtual void destroy() {};

		virtual void update() final {
			if (m_child) {
				m_child->update();
			}
			render();
		};

		void set_parent(Rectangle* parent) {
			m_parent = parent;
			this->copy_rectangle(parent);
		}

		bool on_resize(WindowResizeEvent& e) {
			this->copy_rectangle(m_parent);
			std::cout << "Renderframe level: Position: " << this->m_pos_x << " " << this->m_pos_y << " Size: " << this->m_size_x << " " << this->m_size_y << std::endl;
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
		
		void push_layer(const std::shared_ptr<RenderFrame>& layer) {
			layer->set_parent(this);
			m_stack.push_back(layer);
			layer->init();
		};
		
		std::vector<std::shared_ptr<RenderFrame>>::iterator begin() {
			return m_stack.begin();
		}
		std::vector<std::shared_ptr<RenderFrame>>::iterator end() {
			return m_stack.end();
		}


		void on_event(liff::Event& e) override {
			RenderFrame::on_event(e);
			for (const std::shared_ptr<RenderFrame>& l : m_stack) {
				l->on_event(e);
			}
			std::cout << "LayerStack level: Position: " << this->m_pos_x << " " << this->m_pos_y << " Size: " << this->m_size_x << " " << this->m_size_y << std::endl;
		};
	};

	class RenderFrameLayout : public RenderFrame {
	private:
		float m_ratio;
		std::shared_ptr<RenderFrame> m_frame1;
		std::shared_ptr<RenderFrame> m_frame2;
		bool m_vertical = true;

		Rectangle m_rect1;
		Rectangle m_rect2;
		
		
	public:
		RenderFrameLayout(Rectangle* parent, const std::shared_ptr<RenderFrame>& render_frame1,
		                  const std::shared_ptr<RenderFrame>& render_frame2, float ratio, bool vertical)
			: RenderFrame(parent),
			  m_frame1(render_frame1),
			  m_frame2(render_frame2),
			  m_ratio(ratio),
			  m_vertical(vertical),
			  m_rect1(0, 0, 100, 100),
			  m_rect2(0, 100, 100, 200){
			
			//TODO: check ratio if it is greater than 1
			adjust_rect();
			
			m_frame1->set_parent(&m_rect1);
			m_frame2->set_parent(&m_rect2);

			m_frame1->init();
			m_frame2->init();

		}

		void on_event(liff::Event& e) override {
			RenderFrame::on_event(e);
			EventDispatcher dispatcher(e);
			dispatcher.dispatch<WindowResizeEvent>(std::bind(&RenderFrameLayout::on_resize, this, std::placeholders::_1));
			m_frame1->on_event(e);
			m_frame2->on_event(e);
		};
		
		void render() override {
			m_frame1->update();
			m_frame2->update();
		};
		
	private:
		bool on_resize(Event& e) {
			adjust_rect();
			return true;
		}

		void adjust_rect() {

			if (m_vertical) {

				int x_offset = (this->get_size_x() - this->get_pos_x()) * m_ratio;
				
				m_rect1.set_position(this->get_pos_x(), this->get_pos_y());
				m_rect1.set_size(x_offset, this->get_size_y());

				m_rect2.set_position(x_offset, this->get_pos_y());
				m_rect2.set_size(this->get_size_x(), this->get_size_y());
			}
			else {
				int y_offset = (this->get_size_y() - this->get_pos_y()) / 2;
				
				m_rect1.set_position(this->get_pos_x(), this->get_pos_y());
				m_rect1.set_size(this->get_size_x(), y_offset);

				m_rect2.set_position(this->get_pos_x(), y_offset);
				m_rect2.set_size(this->get_size_x(), this->get_size_y());
			}
		}

	};

	
}
