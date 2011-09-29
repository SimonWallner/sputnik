//
//  ShipBehaviour.h
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_COMPONENT_SHIP_BEHAVIOUR
#define KOCMOC_COMPONENT_SHIP_BEHAVIOUR

#include <kocmoc-core/componentSystem/Component.hpp>

#include <kocmoc-core/component/ObjectBehaviour.hpp>

#include <iostream>

namespace kocmoc
{
	namespace component
	{
		class ShipBehaviour : public core::componentSystem::Component
		{
		public:
			ShipBehaviour(void) {};
			
			void left(void)
			{
				objectBehaviour->position.x += -1.0f;
			}
			
			void right(void)
			{
				objectBehaviour->position.x += 1.0f;
			}
			
			void init(void);
			
		private:
			core::component::ObjectBehaviour* objectBehaviour;
		};
	}
}

#endif