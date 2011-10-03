#include "WiimoteInputManager.hpp"

#include <kocmoc-core/compiler.h>

using namespace sputnik::input;
using namespace kocmoc::core;

using kocmoc::core::input::ButtonEvent;

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
		for (std::vector<CWiimote >::iterator it = wiimotes->begin();
			 it != wiimotes->end();
			 it++)
		{
			switch (it->GetEvent())
			{
				case CWiimote::EVENT_EVENT:
					handleEvent(*it);
					break;
				default:
					break;
			}
		}
	}
}

void WiimoteInputManager::handleEvent(CWiimote& wiimote)
{
	if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_A))
		notifyButtonListeners(WIIMOTE_EVENT_BUTTON_A, ButtonEvent(true));
	
	if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_B))
		notifyButtonListeners(WIIMOTE_EVENT_BUTTON_B, ButtonEvent(true));
	
	if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_ONE))
		notifyButtonListeners(WIIMOTE_EVENT_BUTTON_1, ButtonEvent(true));
	
	if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_TWO))
		notifyButtonListeners(WIIMOTE_EVENT_BUTTON_2, ButtonEvent(true));
	
	if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_LEFT))
		notifyButtonListeners(WIIMOTE_EVENT_BUTTON_LEFT, ButtonEvent(true));
	
	if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_RIGHT))
		notifyButtonListeners(WIIMOTE_EVENT_BUTTON_RIGHT, ButtonEvent(true));
	
	if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_UP))
		notifyButtonListeners(WIIMOTE_EVENT_BUTTON_UP, ButtonEvent(true));
	
	if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_DOWN))
		notifyButtonListeners(WIIMOTE_EVENT_BUTTON_DOWN, ButtonEvent(true));
	
	if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_MINUS))
		notifyButtonListeners(WIIMOTE_EVENT_BUTTON_MINUS, ButtonEvent(true));
	
	if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_PLUS))
		notifyButtonListeners(WIIMOTE_EVENT_BUTTON_PLUS, ButtonEvent(true));
	
	if(wiimote.Buttons.isJustPressed(CButtons::BUTTON_HOME))
		notifyButtonListeners(WIIMOTE_EVENT_BUTTON_HOME, ButtonEvent(true));
	
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
    }
	
    int exType = wiimote.ExpansionDevice.GetType();
    if(exType == wiimote.ExpansionDevice.TYPE_NUNCHUK)
    {

    }
 
}

void WiimoteInputManager::handleStatus(CWiimote &wiimote)
{
	std::cout << "Wiimote Status for Wiimote: " << wiimote.GetID() << std::endl;
	std::cout << "battery level: " << wiimote.GetBatteryLevel() << "%" << std::endl;
}

void WiimoteInputManager::notifyButtonListeners(int wiimoteEventSymbolicConstant, ButtonEvent event)
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
	}
}