#pragma once
#include "Application.h"

extern liff::Application* liff::create_application();


int main() {
	auto app = liff::create_application();
	app->run();
}