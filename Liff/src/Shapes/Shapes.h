#pragma once
#include "liffpch.h"


#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"




namespace liff {

	class Vertex {
	private:
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 textureCoordinate;
		float textureIndex;

	public:
		Vertex(float x, float y, float z, float r, float g, float b, float a, float u = 0.0f, float v = 0.0f, float ti = 0.0f)
			:position(glm::vec3(x, y, z)), color(glm::vec4(r, g, b, a)), textureCoordinate(glm::vec2(u, v)), textureIndex(ti) {}

		std::vector<float> get_data() const {
			return { position.x, position.y, position.z,
					color.r, color.g, color.b, color.a,
					textureCoordinate.x, textureCoordinate.y,
					textureIndex };
		}

		void set_position(const glm::vec3& position) { this->position = position; }
		void set_color(const glm::vec4& color) { this->color = color; }
	};
	
	class BufferData {
	private:
		unsigned int lastIndex;
	public:
		std::vector<float> vertexBuffer;
		std::vector<unsigned int> indexBuffer;

		BufferData(){}
		
		BufferData(const std::vector<float>& vb, const std::vector<unsigned int> ib, int li = 0)
			:vertexBuffer(vb), indexBuffer(ib), lastIndex(li) {}
		
		BufferData operator + (BufferData const& data) {
			std::vector<float> vb = vertexBuffer;
			std::vector<unsigned int> ib = indexBuffer;
			vb.insert(vb.end(), data.vertexBuffer.begin(), data.vertexBuffer.end());
			std::vector<unsigned int> ind;
			for(auto i: data.indexBuffer) {
				ind.push_back(i + lastIndex+1);
			}
			ib.insert(ib.end(), ind.begin(), ind.end());
			unsigned int lastIndexForthis = *std::max_element(ind.begin(), ind.end());
			return BufferData(vb, ib, lastIndexForthis);
		}

		std::string to_string() const{
			std::string s = "VertexBuffer: \n";
			for (int i = 0; i < vertexBuffer.size(); i++) {
				if(i%10 == 0) {
					s += "\n";
				}
				s += std::to_string(vertexBuffer[i]) + ", ";
			}
			s += "\nIndexBuffer: \n";
			for (int i = 0; i < indexBuffer.size(); i++) {
				if(i%6 == 0) {
					s += "\n";
				}
				s += std::to_string(indexBuffer[i]) + ", ";
			}
			return s;
		}
		
	};

	
	class Drawable {
	public:
		virtual BufferData get_buffer_data() = 0;
		std::string string_buffer_data() {
			return get_buffer_data().to_string();
		}
	};

	class Quad: public Drawable {
	private:
		Vertex v1;
		Vertex v2;
		Vertex v3;
		Vertex v4;	
		glm::vec4 color;

	public:
		Quad(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const glm::vec4& icolor)
			:v1(p1.x, p1.y, p1.z, icolor.r, icolor.g, icolor.b, icolor.a),
			 v2(p2.x, p2.y, p2.z, icolor.r, icolor.g, icolor.b, icolor.a),
			 v3(p3.x, p3.y, p3.z, icolor.r, icolor.g, icolor.b, icolor.a),
			 v4(p4.x, p4.y, p4.z, icolor.r, icolor.g, icolor.b, icolor.a),
			 color(icolor){}
		
		BufferData get_buffer_data() override {
			auto vb1 = v1.get_data();
			auto vb2 = v2.get_data();
			auto vb3 = v3.get_data();
			auto vb4 = v4.get_data();
			vb1.insert(vb1.end(), vb2.begin(), vb2.end());
			vb1.insert(vb1.end(), vb3.begin(), vb3.end());
			vb1.insert(vb1.end(), vb4.begin(), vb4.end());
			
			return BufferData(vb1, { 0, 1, 2, 0, 2, 3 }, 3);
		}

		void set_color(glm::vec4 col) {
			color = col; v1.set_color(col);
			v1.set_color(col);
			v2.set_color(col);
			v3.set_color(col);
			v4.set_color(col);
		}
		glm::vec4 get_color() const { return color; }
	};

	class Rectangle : public Drawable {
	private:
		glm::vec2 position;
		glm::vec2 to;
		Quad quad;

	public:
		Rectangle(const glm::vec2& pos, const glm::vec2& t, const glm::vec4& c)
			:quad(glm::vec3(pos, 0.0f), glm::vec3(t.x, pos.y, 0.0f), glm::vec3(t, 0.0f), glm::vec3(pos.x, t.y, 0.0f), c), position(pos), to(t){}

		BufferData get_buffer_data() override {
			return quad.get_buffer_data();
		}

		void set_color(glm::vec4 col) { quad.set_color(col); }
		glm::vec4 get_color() const { return quad.get_color(); }
	};
}
