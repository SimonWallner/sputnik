#include "WiimoteInputManager.hpp"

#include <wiic/wiicpp.h>

#include <kocmoc-core/compiler.h>

using namespace sputnik::input;
using namespace kocmoc::core;

WiimoteInputManager::WiimoteInputManager(GLFWwindow window)
	: InputManager(window)
{
	std::cout << "searching wiimotes. Press buttons 1 and 2!" << std::endl;
	
	// code derived from the wiic tutorial
	
	CWii wii; // Defaults to 4 remotes
	std::vector<CWiimote>::iterator i;
	int reloadWiimotes = 0;
	int numFound;
	int index;
	
	printf("Searching for wiimotes... Turn them on!\n");
	
	//Find the wiimote
	numFound = wii.Find(5);
	
	printf("Found %d Wiimotes\n", numFound);
	
	UNUSED reloadWiimotes;
	UNUSED index;
}

void WiimoteInputManager::dumpBindings()
{
	InputManager::dumpBindings();
}

void WiimoteInputManager::pollWiimote()
{
	
}