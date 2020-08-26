#include <iostream>

#include "Liff.h"
#include "Rendering/VertexArray.h"

class TestLayer : public liff::RenderFrame {
private:
	bool sdw;
    unsigned int VAO;
    unsigned int shaderProgram;
    liff::VertexArray va;
public:
	void init() override {
		sdw = true;
        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout(location = 1) in vec4 aColor;\n"
            "layout(location = 2) in vec2 aTexCoord;\n"
            "layout(location = 3) in float aTexInd;\n"
            "out vec4 Color;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "	Color = aColor;"
            "}\0";
        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "in vec4 Color;"
            "void main()\n"
            "{\n"
            "   FragColor = Color;\n"
            "}\n\0";

// 		"#version 330 core\n"
// 			"out vec4 FragColor;"
// 			""
// 			"in vec4 Color;"
// 			""
// 			""
// 			"void main()"
// 			"{"
// 			"	FragColor = Color;"
// 			"}",
// 
// 
// 			"#version 330 core\n"
// 			"layout(location = 0) in vec3 aPos;"
// 			"layout(location = 1) in vec4 aColor;"
// 			"layout(location = 2) in vec2 aTexCoord;"
// 			"layout(location = 3) in float aTexInd;"
// 			""
// 			"out vec4 Color;"
// 			""
// 			"uniform mat4 model;"
// 			"uniform mat4 view;"
// 			"uniform mat4 projection;"
// 			""
// 			"void main()"
// 			"{"
// 			"	gl_Position = projection * vec4(aPos, 1.0f);"
// 			"	Color = aColor;"
// 			"}"

		
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // fragment shader
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        liff::Rectangle r({ .25, .25 }, { .75, .75 }, { .1, .2, .5, 1.0f });
        liff::Rectangle s({ -.25, -.25 }, { 0, 0 }, { .1, .1, .7, 1.0});
        auto d = r.get_buffer_data()+s.get_buffer_data();

        va = liff::VertexArray(d);

        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	};

	
	void render() override {
		if(sdw) {
			ImGui::ShowDemoWindow(&sdw);
		}

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glUseProgram(shaderProgram);
        //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        va.bind();
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
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
//         liff::Quad q(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(3.0f, 3.0f, 3.0f), glm::vec4(.5f, .2f, .1f, 1.0f));
// 		liff::Quad p(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(3.0f, 3.0f, 3.0f), glm::vec4(.5f, .2f, .1f, 1.0f));
//         liff::Quad r(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(3.0f, 3.0f, 3.0f), glm::vec4(.5f, .2f, .1f, 1.0f));
//         auto b = p.get_buffer_data() + q.get_buffer_data() + r.get_buffer_data();
        liff::Rectangle r1({ 0, 0 }, { 100, 100 }, { .5, .2, .1, 1 });
        liff::Rectangle r2({ 100, 100 }, { 200, 200 }, { .5, .2, .1, 1 });
		//std::cout << (r1.get_buffer_data()+r2.get_buffer_data()).to_string();
	}

};

liff::Application* liff::create_application() {
	return new TestApplication("Liff");
}