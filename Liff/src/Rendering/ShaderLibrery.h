#pragma once
#include "liffpch.h"
#include "Rendering/Shader.h"

#include <map>

namespace liff {
	
	class ShaderLibrery {
	private:
		std::map<std::string, Shader> library;
		
	public:
		void createShader(std::string name, std::string vs, std::string fs) {
			
		}
	};
}
