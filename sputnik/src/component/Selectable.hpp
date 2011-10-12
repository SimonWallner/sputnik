#ifndef SPUTNIK_COMPONENT_SELECTABLE_HPP
#define SPUTNIK_COMPONENT_SELECTABLE_HPP

#include <kocmoc-core/componentSystem/Component.hpp>

#include <glm/glm.hpp>

namespace sputnik
{
	namespace component
	{
		/**
		 * A selectable object with a boundith sphere.
		 */
		class Selectable : public kocmoc::core::componentSystem::Component
		{
		public:
			/**
			 * create a new selectable with the given diameter.
			 */
			Selectable(float _radius)
			{
				radius = _radius;
			}
			
			void hover(bool isHovering);
			void select(bool isSelected);
			
			/**
			 * Drag the selectable
			 * @param acceleration vector in m/s
			 */
			void drag(glm::vec3 acceleration);
			
		private:
			/**
			 * radious of the bounding sphere
			 */
			float radius;
		};
	}
}

#endif