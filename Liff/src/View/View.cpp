#include "liffpch.h"
#include "View.h"

#include "Behaviour.h"

namespace liff {
	void View::add_behaviour(std::shared_ptr<Behaviour> b) { behaviours.push_back(b); }
	bool View::collide(glm::vec2 point) const {
		if ((point.x >= position.x) && (point.y >= position.y) && (point.x <= size.x) && (point.y <= size.y)) return true;
		else return false;
	}
	void View::update() { for (auto& b : behaviours) b->on_update(); on_update(); }
	void View::on_event(liff::Event& e) { if (!e.m_handeled) handle_event(e); }
	void View::render() { on_render(); }
}
