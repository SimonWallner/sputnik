#include "SpeedToMidi.hpp"

#include <math.h>

using namespace kocmoc::core::component;
using namespace sputnik::component;


void SpeedToMidi::init()
{
	ob = parent->getComponent<ObjectBehaviour>();
}

void SpeedToMidi::onUpdate(float deltaT, float t)
{
	float speed = glm::length(ob->speed);
	mOut.sendCC(cc, pow(speed/40.0f, 0.5f));
	
	UNUSED t;
	UNUSED deltaT;
}
