#include "WeightTest.hpp"

#include <kocmoc-core/component/ObjectBehaviour.hpp>
#include <kocmoc-core/scene/AssetLoader.hpp>
#include <kocmoc-core/math/math.hpp>
#include <kocmoc-core/component/Renderable.hpp>

#include <component/TextLabel.hpp>
#include <component/Selectable.hpp>

using namespace sputnik::object;
using namespace sputnik::component;
using namespace sputnik::scene;

using namespace kocmoc::core::component;
using namespace kocmoc::core;
using namespace kocmoc::core::scene;
using namespace kocmoc::core::types;

WeightTest::WeightTest(std::string name, kocmoc::core::util::Properties* props,
					   glm::vec3 pos, float mass, SelectableWorld* world)
	: Object(name, props)
{
	ObjectBehaviour* ob = new ObjectBehaviour();
	ob->lambda = math::decayConst(0.5f);
	ob->position = pos;
	ob->mass = mass;
	registerUpdateReceiver(ob);
	addComponent(ob);
	
	AssetLoader loader;
	loader.addResourcePath(props->getString(symbolize("media-path")));
	std::string model = props->getString(symbolize("weight-test-model"));
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
	
	component::Selectable* selectable = new component::Selectable(3.0f);
	addComponent(selectable);
	registerUpdateReceiver(selectable);
	world->add(selectable);

	initComponents();
}
