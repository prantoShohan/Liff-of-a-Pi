#pragma once
#include "liffpch.h"



namespace liff {
	enum class EventType {
		None = 0,
		WindowResizeEvent, WindowCloseEvent,
		KeyPressedEvent
	};

	enum EventCategory {
		None = 0,
		WindowEventCategory = 1 << 0,
		KeyEventCategory = 1 << 1
	};
	
	class Event {
	public:
		virtual ~Event() = default;
		bool m_handeled = false;

		virtual EventType get_type() = 0;
		virtual EventCategory get_category() = 0;
		virtual bool in_category(EventCategory category) { return category && get_category(); };
	};

	class EventDispatcher {
	private:
		Event& m_event;
		
	public:
		explicit EventDispatcher(Event& event)
			: m_event(event) {}

		template <class T>
		bool dispatch(std::function<bool(T&)> func) {
			if(m_event.get_type() == T::get_static_type()) {
				m_event.m_handeled = func(static_cast<T&>(m_event));
				return true;
			}
			return false;
		}
	};

	class WindowResizeEvent: public Event {
	private:
		int m_width;
		int m_height;

	public:

		WindowResizeEvent(int width, int height)
			: m_width(width),
			  m_height(height) {}

		EventType get_type() override { return EventType::WindowResizeEvent; };
		EventCategory get_category() override { return EventCategory::WindowEventCategory; };
		static EventType get_static_type() { return EventType::WindowResizeEvent; }


		int get_width() const { return m_width; }
		int get_height() const { return m_height; }
	};

	class WindowCloseEvent : public Event {
	public:
		EventType get_type() override { return EventType::WindowCloseEvent; };
		EventCategory get_category() override { return EventCategory::WindowEventCategory; };
		static EventType get_static_type() { return EventType::WindowCloseEvent; }
	};

	class KeyPressedEvent: public Event {
		int key;

	public:
		KeyPressedEvent(int k): key(k){}
		
		EventType get_type() override { return EventType::KeyPressedEvent; }
		EventCategory get_category() override { return EventCategory::KeyEventCategory; }
		static EventType get_static_type() { return EventType::KeyPressedEvent; }

		int get_key() { return key; };
	};
}
