//
//  Ship.pp
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef SPUTNIK_COMPONENT_MONKEY_HPP
#define	SPUTNIK_COMPONENT_MONKEY_HPP

#include <kocmoc-core/componentSystem/Object.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>
#include <kocmoc-core/component/Renderable.hpp>

#include <input/WiimoteInputManager.hpp>

#include "MonkeyBehaviour.hpp"

namespace sputnik
{
	namespace component
	{
		class Monkey : public kocmoc::core::componentSystem::Object
		{
		public:
			Monkey(std::string name,
				   kocmoc::core::util::Properties* props,
				   sputnik::input::WiimoteInputManager* _inputManager)
				: Object(name, props)
				, inputManager(_inputManager)
			{}
			
			void onMessage(void);
			
			void init(void);
			
		private:
			kocmoc::core::component::ObjectBehaviour* objectBehaviour;
			MonkeyBehaviour* monkeyBehaviour;
			kocmoc::core::component::Renderable* renderable;
			
			sputnik::input::WiimoteInputManager* inputManager;
		};
	}
}

#endif