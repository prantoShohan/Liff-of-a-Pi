#pragma once
#include "liffpch.h"


#include "Behaviour.h"
#include "Core/Interfaces.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

namespace liff {

	class View: public EventListener{
	protected:
		std::shared_ptr<View> root;
		std::shared_ptr<View> parent;

		std::vector<std::shared_ptr<Behaviour>> behaviours = {};

		glm::vec2 position;
		glm::vec2 size;

		bool isLeaf;
		bool isRoot;
		bool focused = false;

		std::string id;
		
	public:
		View(float posX, float posY, float sizeX, float sizeY, bool lf, bool rt = false) : position(posX, posY), size(sizeX, sizeY), isLeaf(lf), isRoot(rt) {}
		virtual ~View() = default;

		std::shared_ptr<View> get_root() const { return root; }
		void set_root(const std::shared_ptr<View>& root) { this->root = root; }
		std::shared_ptr<View> get_parent() const { return parent; }
		void set_parent(const std::shared_ptr<View>& parent) { this->parent = parent; }
		glm::vec2 get_position() const { return position; }
		void set_position(const glm::vec2& position) { this->position = position; }
		glm::vec2 get_size() const { return size; }
		void set_size(const glm::vec2& size) { this->size = size; }

		void add_behaviour(std::shared_ptr<Behaviour> b);
		void focus(bool f) { focused = f; }

		bool collide(glm::vec2 point) const;

		virtual void update();
		virtual void on_event(liff::Event& e) override;
		virtual void render();


		virtual void on_update() {}
		virtual void on_render() = 0;
		virtual bool handle_event(Event& e) = 0;
		
	};
}
