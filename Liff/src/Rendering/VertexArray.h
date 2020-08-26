#pragma once
#include "liffpch.h"

#include <glad/glad.h>

#include "Shapes/Shapes.h"

namespace liff {
	class BufferData;

	class VertexArray {
	private:
		unsigned int rendererID;
		unsigned int vbo;
		unsigned int ebo;
		
	public:
		VertexArray() {}
		VertexArray(const BufferData& data) {
			glGenVertexArrays(1, &rendererID);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);
			
			glBindVertexArray(rendererID);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.vertexBuffer.size(), data.vertexBuffer.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.indexBuffer.size(), data.indexBuffer.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)12);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)28);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)36);
			glEnableVertexAttribArray(3);

			//TODO delete buffer
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			//TODO unbind index buffer
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			//std::cout << data.to_string()<<std::endl<<rendererID<< std::endl;
			
		}

		void bind() {
			glBindVertexArray(rendererID);
		}
	};
}
