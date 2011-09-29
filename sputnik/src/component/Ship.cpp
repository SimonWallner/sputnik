//
//  Ship.cpp
//  kocmoc
//
//  Created by Simon Wallner on 30.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Ship.hpp"

#include <kocmoc-core/scene/AssetLoader.hpp>

using namespace kocmoc::component;
using namespace kocmoc::core::component;

using kocmoc::core::scene::AssetLoader;
using kocmoc::core::types::symbolize;

void Ship::init()
{
	objectBehaviour = new ObjectBehaviour();
	shipBehaviour = new ShipBehaviour();
	shipController = new ShipController();

	AssetLoader loader;
	loader.addResourcePath(props->getString(symbolize("media-path")));
	std::string test = props->getString(symbolize("test-model-name"));
	std::string shaderPath = props->getString(symbolize("media-path")) + "shaders/base";
	
	// FIXME: something mutates my stirngs in the props.
	// changing it here to c_str() helped, but it is evil
	// XXX:
#warning XXX: problem with mutable strings in props!
	renderable = loader.load(test.c_str(), shaderPath);
	props->dumpCache();
	
	addComponent(objectBehaviour);
	addComponent(shipBehaviour);
	addComponent(renderable);
	addComponent(shipController);
	
	registerUpdateReceiver(shipController);
	registerRenderReceiver(renderable);
	
	shipController->init();
	objectBehaviour->init();
	shipBehaviour->init();
	renderable->init();
}