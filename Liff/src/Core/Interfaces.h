#pragma once

#include "Event.h"
#include "glm/vec2.hpp"

namespace liff {
	class EventListener {
	public:
		virtual ~EventListener() = default;
		virtual void on_event(liff::Event& e) = 0;
	};

	class Rectangle {
	protected:
		int m_pos_x;
		int m_pos_y;

		int m_size_x;
		int m_size_y;
		
	public:
		Rectangle();;
		Rectangle(Rectangle* rectangle):m_pos_x(rectangle->get_pos_x()), m_pos_y(rectangle->get_pos_y()), m_size_x(rectangle->get_size_x()), m_size_y(rectangle->get_size_y()) {}
		Rectangle(int pos_x, int pos_y, int size_x, int size_y)
			: m_pos_x(pos_x), m_pos_y(pos_y), m_size_x(size_x), m_size_y(size_y){}

		int get_pos_x() const { return m_pos_x; }
		int get_pos_y() const { return m_pos_y; }
		int get_size_x() const { return m_size_x; }
		int get_size_y() const { return m_size_y; }

		void copy_rectangle(Rectangle* rectangle) {
			m_pos_x = rectangle->get_pos_x();
			m_pos_y = rectangle->get_pos_y();
					   
			m_size_x = rectangle->get_size_x();
			m_size_y = rectangle->get_size_y();
		}


		void set_position(int x, int y) { m_pos_x = x; m_pos_y = y; }
		void set_size(int x, int y) { m_size_x = x; m_size_y = y; }
	};

	

}
