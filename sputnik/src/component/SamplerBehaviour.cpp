#include "SamplerBehaviour.hpp"

using namespace sputnik::component;
using namespace kocmoc::core::component;
using namespace kocmoc::core;

using glm::vec3;

void SamplerBehaviour::init()
{
	ob = parent->getComponent<ObjectBehaviour>();
	selectable = parent->getComponent<Selectable>();
}

void SamplerBehaviour::onUpdate(float deltaT, float t)
{
	UNUSED deltaT;
	UNUSED t;
	
	if (selectable->isSelected())
	{
		ob->scale = vec3(1.5f);
	}
	else
	{
		ob->drag = vec3(0);
		
		if (selectable->isHovering())
			ob->scale = vec3(1.2f);
		else 
			ob->scale = vec3(1);
	}
}
