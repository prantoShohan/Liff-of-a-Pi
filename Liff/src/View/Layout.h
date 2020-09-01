#pragma once
#include "liffpch.h"

#include "View.h"

namespace liff {
	class Layout : public View {

	public:
		Layout(float x, float y, float size_x, float size_y) : View(x, y, size_x, size_y, false) {}
		virtual ~Layout() = default;
	};

	class LinearLayout: public Layout {
	private:
		std::vector<std::shared_ptr<View>> children;

	public:
		void add_child(std::shared_ptr<View> v) {
			children.push_back(v);
		}
		
		virtual void update() {
			View::update();
			for(auto v: children) {
				v->update();
			}
		}
		
		virtual void on_event(Event& e) override {
			View::on_event(e);
			for (auto v : children) {
				v->on_event(e);
			}
		}

		virtual void render() {
			View::render();
			for (auto v : children) {
				v->render();
			}
		}
		
	};
}
