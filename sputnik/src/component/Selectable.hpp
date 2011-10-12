#ifndef SPUTNIK_COMPONENT_SELECTABLE_HPP
#define SPUTNIK_COMPONENT_SELECTABLE_HPP

#include <kocmoc-core/componentSystem/Component.hpp>

#include <glm/glm.hpp>

namespace sputnik
{
	namespace component
	{
		class Selectable : public kocmoc::core::componentSystem::Component
		{
		public:
			void hover(bool isHovering);
			void select(bool isSelected);
			
			/**
			 * Drag the selectable
			 * @param acceleration vector in m/s
			 */
			void drag(glm::vec3 acceleration);
		};
	}
}

#endif