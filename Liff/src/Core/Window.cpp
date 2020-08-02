#include "liffpch.h"
#include "Window.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace liff {
	void GLWindow::init() {

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// glfw window creation
		// --------------------
		m_window = glfwCreateWindow(m_size.x, m_size.y, m_title.data(), NULL, NULL);
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

		glfwSwapInterval(1);
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
		
	}

	void GLWindow::destroy() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void GLWindow::begin() {
		glfwSwapBuffers(m_window);
		glfwPollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void GLWindow::end() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}
	//
	// void GLWindow::render() {
	//
	//
	// 	glfwSwapBuffers(m_window);
	// 	glfwPollEvents();
	//
	// 	//TODO: to another class
	// 	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// 	glClear(GL_COLOR_BUFFER_BIT);
	//
	// 	ImGui_ImplOpenGL3_NewFrame();
	// 	ImGui_ImplGlfw_NewFrame();
	// 	ImGui::NewFrame();
	// 	bool _show_demo_window = true;
	// 	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	// 	if (_show_demo_window)
	// 		ImGui::ShowDemoWindow(&_show_demo_window);
	//
	// 	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	// 	{
	// 		static float f = 0.0f;
	// 		static int counter = 0;
	//
	// 		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
	//
	// 		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	// 		ImGui::Checkbox("Demo Window", &_show_demo_window);      // Edit bools storing our window open/close state
	// 		//ImGui::Checkbox("Another Window", &_show_another_window);
	//
	// 		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	// 		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
	//
	// 		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	// 			counter++;
	// 		ImGui::SameLine();
	// 		ImGui::Text("counter = %d", counter);
	//
	// 		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	// 		ImGui::End();
	// 	}
	//
	// 	// Rendering
	// 	ImGui::Render();
	// 	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//
	//
	//
	// }

	void* GLWindow::get_window() {
		return m_window;
	}
}
