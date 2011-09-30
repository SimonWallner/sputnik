//
//  ShipController.cpp
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ShipController.hpp"

#include "ShipBehaviour.hpp"

using namespace sputnik::component;

ShipController::ShipController()
{}

void ShipController::init()
{
	shipBehaviour = parent->getComponent<ShipBehaviour>();
}

void ShipController::onUpdate()
{
	shipBehaviour->left();
}