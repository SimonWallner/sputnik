//
//  ShipController.cpp
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "MonkeyController.hpp"
#include "MonkeyBehaviour.hpp"

using namespace sputnik::component;

MonkeyController::MonkeyController()
{}

void MonkeyController::init()
{
	monkeyBehaviour = parent->getComponent<MonkeyBehaviour>();
}

void MonkeyController::onUpdate()
{
	monkeyBehaviour->left();
}