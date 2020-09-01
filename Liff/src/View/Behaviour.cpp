#include "liffpch.h"
#include "Behaviour.h"
#include "View.h"

namespace liff {
	void FocusBehaviour::on_update() {
		auto v = target->collide(Input::get_mouse_position());
		
		if (v) {
			target->focus(true);

		}
		else {
			target->focus(false);
			std::cout << "focus " << v << std::endl;
		}
	}
}
