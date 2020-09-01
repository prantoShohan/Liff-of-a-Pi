#pragma once
#include "liffpch.h"
#include "Rendering/Shader.h"


namespace liff {
	
	class ShaderLibrary {
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> library;
		ShaderLibrary() {
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

			createShader("basic", vertexShaderSource, fragmentShaderSource);
		}
		
	public:
		ShaderLibrary(const ShaderLibrary&) = delete;

		static ShaderLibrary& get() {
			static ShaderLibrary instance = ShaderLibrary();
			return instance;
		}
		
		void createShader(std::string name, std::string vs, std::string fs) {
			library[name] = std::make_shared<Shader>(fs, vs);
		}

		std::shared_ptr<Shader> get_shader_instance(std::string name) {
			return library[name];
		}
		
	};
}
