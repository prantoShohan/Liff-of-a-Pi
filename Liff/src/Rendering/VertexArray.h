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

		int indexSize;

	public:
		VertexArray() {}
		VertexArray(int quadNumber) {
			indexSize = quadNumber*6;
			glGenVertexArrays(1, &rendererID);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);

			glBindVertexArray(rendererID);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * quadNumber * 4 * 10, nullptr, GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexSize, nullptr, GL_DYNAMIC_DRAW);

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
		}
		VertexArray(const BufferData& data) {
			indexSize = data.indexBuffer.size();
			glGenVertexArrays(1, &rendererID);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);

			glBindVertexArray(rendererID);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.vertexBuffer.size(), data.vertexBuffer.data(), GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.indexBuffer.size(), data.indexBuffer.data(), GL_DYNAMIC_DRAW);

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

		void submit_data(const BufferData& data) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, data.vertexBuffer.size()*sizeof(float), data.vertexBuffer.data());

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data.indexBuffer.size() * sizeof(unsigned int), data.indexBuffer.data());
		}

		void bind() {
			glBindVertexArray(rendererID);
		}

		void deleteVAO() {
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ebo);
			glDeleteVertexArrays(1, &rendererID);

		}

		int get_size() { return indexSize; }
	};
}
