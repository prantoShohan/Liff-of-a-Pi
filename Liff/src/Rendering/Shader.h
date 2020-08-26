#pragma once
#include "liffpch.h"

#include <glad/glad.h>



#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x2.hpp"

namespace liff {
	class Shader
	{
	private:
		unsigned int rendererId;

		std::string fragmentShader;
		std::string vertexShader;
		std::unordered_map<std::string, unsigned int> uniforms;

		bool bound = false;

	public:
		Shader() = default;
		Shader(std::string fragment_shader, std::string vertex_shader)
			:fragmentShader(fragment_shader), vertexShader(vertex_shader) {
			rendererId = create_shader();
		}

		void bind() {
			if (!bound) {
				glUseProgram(rendererId);
				bound = true;
			}
		}
		void unbind() {
			if (bound) {
				glUseProgram(0);
				bound = false;
			}
		}

		void set_model_matrix(glm::mat4 model) {
			glUniformMatrix4fv(uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));
		}
		
		void set_view_matrix(glm::mat4 view) {
			glUniformMatrix4fv(uniform_location("view"), 1, GL_FALSE, glm::value_ptr(view));
		};
		
		void set_projection_matrix(glm::mat4 projection) {
			glUniformMatrix4fv(uniform_location("projection"), 1, GL_FALSE, glm::value_ptr(projection));
		};

		int uniform_location(std::string name) {
			if (uniforms.find(name) != uniforms.end())
			{
				return uniforms[name];
			}
			else
			{
				unsigned int location = get_uniform_location(rendererId, name);
				uniforms[name] = location;
				return location;
			}
		};

	private:
		unsigned int create_shader() {
			unsigned int program = glCreateProgram();
			unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
			unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);

			glAttachShader(program, vs);
			glAttachShader(program, fs);
			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vs);
			glDeleteShader(fs);

			return program;
		}

		unsigned int compile_shader(unsigned type, const std::string& source) {
			//main code
			unsigned int id = glCreateShader(type);
			const char* src = source.c_str();
			glShaderSource(id, 1, &src, NULL);
			glCompileShader(id);

			//error checking
			int result;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				int length;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)alloca(length * sizeof(char));
				glGetShaderInfoLog(id, length, &length, message);
				std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << message << std::endl;
				__debugbreak();
				return 0;

			}

			return id;
		}

		unsigned get_uniform_location(unsigned shaderId, std::string name) {
			int location = glGetUniformLocation(shaderId, name.c_str());
			if (location == -1)
			{
				std::cout << "UNIFORM NOT FOUND\n";
				__debugbreak();
			}
			return location;
		}

		
	};

}
