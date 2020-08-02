#pragma once

#include "Event.h"

namespace liff {
	class EventListener {
	public:
		virtual ~EventListener() = default;
		virtual void on_event(liff::Event& e) = 0;
	};

	

}
