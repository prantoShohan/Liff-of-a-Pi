#pragma once
#include "liffpch.h"

#include "Core/Window.h"



#include "Core/Interfaces.h"
#include "Core/Event.h"
#include "glm/gtc/matrix_transform.hpp"

namespace liff {
	class Camera: public EventListener {
	public:
		virtual glm::mat4 get_view() = 0;
		virtual glm::mat4 get_projection() = 0;
		virtual glm::mat4 get_viewProjection() = 0;

		virtual void set_projection(float left, float right, float bottom, float top) = 0;
	};

	
	class Camera2d:public Camera {
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
			:projection(glm::ortho(left, right, bottom, top)), view(glm::mat4(1.0f)), viewProjection(glm::ortho(left, right, bottom, top)) {
			on_update();
		}
		
		void set_position(glm::vec3 pos) { position = pos; on_update(); }
		void set_rotation(float angle) { rotation = angle; on_update(); }

		glm::vec3 get_position() const { return position; }
		float get_rotation() const { return rotation; }

		glm::mat4 get_view() override{ return view; }
		glm::mat4 get_projection() override{ return projection; }
		glm::mat4 get_viewProjection() override{ return viewProjection; }

		void set_projection(float left, float right, float bottom, float top) override { projection = glm::ortho(left, right, bottom, top); on_update(); }

		bool on_window_resize(WindowResizeEvent& e) { set_projection(0, e.get_width(), 0, e.get_height()); return true; }
		
		void on_event(liff::Event& e) override {
			EventDispatcher dispatcher(e);
			dispatcher.dispatch<WindowResizeEvent>(std::bind(&Camera2d::on_window_resize, this, std::placeholders::_1));
		}
	};

	class PlayerCam2d : public Camera {
	private:
		Camera2d camera;
		glm::vec2 velocity = { 5.0f, 5.0f };

		void move_right() { camera.set_position(glm::vec3(camera.get_position().x + velocity.x, camera.get_position().y, camera.get_position().z)); };
		void move_left() { camera.set_position(glm::vec3(camera.get_position().x - velocity.x, camera.get_position().y, camera.get_position().z)); };;
		void move_up() { camera.set_position(glm::vec3(camera.get_position().x, camera.get_position().y + velocity.y, camera.get_position().z)); };;
		void move_down() { camera.set_position(glm::vec3(camera.get_position().x, camera.get_position().y - velocity.y, camera.get_position().z)); };

		bool on_key_pressed(KeyPressedEvent& e) {
			if(e.get_key() == GLFW_KEY_W) {
				move_up();
			}
			else if (e.get_key() == GLFW_KEY_S) {
				move_down();
			}
			else if (e.get_key() == GLFW_KEY_A) {
				move_left();
			}
			else if (e.get_key() == GLFW_KEY_D) {
				move_right();
			}
			return true;
		}
		
	public:
		PlayerCam2d(float left, float right, float bottom, float top)
			:camera(left, right, bottom, top){}
		
		void on_event(liff::Event& e) override {
			EventDispatcher dispatcher(e);
			dispatcher.dispatch<KeyPressedEvent>(std::bind(&PlayerCam2d::on_key_pressed, this, std::placeholders::_1));
			camera.on_event(e);
		};
		
		glm::mat4 get_view() override { return camera.get_view(); }
		glm::mat4 get_projection() override { return camera.get_projection(); }
		glm::mat4 get_viewProjection() override { return camera.get_viewProjection(); }
		void set_projection(float left, float right, float bottom, float top) override { return camera.set_projection(left, right, bottom, top); }
	};

}
