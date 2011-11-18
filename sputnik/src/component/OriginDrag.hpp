#ifndef SPUTNIK_COMPONENT_ORIGIN_DRAG_HPP
#define SPUTNIK_COMPONENT_ORIGIN_DRAG_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>

#include <glm/glm.hpp>

namespace sputnik
{
	namespace component
	{
		/**
		 * Simple component/behaviour that pulls the object towards a fixed
		 * origin
		 */
		class OriginDrag : public kocmoc::core::componentSystem::Component
		{
		public:
			OriginDrag(glm::vec3 origin, float _force = 1.0f);

			glm::vec3 origin;
			float force;
			
			void init();
			void onUpdate(float deltaT, float t);

		private:
			kocmoc::core::component::ObjectBehaviour* ob;
		};
	}
}


#endif
