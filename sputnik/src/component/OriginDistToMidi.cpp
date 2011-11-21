#include "OriginDistToMidi.hpp"

using namespace kocmoc::core::component;
using namespace sputnik::component;

void OriginDistToMidi::init()
{
	ob = parent->getComponent<ObjectBehaviour>();
}

void OriginDistToMidi::onUpdate(float deltaT, float t)
{
	float maxDistance = 10.0f;
	
	float distance = glm::length(origin - ob->position);
	mOut->sendCC(cc, distance / maxDistance);
	
	UNUSED deltaT;
	UNUSED t;
}
