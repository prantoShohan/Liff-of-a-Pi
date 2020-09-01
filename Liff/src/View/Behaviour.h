#pragma once

#include "liffpch.h"


#include "Core/Input.h"

 
namespace liff {

	class View;
	
	class Behaviour {
	public:
		virtual void on_update() {};
		virtual ~Behaviour() = default;
	};


	class FocusBehaviour: public Behaviour {
	protected:
		View *target;
		
	public:
		FocusBehaviour(View* v): target(v){}
		~FocusBehaviour() override {};

		void on_update() override;

	};

}
