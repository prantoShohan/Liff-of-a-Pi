#pragma once
#include "liffpch.h"
#include "Rendering/Shader.h"


namespace liff {
	
	class ShaderLibrary {
	private:
		std::unordered_map<std::string, Shader> library;
		ShaderLibrary(){}
		
	public:
		ShaderLibrary(const ShaderLibrary&) = delete;

		static ShaderLibrary& get() {
			static ShaderLibrary instance = ShaderLibrary();
			return instance;
		}
		
		void createShader(std::string name, std::string vs, std::string fs) {
			library[name] = Shader(fs, vs);
		}

		Shader& get_shader_instance(std::string name) {
			return library[name];
		}
		
	};
}
