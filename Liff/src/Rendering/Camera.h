#pragma once
#include "liffpch.h"


#include "Core/Interfaces.h"
#include "Core/Event.h"
#include "glm/gtc/matrix_transform.hpp"

namespace liff {
	class Camera {
	public:
		virtual glm::mat4 get_view() = 0;
		virtual glm::mat4 get_projection() = 0;
		virtual glm::mat4 get_viewProjection() = 0;

		virtual void set_projection(float left, float right, float bottom, float top) = 0;
	};

	
	class Camera2d:public Camera, public EventListener {
	private:
		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 viewProjection;

		glm::vec3 position = {0.0f, 0.0f, 0.0f};
		float rotation = 0;

		void on_update() {
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));

			view = glm::inverse(transform);
			viewProjection = projection * view;
		}
	public:
		Camera2d(float left, float right, float bottom, float top)
			:projection(glm::ortho(left, right, bottom, top)) {
			on_update();
		}
		
		void set_position(glm::vec3 pos) { position = pos; on_update(); }
		void set_rotation(float angle) { rotation = angle; on_update(); }

		glm::vec3 get_postion() { return position; }
		float get_rotation() { return rotation; }

		glm::mat4 get_view() override{ return view; }
		glm::mat4 get_projection() override{ return projection; }
		glm::mat4 get_viewProjection() override{ return viewProjection; }

		void set_projection(float left, float right, float bottom, float top) override { projection = glm::ortho(left, right, bottom, top); on_update(); }

		void on_event(liff::Event& e) override {};
	};

}
