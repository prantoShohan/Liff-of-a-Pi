#include "liffpch.h"
#include "Application.h"

namespace liff {
	void Application::run() {
		on_start();
		setup();
		do_something();

		on_end();
	}
	void Application::on_start() {}
	void Application::on_end() {}
	void Application::setup() {}

	bool Application::on_window_resize(WindowResizeEvent& e) {
		std::cout << "window resized: " << e.get_height() << "  " << e.get_width() << std::endl;
		return  true;
	}

	bool Application::on_window_close(WindowCloseEvent& e) {
		std::cout << "Window close\n";
		return true;
	}
	
	void Application::on_event(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::on_window_resize, this, std::placeholders::_1));
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::on_window_close, this, std::placeholders::_1));
	}
}
