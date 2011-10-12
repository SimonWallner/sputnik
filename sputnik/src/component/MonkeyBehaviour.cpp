//
//  ShipBehaviour.cpp
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "MonkeyBehaviour.hpp"

using namespace sputnik::component;
using kocmoc::core::component::ObjectBehaviour;
using kocmoc::core::types::symbolize;
using kocmoc::core::types::Symbol;

using sputnik::input::WiimoteAnalogEvent;

using glm::vec2;
using glm::vec3;

MonkeyBehaviour::MonkeyBehaviour(input::WiimoteInputManager* inputManager)
	: moveMonkey(symbolize("move-monkey"))
	, bump(symbolize("bump-monkey"))
	, movementDomainStart(vec2(-3.0f, -3.0f))
	, movementDomainSize(vec2(6.0f, 6.0f))
	, ic(this)
{
	inputManager->registerWiimoteEventListener(moveMonkey, &ic);
	inputManager->registerWiimoteEventListener(bump, &ic);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_CURSOR_RELATIVE_X_Y, moveMonkey);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_BUTTON_A_HELD, bump);
}

void MonkeyBehaviour::init()
{
	objectBehaviour = parent->getComponent<ObjectBehaviour>();
}

void MonkeyBehaviour::InputCallback::wiimoteAnalogEventCallback(Symbol name, WiimoteAnalogEvent event)
{
	if (name == p->moveMonkey)
	{
		vec2 rel;
		rel.x = event.x;
		rel.y = event.y;
		
		vec2 newPosition = p->movementDomainSize * rel + p->movementDomainStart;
		
		p->objectBehaviour->position = vec3(newPosition, 0);
		
		// send some midi data
		p->midiOut.sendCC(1, event.x);
		p->midiOut.sendCC(2, event.y);
	}
}