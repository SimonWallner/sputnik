#include "TapeMachine.hpp"

#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/scene/AssetLoader.hpp>
#include <kocmoc-core/component/Renderable.hpp>

#include <component/TextLabel.hpp>
#include <component/SpeedToMidi.hpp>
#include <component/Selectable.hpp>

using namespace sputnik::object;
using namespace sputnik::component;
using namespace kocmoc::core;

using kocmoc::core::component::Renderable;
using kocmoc::core::component::ObjectBehaviour;
using kocmoc::core::scene::AssetLoader;
using kocmoc::core::types::symbolize;

using std::string;

TapeMachine::TapeMachine(string name,
								  kocmoc::core::util::Properties* props,
								  scene::SelectableWorld* world,
								  output::MIDIOut* mOut,
								  unsigned int cc,
								  std::string modelName)
: Object(name, props)
{
	objectBehaviour = new ObjectBehaviour();
	objectBehaviour->lambda = math::decayConst(0.5f);
	registerUpdateReceiver(objectBehaviour);
	addComponent(objectBehaviour);
	
	AssetLoader loader;
	loader.addResourcePath(props->getString(symbolize("media-path")));
	std::string model = props->getString(symbolize(modelName.c_str()));
	std::string shaderPath = props->getString(symbolize("media-path")) + "shaders/base";
	
	// FIXME: something mutates my strings in the props.
	// changing it here to c_str() helped, but it is evil
	// XXX:
//#warning XXX: problem with mutable strings in props!
	kocmoc::core::component::Renderable* renderable = loader.load(model.c_str(), shaderPath);
	addComponent(renderable);	
	registerRenderReceiver(renderable);
	
	TextLabel* textLabel = new TextLabel(props, name);
	addComponent(textLabel);
	registerRenderReceiver(textLabel);
	registerUpdateReceiver(textLabel);
	
	SpeedToMidi* speed2Midi = new SpeedToMidi(mOut, cc);
	addComponent(speed2Midi);
	registerUpdateReceiver(speed2Midi);
	
	Selectable* selectable = new Selectable(3.0f);
	addComponent(selectable);
	world->add(selectable);
	
	initComponents();
}
