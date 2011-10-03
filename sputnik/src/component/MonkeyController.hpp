//
//  ShipController.h
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_COMPONENT_SHIP_CONTROLLER_HPP
#define KOCMOC_COMPONENT_SHIP_CONTROLLER_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/types/types.h>

namespace sputnik
{
	namespace component
	{
		class MonkeyBehaviour;
		
		class MonkeyController : public kocmoc::core::componentSystem::Component
		{
		public:
			
			MonkeyController(void);
			
			void onUpdate(void);
			
			void init(void);

		private:
			MonkeyBehaviour* monkeyBehaviour;
		};
	}
}

#endif
