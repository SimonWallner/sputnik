#include "WayPoint.hpp"
#include <component/Selectable.hpp>
#include <kocmoc-core/scene/AssetLoader.hpp>
#include <kocmoc-core/component/Renderable.hpp>

using namespace sputnik::object;
using namespace sputnik::component;

using namespace kocmoc::core;
using namespace kocmoc::core::component;
using namespace kocmoc::core::scene;
using namespace kocmoc::core::types;

WayPoint::WayPoint(util::Properties* props,
				   scene::SelectableWorld* world,
				   output::MIDIOut* mOut,
				   unsigned int cc) 
	: kocmoc::core::componentSystem::Object("way point i", props)
{
	AssetLoader loader;
	loader.addResourcePath(props->getString(symbolize("media-path")));
	std::string model = props->getString(symbolize("sphere4-model-name"));
	std::string shaderPath = props->getString(symbolize("media-path")) + "shaders/base";
	// FIXME: something mutates my strings in the props.
	// changing it here to c_str() helped, but it is evil
	// XXX:
	//#warning XXX: problem with mutable strings in props!
	kocmoc::core::component::Renderable* renderable = loader.load(model.c_str(), shaderPath);
	addComponent(renderable);	
	registerRenderReceiver(renderable);
	
	
	ob = new ObjectBehaviour();
	ob->mass = 0.5f;
	addComponent(ob);
	registerUpdateReceiver(ob);
	
	originDrag = new OriginDrag(glm::vec3(0));
	addComponent(originDrag);
	registerUpdateReceiver(originDrag);
	
	originDistToMidi = new OriginDistToMidi(mOut, cc);
	addComponent(originDistToMidi);
	registerUpdateReceiver(originDistToMidi);
	
	Selectable* selectable = new Selectable(2.0f); // make it slightly bigger
	addComponent(selectable);
	registerUpdateReceiver(selectable);
	world->add(selectable);
	
	initComponents();
}
