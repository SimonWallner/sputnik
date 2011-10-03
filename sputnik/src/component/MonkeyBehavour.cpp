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

void MonkeyBehaviour::init()
{
	objectBehaviour = parent->getComponent<ObjectBehaviour>();
}