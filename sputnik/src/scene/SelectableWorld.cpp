#include "SelectableWorld.hpp"

#include <kocmoc-core/math/math.hpp>

using namespace sputnik::scene;

using kocmoc::core::math::pointToRayDistance;
using kocmoc::core::math::min;

using glm::vec3;

Selectable* SelectableWorld::rayIntersection(vec3 startPoint,
											vec3 endPoint)
{
	vec3 direction = endPoint - startPoint;
	float distance = glm::length(direction);
	Selectable* closest = NULL;
	
	for (SelectableList::const_iterator it = world.begin();
		 it != world.end();
		 it++)
	{
		float rayDistance = pointToRayDistance((*it)->getPosition(), startPoint, direction);
		
		if (rayDistance == -1)
			continue;
		
		if (rayDistance < (*it)->getRadius()) // hit!
		{
			float newDist = glm::length(startPoint - (*it)->getPosition());
			if (newDist < distance)
			{
				closest = *it;
				distance = newDist;
			}
		}
	}
	return closest;
}
