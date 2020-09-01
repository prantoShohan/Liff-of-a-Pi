#pragma once
#include "liffpch.h"

#include "View.h"

namespace liff {
	class Widget : public View {
	public:
		Widget(float x, float y, float size_x, float size_y) : View(x, y, size_x, size_y, true) {}
		virtual ~Widget() = default;

		
	};
}
