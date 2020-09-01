#pragma once
#include "liffpch.h"

#include "Application.h"
#include "glm/vec2.hpp"

namespace liff {
	class Input {
	public:
		static bool is_key_pressed(int key) {
			auto window = static_cast<GLFWwindow*>(Application::get()->get_window()->get_window());
			auto state = glfwGetKey(window, key);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		};
		static glm::vec2 get_mouse_position() {
			
			auto window = static_cast<GLFWwindow*>(Application::get()->get_window()->get_window());
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			return { static_cast<float>(xpos), static_cast<float>(height - ypos) };
		}
	};
}
