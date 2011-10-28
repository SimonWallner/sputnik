#ifndef SPUTNIK_SCENE_GENERATOR_HPP
#define SPUTNIK_SCENE_GENERATOR_HPP

#include <kocmoc-core/scene/TriangleMesh.hpp>

namespace sputnik
{
	namespace scene
	{
		/** 
		 * generators of all sorts
		 */
		namespace generator
		{
			kocmoc::core::scene::TriangleMesh* generateStars(float domainSize, float starSize,
										unsigned int count);
		}
	}	
}

#endif
