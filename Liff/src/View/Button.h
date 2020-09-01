#pragma once
#include "liffpch.h"


#include "Behaviour.h"
#include "Core/Event.h"
#include "glm/vec4.hpp"
#include "Rendering/Renderer.h"
#include "Widget.h"

namespace liff {

	class ButtonBasic : public Widget {
	protected:
		Rectangle shape;
		glm::vec4 baseColor;
		glm::vec4 focusColor;
		glm::vec4 clickColor;
		
	public:
		ButtonBasic(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, const glm::vec4& focColor, const glm::vec4& clkColor) :baseColor(color), focusColor(focColor), clickColor(clkColor), Widget(pos.x, pos.y, size.x, size.y), shape(pos, size, color) {
			add_behaviour(std::make_shared<FocusBehaviour>(this));
		}

		void on_render() override {
			auto d = DrawData(shape.get_buffer_data(), "basic");
			Renderer::get().submit(d);
		};


		void on_update() override {
			if (focused) {
				this->set_color(focusColor);
			}
			else {
				this->set_color(baseColor);
			}
		}
		
		void set_color(glm::vec4 c) { shape.set_color(c); }
		glm::vec4 get_color() { return shape.get_color(); }

		bool handle_event(Event& e) override { return false; }
	};
}
