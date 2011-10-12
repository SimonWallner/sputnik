#include <component/ArcBehaviour.hpp>

#include <iostream>

#include <kocmoc-core/renderer/RenderMesh.hpp>
#include <kocmoc-core/scene/AssetLoader.hpp>
#include <kocmoc-core/util/Properties.hpp>
#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/component/Renderable.hpp>

using namespace sputnik::component;
using namespace sputnik::input;

using kocmoc::core::renderer::RenderPass;
using kocmoc::core::renderer::RenderPass;
using kocmoc::core::scene::Camera;
using kocmoc::core::scene::AssetLoader;
using kocmoc::core::component::Renderable;
using kocmoc::core::util::Properties;
using kocmoc::core::types::symbolize;
using kocmoc::core::types::Symbol;

ArcBehaviour::ArcBehaviour(Properties* _props,
						   unsigned int _instanceCount,
						   WiimoteInputManager* inputManager)
	: props(_props)
	, instanceCount(_instanceCount)
	, start(glm::vec3(0))
	, end(glm::vec3(0, 0, -20))
	, arcPointer(kocmoc::core::types::symbolize("arc-pointer"))
	, ic(this)
{
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_CURSOR_RELATIVE_X_Y, arcPointer);
	inputManager->registerWiimoteEventListener(arcPointer, &ic);
}

void ArcBehaviour::onRender(RenderPass pass, Camera *camera)
{	
	if (pass == kocmoc::core::renderer::RP_NORMAL)
	{
		instancedMesh->setShaderParam("start", start);
		instancedMesh->setShaderParam("end", end);
		instancedMesh->drawInstanced(camera, glm::mat4(1), instanceCount);
	}
}

void ArcBehaviour::init()
{
	AssetLoader loader;
	loader.addResourcePath(props->getString(symbolize("media-path")));
	loader.addResourcePath(props->getString(symbolize("core-media-path")));
	std::string test = props->getString(symbolize("arc-model-name"));
	std::string shaderPath = props->getString(symbolize("media-path")) + "shaders/arc";
	
	// FIXME: something mutates my stirngs in the props.
	// changing it here to c_str() helped, but it is evil
	// XXX:
#warning XXX: problem with mutable strings in props!
	Renderable* renderable = loader.load(test.c_str(), shaderPath);
	instancedMesh = renderable->getFirstMesh();
}

void ArcBehaviour::InputCallback::wiimoteAnalogEventCallback(Symbol name,
															 WiimoteAnalogEvent event)
{
	if (name == p->arcPointer)
	{
		p->setEnd(glm::vec3(40.0f * (event.x - 0.5f),
							40.0f * (event.y - 0.5f),
							-20.0f));
	}
}
