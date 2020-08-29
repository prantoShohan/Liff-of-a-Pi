#pragma once
#include "liffpch.h"
#include "Rendering/Shader.h"


namespace liff {
	
	class ShaderLibrary {
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> library;
		ShaderLibrary(){}
		
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
