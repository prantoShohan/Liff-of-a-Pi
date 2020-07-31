#include "liffpch.h"
#include "Application.h"

namespace liff {
	void Application::run() {
		m_window = set_window();
		
		on_start();
		setup();

		while(m_running) {
			m_window->render();
		}
		do_something();

		on_end();
	}
	
	void Application::on_start() {}
	void Application::on_end() {}
	void Application::setup() {}

	bool Application::on_window_resize(WindowResizeEvent& e) {
		glViewport(0, 0, e.get_width(), e.get_width());
		std::cout << "window resized: " << e.get_height() << "  " << e.get_width() << std::endl;
		return  true;
	}

	bool Application::on_window_close(WindowCloseEvent& e) {
		m_running = false;
		std::cout << "Window close\n";
		return true;
	}
	
	void Application::on_event(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::on_window_resize, this, std::placeholders::_1));
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::on_window_close, this, std::placeholders::_1));
	}
}
