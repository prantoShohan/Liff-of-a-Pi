#pragma once

#include "Event.h"
#include "glm/vec2.hpp"

namespace liff {
	class EventListener {
	public:
		virtual void on_event(liff::Event& e) = 0;
	};

	class Rectangle {
	protected:
		glm::vec2 m_position;
		glm::vec2 m_size;
	public:
		Rectangle(Rectangle* rectangle) { m_position = rectangle->get_position(); m_size = rectangle->get_size(); }
		Rectangle(const glm::vec2& position, const glm::vec2& size)
			: m_position(position),m_size(size) {}

		virtual glm::vec2 get_position() const { return m_position; }
		virtual glm::vec2 get_size() const { return m_size; }


		virtual void set_position(const glm::vec2& position) { this->m_position = position; }
		virtual void set_size(const glm::vec2& size) { this->m_size = size; }
	};

	

}
