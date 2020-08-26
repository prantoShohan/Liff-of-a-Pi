#include <iostream>

#include "Liff.h"
#include "Rendering/Shader.h"
#include "Rendering/VertexArray.h"

class TestLayer : public liff::RenderFrame {
private:
	bool sdw;
    unsigned int VAO;
    unsigned int shaderProgram;
    liff::VertexArray va;
    liff::Shader shader;
	
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
			""
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
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

        shader = liff::Shader(fragmentShaderSource, vertexShaderSource);

        liff::Rectangle r({ .25, .25 }, { .75, .75 }, { .1, .2, .5, 1.0f });
        liff::Rectangle s({ -.25, -.25 }, { 0, 0 }, { .1, .1, .7, 1.0});
        liff::Rectangle t({ -.75, -.75 }, { -.25, -.25 }, { .1, .1, .7, 1.0 });
        auto d = r.get_buffer_data()+s.get_buffer_data()+t.get_buffer_data();

        std::cout << d.to_string();

        va = liff::VertexArray(d);

        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	};

	
	void render() override {
		if(sdw) {
			ImGui::ShowDemoWindow(&sdw);
		}

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shader.bind();
        va.bind();
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
	};
	void destroy() override{};
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
        liff::Rectangle r1({ 0, 0 }, { 100, 100 }, { .5, .2, .1, 1 });
        liff::Rectangle r2({ 100, 100 }, { 200, 200 }, { .5, .2, .1, 1 });
		//std::cout << (r1.get_buffer_data()+r2.get_buffer_data()).to_string();
	}

};

liff::Application* liff::create_application() {
	return new TestApplication("Liff");
}