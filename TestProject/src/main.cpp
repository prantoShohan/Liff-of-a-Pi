#include <iostream>

#include "Liff.h"


class TestApplication: public liff::Application {

public:
	explicit TestApplication(const std::string& cs)
		: Application(cs) {}

private:
	void do_something() override {
		std::cout << "Testing the liff\n";
	}


public:
	std::shared_ptr<liff::Window> set_window() override {
		return std::make_shared<liff::GLWindow>(1280, 720, "Liff", (liff::EventListener*)this);
	}
};

liff::Application* liff::create_application() {
	return new TestApplication("Liff");
}