#include "WiimoteDebugger.hpp"

#include <iostream>

using namespace sputnik::component;
using namespace kocmoc::core::component;
using kocmoc::core::types::symbolize;
using kocmoc::core::types::Symbol;
using sputnik::input::WiimoteAnalogEvent;
using sputnik::input::WiimoteEventListener;

WiimoteDebugger::WiimoteDebugger(std::string name, kocmoc::core::util::Properties* props,
											sputnik::input::WiimoteInputManager* _inputManager)
	: Object(name, props)
	, inputManager(_inputManager)
	, dot0(symbolize("dot-0"))
	, dot1(symbolize("dot-1"))
	, dot2(symbolize("dot-2"))
	, dot3(symbolize("dot-3"))
	, ic(this)
{}

void WiimoteDebugger::init()
{
	markers[0] = new OverlayQuad(props);
	markers[1] = new OverlayQuad(props);
	markers[2] = new OverlayQuad(props);
	markers[3] = new OverlayQuad(props);
	
	for (unsigned int i = 0; i < 4; i++)
	{
		addComponent(markers[i]);
		registerRenderReceiver(markers[i]);
	}
	
	initComponents();
	
	inputManager->registerWiimoteEventListener(dot0, &ic);
	inputManager->registerWiimoteEventListener(dot1, &ic);
	inputManager->registerWiimoteEventListener(dot2, &ic);
	inputManager->registerWiimoteEventListener(dot3, &ic);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_DOT_0_X_Y_SIZE, dot0);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_DOT_1_X_Y_SIZE, dot1);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_DOT_2_X_Y_SIZE, dot2);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_DOT_3_X_Y_SIZE, dot3);
	
	std::cout << "dump wiimote input manager" << std::endl;
	inputManager->dumpBindings();
	
}

void WiimoteDebugger::InputCallback::wiimoteAnalogEventCallback(Symbol name,
																WiimoteAnalogEvent event)
{
	Symbol dots[] = {p->dot0, p->dot1, p->dot2, p->dot3};
	for (unsigned int i = 0; i < 4; i++)
	{
		if (name == dots[i])
		{
			p->markers[i]->setScale(glm::vec2(event.z) * 8.0f);
			p->markers[i]->setPosition(glm::vec2(event.x, event.y));
		}
	}
}
