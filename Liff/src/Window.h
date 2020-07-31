#pragma once
#include "liffpch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Interfaces.h"

namespace liff {
	class Window {
	protected:
		int m_height;
		int m_width;
		std::string m_title;
		
	public:
		Window(int width, int height, std::string title): m_height(height), m_width(width), m_title(title){}
		virtual ~Window() = default;
		
		virtual void init() = 0;
		virtual void destroy() = 0;

		virtual void render() = 0;

		virtual void* get_window() = 0;
		
	};



	class GLWindow:public Window {
	private:
		GLFWwindow* m_window;
		EventListener* m_eventListener;

	public:
		GLWindow(int width, int height, const std::string& title, EventListener* listener)
			: Window(width, height, title), m_eventListener(listener) {
			init();
		}

		~GLWindow() override {}
		void init() override;
		void destroy() override;
		void render() override;


		void* get_window() override;
	};
}


