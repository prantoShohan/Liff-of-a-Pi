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
};

liff::Application* liff::create_application() {
	return new TestApplication("Liff");
}