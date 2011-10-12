#include "Sampler.hpp"

#include <kocmoc-core/component/ObjectBehaviour.hpp>
#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/scene/AssetLoader.hpp>

#include <component/Selectable.hpp>

using namespace sputnik::object;
using namespace sputnik::component;

using kocmoc::core::component::Renderable;
using kocmoc::core::component::ObjectBehaviour;
using kocmoc::core::componentSystem::Component;
using kocmoc::core::scene::AssetLoader;
using kocmoc::core::types::symbolize;

using std::string;

Sampler::Sampler(string name, kocmoc::core::util::Properties* props)
: Object(name, props)
{
	Selectable* selectable = new Selectable(1.0f);
	addComponent(selectable);
	
	ObjectBehaviour* objectBehaviour = new ObjectBehaviour();
	addComponent(objectBehaviour);
	
	AssetLoader loader;
	loader.addResourcePath(props->getString(symbolize("media-path")));
	std::string test = props->getString(symbolize("sphere1-model-name"));
	std::string shaderPath = props->getString(symbolize("core-media-path")) + "shaders/base";
	
	// FIXME: something mutates my stirngs in the props.
	// changing it here to c_str() helped, but it is evil
	// XXX:
#warning XXX: problem with mutable strings in props!
	Renderable* renderable = loader.load(test.c_str(), shaderPath);
	addComponent(renderable);
	
	registerRenderReceiver(renderable);

	
	initComponents();
}