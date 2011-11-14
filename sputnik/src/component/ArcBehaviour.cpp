#include <component/ArcBehaviour.hpp>

#include <iostream>

#include <kocmoc-core/renderer/RenderMesh.hpp>
#include <kocmoc-core/scene/AssetLoader.hpp>
#include <kocmoc-core/util/Properties.hpp>
#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/component/Renderable.hpp>
#include <kocmoc-core/math/math.hpp>

#include <glm/gtc/matrix_transform.hpp>


using namespace sputnik::component;
using namespace sputnik::input;
using namespace sputnik::scene;

using namespace kocmoc::core;

using kocmoc::core::renderer::RenderPass;
using kocmoc::core::renderer::RenderPass;
using kocmoc::core::scene::Camera;
using kocmoc::core::scene::AssetLoader;
using kocmoc::core::component::Renderable;
using kocmoc::core::util::Properties;
using kocmoc::core::types::symbolize;
using kocmoc::core::types::Symbol;
using kocmoc::core::input::ButtonEvent;

using glm::vec3;
using glm::vec4;

ArcBehaviour::ArcBehaviour(Properties* _props,
						   unsigned int _instanceCount,
						   WiimoteInputManager* inputManager,
						   kocmoc::core::scene::FilmCamera* _camera,
						   scene::SelectableWorld* _world)
	: props(_props)
	, instanceCount(_instanceCount)
	, start(glm::vec3(0))
	, end(glm::vec3(0, 0, -20))
	, arcPointer(kocmoc::core::types::symbolize("arc-pointer"))
	, arcB(kocmoc::core::types::symbolize("arc-B"))
	, camera(_camera)
	, world(_world)
	, hover(NULL)
	, selection(NULL)
	, ic(this)
{
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_CURSOR_RELATIVE_X_Y, arcPointer);
	inputManager->registerWiimoteEventListener(arcPointer, &ic);
	
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_BUTTON_B_PRESSED, arcB);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_BUTTON_B_RELEASED, arcB);
	inputManager->registerWiimoteEventListener(arcB, &ic);
}

void ArcBehaviour::onRender(RenderPass pass, Camera *camera)
{	
	if (pass == kocmoc::core::renderer::RP_NORMAL)
	{
		instancedMesh->setShaderParam("start", start);
		instancedMesh->setShaderParam("end", end);
		instancedMesh->setShaderParam("midpoint", midpoint);
		instancedMesh->setShaderParam("totalInstances", instanceCount);
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
//#warning XXX: problem with mutable strings in props!
	Renderable* renderable = loader.load(test.c_str(), shaderPath);
	instancedMesh = renderable->getFirstMesh();
}

void ArcBehaviour::moveArc(float x, float y)
{
	vec3 originViewSpace = vec3(0, -1.5, -2);
	float arcMaxLength = 100.0f;
	glm::mat4 inverseViewMatrix = glm::core::function::matrix::inverse(camera->getViewMatrix());
	
	vec3 arcStartWorldSpace = vec3(inverseViewMatrix * vec4(originViewSpace, 1));
	setStart(arcStartWorldSpace);
	
	vec3 normalizedPointer = vec3((x - 0.5f) * 2.0f,
								  (y - 0.5f) * 2.0f, 1.0f);
	
	vec3 directionBounds = vec3(1, 0.75, -1);
	
	vec3 pointerDirectionViewSpace = glm::normalize((normalizedPointer * directionBounds));
	vec3 endViewSpace = pointerDirectionViewSpace * arcMaxLength;
	vec3 arcEndWorldSpace = vec3(inverseViewMatrix * vec4(endViewSpace, 1.0f));
	
	vec3 arcDirectionViewSpace = glm::normalize(endViewSpace - originViewSpace);
	vec3 arcDirectionWorldSpace = glm::normalize(arcEndWorldSpace - arcStartWorldSpace);

	
	Selectable* prevHover = hover;
	hover = world->rayIntersection(this->start, this->end);
	
	if (hover == NULL)
	{
		if (prevHover != NULL)
			prevHover->setHovering(false);
	}
	else if (prevHover != hover)
	{
		if (prevHover != NULL)
			prevHover->setHovering(false);
		hover->setHovering(true);
	}

	
	if (selection)
	{
		vec3 posWorldSpace = selection->getPosition();
		setEnd(posWorldSpace);
		
		float midLength = glm::length(this->start - this->end) / 2.0f;
		vec3 midViewSpace = originViewSpace + arcDirectionViewSpace * midLength;
		
		setMid(vec3(inverseViewMatrix * vec4(midViewSpace, 1.0f)));
		
		// apply force
		vec3 intersection = math::planeRayIntersection(posWorldSpace,
													   camera->getViewVector(),
													   arcStartWorldSpace,
													   arcDirectionWorldSpace);
		selection->drag(intersection - posWorldSpace);
	}
	else
	{
		setEnd(arcEndWorldSpace);
		setMid((this->start + this->end) / 2.0f);
	}
}

void ArcBehaviour::InputCallback::wiimoteAnalogEventCallback(Symbol name,
															 WiimoteAnalogEvent event)
{
	if (name == p->arcPointer)
		p->moveArc(event.x, event.y);
}

void ArcBehaviour::InputCallback::wiimoteButtonEventCallback(Symbol name,
															 WiimoteButtonEvent event)
{
	if (name == p->arcB && event.state == ButtonEvent::PRESSED)
	{
		p->selection = p->hover;
		if (p->selection != NULL)
			p->selection->setSelected(true);
	}
	
	else if (name == p->arcB && event.state == ButtonEvent::RELEASED)
	{
		if (p->selection != NULL)
			p->selection->setSelected(false);
		p->selection = NULL;
	}
}
