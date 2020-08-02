#include "liffpch.h"
#include "Application.h"

#include <utility>

namespace liff {

	Application::Application(std::string cs, int width, int height): m_title(std::move(cs)), m_running(true), Rectangle(0, 0, width, height) { }

	void Application::init() {
		m_window = set_window();
		m_window->init();
		m_renderFrame = set_render_frame();
		m_renderFrame->init();
	}

	void Application::run() {
		on_start();
		setup();

		while(m_running) {
			m_window->begin();
			update();
			m_window->end();
		}
		do_something();

		on_end();
	}
	
	void Application::on_start() {}
	void Application::on_end() {}
	void Application::setup() {}

	void Application::update() {
		if(m_renderFrame)
			m_renderFrame->update();
	}

	bool Application::on_window_resize(WindowResizeEvent& e) {
		set_size(e.get_width(), e.get_height());
		glViewport(0, 0, e.get_width(), e.get_height());
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
		m_renderFrame->on_event(e);
	}
}
