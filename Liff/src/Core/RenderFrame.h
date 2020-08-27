#pragma once
#include "liffpch.h"

#include "Interfaces.h"

namespace liff {

	class RenderFrame : public EventListener {
	protected:
		std::shared_ptr<RenderFrame> m_renderFrame;
		virtual void render() = 0;

	public:
		RenderFrame() :m_renderFrame(nullptr) {}

		virtual void init() {};

		virtual void destroy() {};

		virtual void update() final {
			if (m_renderFrame) {
				m_renderFrame->update();
			}
			render();
		};

		void on_event(liff::Event& e) override {}
	};

	
	class LayerStack final : public RenderFrame {
	private:
		std::vector<std::shared_ptr<RenderFrame>> m_stack;
		
		void render() override {
			for (const std::shared_ptr<RenderFrame>& l : m_stack) {
				l->update();
			}
		};

	public:
		
		virtual void push_layer(const std::shared_ptr<RenderFrame>& layer) {
			m_stack.push_back(layer);
			layer->init();
		};
		
		virtual std::vector<std::shared_ptr<RenderFrame>>::iterator begin() {
			return m_stack.begin();
		}
		virtual std::vector<std::shared_ptr<RenderFrame>>::iterator end() {
			return m_stack.end();
		}


		void on_event(liff::Event& e) override {
			for (const std::shared_ptr<RenderFrame>& l : m_stack) {
				l->on_event(e);
			}
		};
	};

	
}
