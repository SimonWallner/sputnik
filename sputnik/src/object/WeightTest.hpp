#ifndef SPUTNIK_OBJECT_WEIGHT_TEST_HPP
#define SPUTNIK_OBJECT_WEIGHT_TEST_HPP

#include <kocmoc-core/componentSystem/Object.hpp>
#include <glm/glm.hpp>

#include <scene/SelectableWorld.hpp>

namespace sputnik
{
	namespace object
	{
		class WeightTest : public kocmoc::core::componentSystem::Object
		{
		public: 
			WeightTest(std::string name, kocmoc::core::util::Properties* props,
					   glm::vec3 pos, float mass, scene::SelectableWorld* world);
			
			
		};
	}
}

#endif
