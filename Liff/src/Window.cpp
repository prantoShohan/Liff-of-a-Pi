#include "liffpch.h"
#include "Window.h"

namespace liff {
	void GLWindow::init() {

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// glfw window creation
		// --------------------
		m_window = glfwCreateWindow(m_width, m_height, m_title.data(), NULL, NULL);
		if (m_window == NULL){
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			__debugbreak();
		}
		glfwMakeContextCurrent(m_window);

		glfwSetWindowUserPointer(m_window, m_eventListener);
		glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height){

			auto e = WindowResizeEvent(width, height);
			EventListener* listener = (EventListener*)glfwGetWindowUserPointer(window);
			listener->on_event(e);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window){
			auto e = WindowCloseEvent();
			EventListener* listener = (EventListener*)glfwGetWindowUserPointer(window);
			listener->on_event(e);
		});
		
		//TODO: this should be in another class
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
			std::cout << "Failed to initialize GLAD" << std::endl;
			__debugbreak();
		}
		
	}

	void GLWindow::destroy() {
		glfwTerminate();
	}

	void GLWindow::render() {

		//TODO: to another class
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	void* GLWindow::get_window() {
		return m_window;
	}
}
