#pragma once
#include "liffpch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <utility>


#include "Interfaces.h"

namespace liff {
	class Window : public Rectangle{
	protected:
		int m_height;
		int m_width;
		std::string m_title;
		
	public:
		Window(Rectangle* rectangle,const std::string& title): Rectangle(rectangle), m_title(std::move(title)){}
		
		virtual void init() = 0;
		virtual void destroy() = 0;

		virtual void begin() = 0;
		virtual void end() = 0;

		virtual void* get_window() = 0;
		
	};



	class GLWindow:public Window {
	private:
		GLFWwindow* m_window;
		EventListener* m_eventListener;
		ImGuiIO io;

	public:
		GLWindow(Rectangle* rectangle, EventListener* listener, const std::string& title)
			: Window(rectangle, title), m_eventListener(listener) {}
		
		void init() override;
		void destroy() override;


		void begin() override;
		void end() override;

		
		void* get_window() override;
	};
}


