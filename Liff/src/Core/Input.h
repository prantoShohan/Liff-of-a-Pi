#pragma once
#include "liffpch.h"

#include "Application.h"

namespace liff {
	class Input {
	public:
		static bool is_key_pressed(int key) {
			auto window = static_cast<GLFWwindow*>(Application::get()->get_window()->get_window());
			auto state = glfwGetKey(window, key);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		};
	};
}
