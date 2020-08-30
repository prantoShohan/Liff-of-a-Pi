#include <iostream>
#include <memory>


#include "Liff.h"
#include "Rendering/Camera.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/ShaderLibrery.h"
#include "Rendering/VertexArray.h"

class TestLayer : public liff::RenderFrame {
private:
	bool sdw;

	
public:
	void init() override {
		sdw = true;
        std::string vertexShaderSource = 
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout(location = 1) in vec4 aColor;\n"
            "layout(location = 2) in vec2 aTexCoord;\n"
            "layout(location = 3) in float aTexInd;\n"
            "out vec4 Color;\n"
			""
			"uniform mat4 model;"
			"uniform mat4 view;"
			"uniform mat4 projection;"
			"uniform mat4 viewProjection;"
			""
            "void main()\n"
            "{\n"
            "   gl_Position = viewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "	Color = aColor;"
            "}\0";
        std::string fragmentShaderSource = 
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "in vec4 Color;"
            "void main()\n"
            "{\n"
            "   FragColor = Color;\n"
            "}\n\0";

        liff::ShaderLibrary::get().createShader("basic", vertexShaderSource, fragmentShaderSource);
        liff::ShaderLibrary::get().createShader("bc", vertexShaderSource, fragmentShaderSource);


		liff::Renderer::get().initialize(std::make_shared<liff::PlayerCam2d>(0, 1280, 0, 720), std::make_shared<liff::SortedDrawCallManager>());

        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	};

	void on_update() override {

		auto p = liff::Input::get_mouse_position();
		std::cout << p.x << " " << p.y << std::endl;

		liff::Renderer::get().submit(liff::DrawData(liff::Rectangle({ 0, 0 }, { 100, 100 }, { .1, .2, .5, 1.0f }).get_buffer_data(), "basic"));
		liff::Renderer::get().submit(liff::DrawData(liff::Rectangle({ 50, 50 }, { 200, 200 }, { .3, .1, .7, 1.0 }).get_buffer_data(), "basic"));
		liff::Renderer::get().submit(liff::DrawData(liff::Rectangle({ 100, 100 }, { 400, 400 }, { .1, .9, .7, 1.0 }).get_buffer_data(), "basic"));
		liff::Renderer::get().submit(liff::DrawData(liff::Rectangle({ 200, 200 }, { 600, 600 }, { .7, .3, .7, 1.0 }).get_buffer_data(), "basic"));
		liff::Renderer::get().submit(liff::DrawData(liff::Rectangle({ 500, 500 }, { 700, 700 }, { .1, .2, .5, 1.0f }).get_buffer_data(), "basic"));

	}

	
	void render() override {
		if(sdw) {
			ImGui::ShowDemoWindow(&sdw);
		}

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        liff::Renderer::get().render();

	};
	
};

class TestApplication: public liff::Application {

public:
	explicit TestApplication(const std::string& cs)
		: Application(cs) {}

	std::shared_ptr<liff::Window> set_window() override {
		return std::make_shared<liff::GLWindow>(1280, 720, "Liff", (liff::EventListener*)this);
	}
	std::shared_ptr<liff::RenderFrame> set_render_frame() override {
		return std::make_shared<TestLayer>();
	};
private:
	void do_something() override {
		std::cout << "Testing the liff\n";
	}

};

liff::Application* liff::create_application() {
	return new TestApplication("Liff");
}