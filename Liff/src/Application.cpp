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
}
