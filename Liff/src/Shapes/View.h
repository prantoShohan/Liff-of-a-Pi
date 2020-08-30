#pragma once
#include "liffpch.h"


#include "Core/Input.h"
#include "Core/Interfaces.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include "Shapes.h"

namespace liff {
	class Behaviour {
	public:
		virtual void on_update() = 0;
	};
	
	class View: public EventListener{
	protected:
		std::shared_ptr<View> root;
		std::shared_ptr<View> parent;

		std::vector<Behaviour> behaviours = {};


		glm::vec2 position;
		glm::vec2 size;

		bool isLeaf;
		bool isRoot;

		std::string id;
		
	public:
		View(float posX, float posY, float sizeX, float sizeY, bool lf, bool rt = false): position(posX, posY), size(sizeX, sizeY), isLeaf(lf), isRoot(rt) {}
		virtual ~View() = default;

		std::shared_ptr<View> get_root() const { return root; }
		void set_root(const std::shared_ptr<View>& root) { this->root = root; }
		std::shared_ptr<View> get_parent() const { return parent; }
		void set_parent(const std::shared_ptr<View>& parent) { this->parent = parent; }
		glm::vec2 get_position() const { return position; }
		void set_position(const glm::vec2& position) { this->position = position; }
		glm::vec2 get_size() const { return size; }
		void set_size(const glm::vec2& size) { this->size = size; }

		void add_behaviour(const Behaviour& b) { behaviours.push_back(b); }

		bool collide(glm::vec2 point) const {
			if ((point.x >= position.x) && (point.y >= position.y) && (point.x <= size.x) && (point.y <= size.y)) return true;
			else return false;
		}
		
		virtual void update() { for (auto& b : behaviours) b.on_update(); on_update(); }
		virtual void on_event(liff::Event& e) override { if(!e.m_handeled) handle_event(e); }
		virtual void render() { on_render(); }


		virtual void on_update() {}
		virtual void on_render() = 0;
		virtual bool handle_event(Event& e) = 0;
		
	};

	class Widget: public View {
	public:
		Widget(float x, float y, float size_x, float size_y): View(x, y, size_x, size_y, true){}
		virtual ~Widget() = default;
	};
	
	class Layout: public View {
	protected:
		std::shared_ptr<View> child;
		
	public:
		Layout(float x, float y, float size_x, float size_y): View(x, y, size_x, size_y, false) {}
		virtual ~Layout() = default;

		void set_child(std::shared_ptr<View> c) { child = c; }
		std::shared_ptr<View> get_child() { return child; }

		virtual void update() { View::update(); child->on_update(); }
		virtual void on_event(Event& e) override { View::on_event(e); if(!e.m_handeled) child->on_event(e); }
		virtual void render() { View::render(); child->on_render(); }
	};

	class Button: public Widget {
	protected:
		liff::Rectangle shape;
		
	public:
		Button(glm::vec2 pos, glm::vec2 size, glm::vec4 color): Widget(pos.x, pos.y, size.x, size.y), shape(pos, size, color){}

		void on_render() override {
			Renderer::get().submit(DrawData(shape.get_buffer_data(), "basic"));
		};
	};
}
