#include "WiimoteInputManager.hpp"

#include <kocmoc-core/compiler.h>

using namespace sputnik::input;
using namespace kocmoc::core;

using kocmoc::core::input::ButtonEvent;
using kocmoc::core::input::AnalogEvent;

WiimoteInputManager::WiimoteInputManager(GLFWwindow window)
	: InputManager(window)
{
	std::cout << "searching wiimotes. Press buttons 1 and 2!" << std::endl;
	
	// code derived from the wiic tutorial
	
	printf("Searching for wiimotes... Turn them on!\n");
	
	//Find the wiimote
	int numFound = wii.Find(5);
	printf("Found %d Wiimotes\n", numFound);
	
	// Connect to the Wiimotes
	wiimotes = &wii.Connect();
	printf("Connected to %d wiimotes\n", (int) wiimotes->size());
	
	// Writing to the Wiimotes
	int LED_MAP[4] = {CWiimote::LED_1, CWiimote::LED_2, CWiimote::LED_3, CWiimote::LED_4};
	unsigned int index = 0;
	for (std::vector<CWiimote >::iterator it = wiimotes->begin();
		it != wiimotes->end();
		it++, index++)
	{
		it->SetLEDs(LED_MAP[index]);
		it->SetMotionSensingMode(CWiimote::ON);
		it->EnableMotionPlus(CWiimote::ON);
		it->IR.SetMode(CIR::ON);
		it->IR.SetVres(10000, 10000);
	}
}

void WiimoteInputManager::dumpBindings()
{
	InputManager::dumpBindings();
}

void WiimoteInputManager::pollWiimote()
{
	if (wii.Poll())
	{
		unsigned int controllerNumber = 0;
		for (std::vector<CWiimote >::iterator it = wiimotes->begin();
			 it != wiimotes->end();
			 it++, controllerNumber++)
		{
			switch (it->GetEvent())
			{
				case CWiimote::EVENT_EVENT:
					handleEvent(*it, controllerNumber);
					break;
					
				case CWiimote::EVENT_STATUS:
					handleStatus(*it, controllerNumber);
					break;

				default:
					break;
			}
		}
	}
}

void WiimoteInputManager::handleEvent(CWiimote& wiimote, unsigned int controllerNumber)
{
	{
		// pressed
		if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_A))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_A_PRESSED, ButtonEvent(ButtonEvent::PRESSED), controllerNumber);
		
		if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_B))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_B_PRESSED, ButtonEvent(ButtonEvent::PRESSED), controllerNumber);
		
		if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_ONE))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_1_PRESSED, ButtonEvent(ButtonEvent::PRESSED), controllerNumber);
		
		if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_TWO))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_2_PRESSED, ButtonEvent(ButtonEvent::PRESSED), controllerNumber);
		
		if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_LEFT))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_LEFT_PRESSED, ButtonEvent(ButtonEvent::PRESSED), controllerNumber);
		
		if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_RIGHT))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_RIGHT_PRESSED, ButtonEvent(ButtonEvent::PRESSED), controllerNumber);
		
		if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_UP))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_UP_PRESSED, ButtonEvent(ButtonEvent::PRESSED), controllerNumber);
		
		if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_DOWN))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_DOWN_PRESSED, ButtonEvent(ButtonEvent::PRESSED), controllerNumber);
		
		if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_MINUS))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_MINUS_PRESSED, ButtonEvent(ButtonEvent::PRESSED), controllerNumber);
		
		if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_PLUS))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_PLUS_PRESSED, ButtonEvent(ButtonEvent::PRESSED), controllerNumber);
		
		if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_HOME))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_HOME_PRESSED, ButtonEvent(ButtonEvent::PRESSED), controllerNumber);
		
		// Released
		if(wiimote.Buttons.isReleased(CButtons::BUTTON_A))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_A_RELEASED, ButtonEvent(ButtonEvent::RELEASED), controllerNumber);
		
		if(wiimote.Buttons.isReleased(CButtons::BUTTON_B))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_B_RELEASED, ButtonEvent(ButtonEvent::RELEASED), controllerNumber);
		
		if(wiimote.Buttons.isReleased(CButtons::BUTTON_ONE))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_1_RELEASED, ButtonEvent(ButtonEvent::RELEASED), controllerNumber);
		
		if(wiimote.Buttons.isReleased(CButtons::BUTTON_TWO))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_2_RELEASED, ButtonEvent(ButtonEvent::RELEASED), controllerNumber);
		
		if(wiimote.Buttons.isReleased(CButtons::BUTTON_LEFT))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_LEFT_RELEASED, ButtonEvent(ButtonEvent::RELEASED), controllerNumber);
		
		if(wiimote.Buttons.isReleased(CButtons::BUTTON_RIGHT))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_RIGHT_RELEASED, ButtonEvent(ButtonEvent::RELEASED), controllerNumber);
		
		if(wiimote.Buttons.isReleased(CButtons::BUTTON_UP))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_UP_RELEASED, ButtonEvent(ButtonEvent::RELEASED), controllerNumber);
		
		if(wiimote.Buttons.isReleased(CButtons::BUTTON_DOWN))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_DOWN_RELEASED, ButtonEvent(ButtonEvent::RELEASED), controllerNumber);
		
		if(wiimote.Buttons.isReleased(CButtons::BUTTON_MINUS))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_MINUS_RELEASED, ButtonEvent(ButtonEvent::RELEASED), controllerNumber);
		
		if(wiimote.Buttons.isReleased(CButtons::BUTTON_PLUS))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_PLUS_RELEASED, ButtonEvent(ButtonEvent::RELEASED), controllerNumber);
		
		if(wiimote.Buttons.isReleased(CButtons::BUTTON_HOME))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_HOME_RELEASED, ButtonEvent(ButtonEvent::RELEASED), controllerNumber);
		
		
		// held
		if(wiimote.Buttons.isHeld(CButtons::BUTTON_A))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_A_HELD, ButtonEvent(ButtonEvent::HELD), controllerNumber);
		
		if(wiimote.Buttons.isHeld(CButtons::BUTTON_B))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_B_HELD, ButtonEvent(ButtonEvent::HELD), controllerNumber);
		
		if(wiimote.Buttons.isHeld(CButtons::BUTTON_ONE))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_1_HELD, ButtonEvent(ButtonEvent::HELD), controllerNumber);
		
		if(wiimote.Buttons.isHeld(CButtons::BUTTON_TWO))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_2_HELD, ButtonEvent(ButtonEvent::HELD), controllerNumber);
		
		if(wiimote.Buttons.isHeld(CButtons::BUTTON_LEFT))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_LEFT_HELD, ButtonEvent(ButtonEvent::HELD), controllerNumber);
		
		if(wiimote.Buttons.isHeld(CButtons::BUTTON_RIGHT))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_RIGHT_HELD, ButtonEvent(ButtonEvent::HELD), controllerNumber);
		
		if(wiimote.Buttons.isHeld(CButtons::BUTTON_UP))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_UP_HELD, ButtonEvent(ButtonEvent::HELD), controllerNumber);
		
		if(wiimote.Buttons.isHeld(CButtons::BUTTON_DOWN))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_DOWN_HELD, ButtonEvent(ButtonEvent::HELD), controllerNumber);
		
		if(wiimote.Buttons.isHeld(CButtons::BUTTON_MINUS))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_MINUS_HELD, ButtonEvent(ButtonEvent::HELD), controllerNumber);
		
		if(wiimote.Buttons.isHeld(CButtons::BUTTON_PLUS))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_PLUS_HELD, ButtonEvent(ButtonEvent::HELD), controllerNumber);
		
		if(wiimote.Buttons.isHeld(CButtons::BUTTON_HOME))
			notifyButtonListeners(WIIMOTE_EVENT_BUTTON_HOME_HELD, ButtonEvent(ButtonEvent::HELD), controllerNumber);
	} // buttons
	
    if(wiimote.isUsingACC())
    {

    }
	
	// if the Motion Plus is turned on then print angles
    if(wiimote.isUsingMotionPlus())
	{
    }
	
    // if(IR tracking is on then print the coordinates
	if(wiimote.isUsingIR())
    {
		{
			int x, y;
			wiimote.IR.GetCursorPosition(x, y);
			//		std::cout << "cursor position :" << x << " | " << y << std::endl;
			
			float relativeX = (float)x / 10000.0f;
			float relativeY = (float)y / 10000.0f;
			
			notifyAnalogListeners(WIIMOTE_EVENT_CURSOR_RELATIVE_X_Y,
								  WiimoteAnalogEvent(controllerNumber, relativeX,
													 1.0f - relativeY, 0));
		}
		{
			// code derived from the sample
			int constants[] = {WIIMOTE_EVENT_DOT_0_X_Y_SIZE,
				WIIMOTE_EVENT_DOT_1_X_Y_SIZE,
				WIIMOTE_EVENT_DOT_2_X_Y_SIZE,
				WIIMOTE_EVENT_DOT_3_X_Y_SIZE};
			int i = 0;
			
			std::vector<CIRDot>& dots = wiimote.IR.GetDots();
			for(std::vector<CIRDot >::iterator it = dots.begin(); it != dots.end(); it++)
			{
				int x, y;
//				(*it).GetCoordinate(x, y);
				(*it).GetRawCoordinate(x, y);
				
				float size = 0;
				if ((*it).isVisible())
					size = (*it).GetSize();
				
				notifyAnalogListeners(constants[i],
									  WiimoteAnalogEvent(controllerNumber, x, y, size));
				i++;
			}
		}
    }
	
    int exType = wiimote.ExpansionDevice.GetType();
    if(exType == wiimote.ExpansionDevice.TYPE_NUNCHUK)
    {

    }
 
}

void WiimoteInputManager::handleStatus(CWiimote &wiimote, unsigned int controllerNumber)
{
	std::cout << "Wiimote Status for Wiimote: " << controllerNumber << std::endl;
	std::cout << "battery level: " << wiimote.GetBatteryLevel() << "%" << std::endl;
}

void WiimoteInputManager::notifyButtonListeners(int wiimoteEventSymbolicConstant,
												ButtonEvent event,
												unsigned int controllerNumber)
{
	// constant --> symbol
	std::pair<WiimoteBindings::const_iterator, WiimoteBindings::const_iterator> bounds = 
	wiimoteEventBindings.equal_range(wiimoteEventSymbolicConstant);
	
	for (WiimoteBindings::const_iterator ci = bounds.first;
		 ci != bounds.second;
		 ci++)
	{
		// symbol --> listener
		std::pair<ButtonEventListenerMultiMap::const_iterator, ButtonEventListenerMultiMap::const_iterator> bounds2 = 
		buttonEventListeners.equal_range(ci->second);
		
		for (ButtonEventListenerMultiMap::const_iterator listeners = bounds2.first;
			 listeners != bounds2.second;
			 listeners++)
		{
			(listeners->second)->buttonEventCallback(ci->second, event);
		}
		
		// symbol --> listener
		std::pair<WiimoteEventListenerMultiMap::const_iterator, WiimoteEventListenerMultiMap::const_iterator> bounds3 = 
		wiimoteEventListeners.equal_range(ci->second);
		
		for (WiimoteEventListenerMultiMap::const_iterator listeners = bounds3.first;
			 listeners != bounds3.second;
			 listeners++)
		{
			(listeners->second)->wiimoteButtonEventCallback(ci->second, WiimoteButtonEvent(controllerNumber, event.state));
		}
	}
}

void WiimoteInputManager::notifyAnalogListeners(int wiimoteEventSymbolicConstant,
												WiimoteAnalogEvent event)
{
	// constant --> symbol
	std::pair<WiimoteBindings::const_iterator, WiimoteBindings::const_iterator> bounds = 
	wiimoteEventBindings.equal_range(wiimoteEventSymbolicConstant);
	
	for (WiimoteBindings::const_iterator ci = bounds.first;
		 ci != bounds.second;
		 ci++)
	{
		// symbol --> listener
		std::pair<WiimoteEventListenerMultiMap::const_iterator, WiimoteEventListenerMultiMap::const_iterator> bounds3 = 
		wiimoteEventListeners.equal_range(ci->second);
		
		for (WiimoteEventListenerMultiMap::const_iterator listeners = bounds3.first;
			 listeners != bounds3.second;
			 listeners++)
		{
			(listeners->second)->wiimoteAnalogEventCallback(ci->second, event);
		}
	}
}