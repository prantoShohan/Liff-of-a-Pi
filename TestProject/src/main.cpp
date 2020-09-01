#include <iostream>
#include <memory>


#include "Liff.h"
#include "Rendering/Camera.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/ShaderLibrery.h"
#include "Rendering/VertexArray.h"
#include "View/Button.h"

class TestLayer : public liff::RenderFrame {
private:
	bool sdw;
	std::shared_ptr<liff::View> root;

	
public:
	void init() override {
		sdw = true;

		liff::Renderer::get().initialize(std::make_shared<liff::Camera2d>(0, 1280, 0, 720), std::make_shared<liff::SortedDrawCallManager>());

		auto p = glm::vec2(50, 50);
		auto q = glm::vec2(200, 200);
		auto c1 = glm::vec4(.3, .1, .7, 1.0);
		auto c2 = glm::vec4(.3, .8, .1, 1.0);
		
		root = std::make_shared<liff::ButtonBasic> (p, q, c1, c2, c2);
		
        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	};

	void on_update() override {

		root->update();
		
		auto p = liff::Input::get_mouse_position();
		std::cout << p.x << " " << p.y << std::endl;

// 		liff::Renderer::get().submit(liff::DrawData(liff::Rectangle({ 0, 0 }, { 100, 100 }, { .1, .2, .5, 1.0f }).get_buffer_data(), "basic"));
// 		liff::Renderer::get().submit(liff::DrawData(liff::Rectangle({ 50, 50 }, { 200, 200 }, { .3, .1, .7, 1.0 }).get_buffer_data(), "basic"));
// 		liff::Renderer::get().submit(liff::DrawData(liff::Rectangle({ 100, 100 }, { 400, 400 }, { .1, .9, .7, 1.0 }).get_buffer_data(), "basic"));
// 		liff::Renderer::get().submit(liff::DrawData(liff::Rectangle({ 200, 200 }, { 600, 600 }, { .7, .3, .7, 1.0 }).get_buffer_data(), "basic"));
// 		liff::Renderer::get().submit(liff::DrawData(liff::Rectangle({ 500, 500 }, { 700, 700 }, { .1, .2, .5, 1.0f }).get_buffer_data(), "basic"));

	}

	
	void render() override {

		
		if(sdw) {
			ImGui::ShowDemoWindow(&sdw);
		}

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		root->render();
		
        liff::Renderer::get().render();

	};


	void on_event(liff::Event& e) override {
		root->on_event(e);
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