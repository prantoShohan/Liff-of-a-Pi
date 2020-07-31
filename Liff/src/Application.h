#pragma once
#include "liffpch.h"
#include "Event.h"

namespace liff {

	class Application {
	private:
		std::string m_title;
		
	public:
		explicit Application(const std::string& cs)
			: m_title(cs) {}
		virtual ~Application() = default;

		void run();
		virtual void on_start();
		virtual void on_end();
		virtual void setup();
		virtual void do_something() = 0;

		virtual bool on_window_resize(WindowResizeEvent& e);
		virtual bool on_window_close(WindowCloseEvent& e);

		virtual void on_event(Event& e);
	};

	Application* create_application();
}
