#include "SelectableWorld.hpp"

#include <float.h>

#include <kocmoc-core/math/math.hpp>

using namespace sputnik::scene;
using namespace sputnik::component;

using kocmoc::core::math::intersectRaySphere;
using kocmoc::core::math::min;

using glm::vec3;

Selectable* SelectableWorld::rayIntersction(vec3 startPoint,
											vec3 endPoint)
{
	vec3 direction = endPoint - startPoint;
	float dist = FLT_MAX;
	Selectable* closest = NULL;
	
	for (SelectableList::const_iterator it = world.begin();
		 it != world.end();
		 it++)
	{
		float newDist = intersectRaySphere((*it)->getPosition(), (*it)->getRadius(),
								  startPoint, direction);
		if (newDist < dist)
		{
			closest = *it;
			dist = newDist;
		}
	}
	return closest;
}

