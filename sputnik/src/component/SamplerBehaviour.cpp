#include "SamplerBehaviour.hpp"

#include <scene/Selectable.hpp>

using namespace sputnik::component;
using namespace sputnik::scene;
using namespace kocmoc::core::component;
using namespace kocmoc::core;

using glm::vec3;

SamplerBehaviour::SamplerBehaviour(SelectableWorld* world)
	: Selectable(3.0f)
{
	world->add(this);
}

void SamplerBehaviour::init()
{
	ob = parent->getComponent<ObjectBehaviour>();
}

void SamplerBehaviour::onUpdate(float deltaT, float t)
{
	UNUSED deltaT;
	UNUSED t;

	//...
}

void SamplerBehaviour::setHovering(bool isHovering)
{
	if (isHovering)
		ob->scale = vec3(1.2f);
	else
		ob->scale = vec3(1.0f);
}

void SamplerBehaviour::setSelected(bool isSelected)
{
	if (isSelected)
		ob->scale = vec3(1.5f);
	else
		ob->drag = vec3(0);
}

void SamplerBehaviour::drag(vec3 F)
{
	ob->drag = F;
}

glm::vec3 SamplerBehaviour::getPosition() const
{
	return ob->position;
}



