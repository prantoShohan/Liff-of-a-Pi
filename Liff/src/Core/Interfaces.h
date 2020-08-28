#pragma once

#include "Event.h"

namespace liff {
	class EventListener {
	public:
		virtual void on_event(liff::Event& e) = 0;
	};

	

}
