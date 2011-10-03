//
//  ShipBehaviour.h
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_COMPONENT_SHIP_BEHAVIOUR
#define KOCMOC_COMPONENT_SHIP_BEHAVIOUR

#include <iostream>

#include <glm/glm.hpp>

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/types/Symbol.hpp>

#include <input/WiimoteInputManager.hpp>
#include <output/MIDIOut.hpp>


namespace sputnik
{
	namespace component
	{
		class MonkeyBehaviour : public kocmoc::core::componentSystem::Component
		{
		public:
			MonkeyBehaviour(input::WiimoteInputManager* inputManager);
			void init(void);
			
		private:
			kocmoc::core::component::ObjectBehaviour* objectBehaviour;
			kocmoc::core::types::Symbol moveMonkey, bump;
			glm::vec2 movementDomainStart, movementDomainSize;
			output::MIDIOut midiOut;
			
			class InputCallback : public kocmoc::core::input::ButtonEventListener, 
									public input::WiimoteEventListener
			{
			public:
				InputCallback(MonkeyBehaviour* _p)
				: p(_p)
				{};
				
				void buttonEventCallback(kocmoc::core::types::Symbol name, 
										 kocmoc::core::input::ButtonEvent event)
				{}
				
				void wiimoteAnalogEventCallback(kocmoc::core::types::Symbol name, 
												input::WiimoteAnalogEvent event);
				
				void wiimoteButtonEventCallback(kocmoc::core::types::Symbol name, 
												input::WiimoteButtonEvent event)
				{}
				
			private:
				MonkeyBehaviour* p;
			} ic;
		};
	}
}

#endif