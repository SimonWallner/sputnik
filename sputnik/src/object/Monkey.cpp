//
//  Ship.cpp
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Monkey.hpp"

#include <kocmoc-core/scene/AssetLoader.hpp>

using namespace sputnik::object;
using namespace sputnik::component;
using namespace kocmoc::core::component;

using kocmoc::core::scene::AssetLoader;
using kocmoc::core::types::symbolize;

Monkey::Monkey(std::string name,
	   kocmoc::core::util::Properties* props,
	   sputnik::input::WiimoteInputManager* _inputManager)
: Object(name, props)
, inputManager(_inputManager)
{
	objectBehaviour = new ObjectBehaviour();
	monkeyBehaviour = new MonkeyBehaviour(inputManager);
	
	AssetLoader loader;
	loader.addResourcePath(props->getString(symbolize("media-path")));
	loader.addResourcePath(props->getString(symbolize("core-media-path")));
	std::string test = props->getString(symbolize("test-model-name"));
	std::string shaderPath = props->getString(symbolize("core-media-path")) + "shaders/base";
	
	// FIXME: something mutates my stirngs in the props.
	// changing it here to c_str() helped, but it is evil
	// XXX:
#warning XXX: problem with mutable strings in props!
	renderable = loader.load(test.c_str(), shaderPath);
	props->dumpCache();
	
	addComponent(objectBehaviour);
	addComponent(monkeyBehaviour);
	addComponent(renderable);
	
	registerRenderReceiver(renderable);
	
	initComponents();
}