//
//  Ship.pp
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_COMPONENT_SHIP_HPP
#define KOCMOC_COMPONENT_SHIP_HPP

#include <kocmoc-core/componentSystem/Object.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>
#include <kocmoc-core/component/Renderable.hpp>

#include "ShipBehaviour.hpp"
#include "ShipController.hpp"


namespace sputnik
{
	namespace component
	{
		class Ship : public kocmoc::core::componentSystem::Object
		{
		public:
			
			explicit Ship(std::string name, kocmoc::core::util::Properties* props) : Object(name, props) {}
			
			void onMessage(void);
			
			void init(void);
			
		private:
			kocmoc::core::component::ObjectBehaviour* objectBehaviour;
			ShipBehaviour* shipBehaviour;
			ShipController* shipController;
			kocmoc::core::component::Renderable* renderable;
		};
	}
}

#endif