#pragma once
#include "liffpch.h"
#include "Event.h"
#include "Interfaces.h"
#include "Window.h"

namespace liff {

	class Application : EventListener {
	private:
		std::string m_title;
		std::shared_ptr<Window> m_window;
		bool m_running;
		
	public:
		explicit Application(const std::string& cs)
			: m_title(cs), m_running(true){
		}
		virtual ~Application() = default;

		void run();
		virtual void on_start();
		virtual void on_end();
		virtual void setup();
		virtual void do_something() = 0;

		virtual std::shared_ptr<Window> set_window() = 0;

		virtual bool on_window_resize(WindowResizeEvent& e);
		virtual bool on_window_close(WindowCloseEvent& e);

		virtual void on_event(Event& e) override;
	};

	Application* create_application();
}
