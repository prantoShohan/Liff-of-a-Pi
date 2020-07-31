#pragma once
#include "Application.h"

extern liff::Application* liff::create_application();


int main() {
	auto app = liff::create_application();
	app->run();
	app->on_event(liff::WindowResizeEvent(1280, 720));
	app->on_event(liff::WindowCloseEvent());
}