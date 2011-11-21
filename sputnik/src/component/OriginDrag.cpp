#include "OriginDrag.hpp"

using namespace sputnik::component;
using namespace kocmoc::core::component;

OriginDrag::OriginDrag(glm::vec3 _origin, float _force)
	: origin(_origin)
	, force(_force)
{}

void OriginDrag::init()
{
	ob = parent->getComponent<ObjectBehaviour>();
}


void OriginDrag::onUpdate(float deltaT, float t)
{
	ob->drag += (origin - ob->position) * force;
	
	UNUSED deltaT;
	UNUSED t;
}
