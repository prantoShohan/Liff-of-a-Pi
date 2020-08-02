#include <iostream>

#include "Liff.h"

class TestLayer : public liff::Layer {
private:
	bool sdw;
public:
	void on_event(liff::Event& e) override{};
	void init() override {
		sdw = true;
		glClearColor(0, 256 / 128, 256 / 128, 1);
	};
	void update() override {
		if(sdw) {
			ImGui::ShowDemoWindow(&sdw);
		}
	};
	void destroy() override{};
};

class TestApplication: public liff::Application {

public:
	explicit TestApplication(const std::string& cs)
		: Application(cs) {}

	std::shared_ptr<liff::Window> set_window() override {
		return std::make_shared<liff::GLWindow>(1280, 720, "Liff", (liff::EventListener*)this);
	}
	
	void setup() override {
		m_layerStack->push_layer(std::make_shared<TestLayer>());
	};

private:
	void do_something() override {
		std::cout << "Testing the liff\n";
	}

};

liff::Application* liff::create_application() {
	return new TestApplication("Liff");
}