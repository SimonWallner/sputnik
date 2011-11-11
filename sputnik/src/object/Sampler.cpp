#include "Sampler.hpp"

#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/scene/AssetLoader.hpp>
#include <kocmoc-core/component/Renderable.hpp>

#include <component/Selectable.hpp>
#include <component/TextLabel.hpp>
#include <component/SamplerBehaviour.hpp>

using namespace sputnik::object;
using namespace sputnik::component;

using kocmoc::core::component::Renderable;
using kocmoc::core::component::ObjectBehaviour;
using kocmoc::core::scene::AssetLoader;
using kocmoc::core::types::symbolize;

using std::string;

sputnik::object::Sampler::Sampler(string name, kocmoc::core::util::Properties* props,
								  scene::SelectableWorld* world)
: Object(name, props)
{
	sputnik::component::Selectable* selectable = new sputnik::component::Selectable(3.0f);
	addComponent(selectable);
	world->add(selectable);
	
	objectBehaviour = new ObjectBehaviour();
	registerUpdateReceiver(objectBehaviour);
	addComponent(objectBehaviour);
	
	AssetLoader loader;
	loader.addResourcePath(props->getString(symbolize("media-path")));
	std::string test = props->getString(symbolize("sphere1-model-name"));
	std::string shaderPath = props->getString(symbolize("media-path")) + "shaders/base";
	
	// FIXME: something mutates my strings in the props.
	// changing it here to c_str() helped, but it is evil
	// XXX:
//#warning XXX: problem with mutable strings in props!
	kocmoc::core::component::Renderable* renderable = loader.load(test.c_str(), shaderPath);
	addComponent(renderable);	
	registerRenderReceiver(renderable);
	
	TextLabel* textLabel = new TextLabel(props, name);
	addComponent(textLabel);
	registerRenderReceiver(textLabel);
	registerUpdateReceiver(textLabel);
	
	SamplerBehaviour* samplerBehaviour = new SamplerBehaviour();
	addComponent(samplerBehaviour);
	registerUpdateReceiver(samplerBehaviour);
	
	initComponents();
}
