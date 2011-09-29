//
//  ShipBehaviour.cpp
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ShipBehaviour.hpp"

using namespace kocmoc::component;
using kocmoc::core::component::ObjectBehaviour;

void ShipBehaviour::init()
{
	objectBehaviour = parent->getComponent<ObjectBehaviour>();
}