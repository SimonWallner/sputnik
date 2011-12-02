#include "Sampler.hpp"

#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/scene/AssetLoader.hpp>
#include <kocmoc-core/component/Renderable.hpp>


#include <component/TextLabel.hpp>
#include <component/SamplerBehaviour.hpp>
#include <component/SpeedToMidi.hpp>

using namespace sputnik::object;
using namespace sputnik::component;
using namespace sputnik::scene;
using namespace kocmoc::core;
using namespace kocmoc::core::util;

using kocmoc::core::component::Renderable;
using kocmoc::core::component::ObjectBehaviour;
using kocmoc::core::scene::AssetLoader;
using kocmoc::core::types::symbolize;


using std::string;

sputnik::object::Sampler::Sampler(string name,
								  Sputnik* sputnik,
								  scene::SelectableWorld* world,
								  input::WiimoteInputManager* inputManager,
								  output::MIDIOut* mOut,
								  unsigned int cc,
								  std::string modelName)
: Object(name, props)
{
	objectBehaviour = new ObjectBehaviour();
	objectBehaviour->lambda = math::decayConst(0.5f);
	objectBehaviour->mass = 3.0f;
	registerUpdateReceiver(objectBehaviour);
	addComponent(objectBehaviour);
	
	Properties* props = sputnik->getProps();
	std::string model = props->getString(symbolize(modelName.c_str()));
	std::string shaderPath = props->getString(symbolize("media-path")) + "shaders/base";
	// FIXME: something mutates my strings in the props.
	// changing it here to c_str() helped, but it is evil
	// XXX:
//#warning XXX: problem with mutable strings in props!
	kocmoc::core::component::Renderable* renderable = sputnik->getAssetLoader()->load(model.c_str(), shaderPath);
	addComponent(renderable);	
	registerRenderReceiver(renderable);
	
	TextLabel* textLabel = new TextLabel(props, name);
	addComponent(textLabel);
	registerRenderReceiver(textLabel);
	registerUpdateReceiver(textLabel);
	
	SamplerBehaviour* samplerBehaviour = new SamplerBehaviour(world,
															  inputManager,
															  mOut,
															  cc);
	addComponent(samplerBehaviour);
	registerUpdateReceiver(samplerBehaviour);
	
	SpeedToMidi* speed2Midi = new SpeedToMidi(mOut, cc+1);
	addComponent(speed2Midi);
	registerUpdateReceiver(speed2Midi);
	
	initComponents();
}
