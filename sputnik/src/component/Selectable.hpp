#ifndef SPUTNIK_COMPONENT_SELECTABLE_HPP
#define SPUTNIK_COMPONENT_SELECTABLE_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>

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
				: radius(_radius)
				, selected(false)
				, hovering(false)
			{}
			
			void init();
			
			inline void setHovering(bool isHovering)
			{
				hovering = isHovering;
			}
			
			inline void setSelected(bool isSelected)
			{
				selected = isSelected;
			}
			
			inline bool isSelected() {return selected;}
			inline bool isHovering() {return hovering;}
			
			/**
			 * Drag the selectable
			 * @param acceleration vector in m/s
			 */
			void drag(glm::vec3 acceleration);
			
			glm::vec3 getPosition() const
			{
				return objectBehaviour->position;
			}
			
			float getRadius() const
			{
				return radius;
			}
			
		private:
			/**
			 * radious of the bounding sphere
			 */
			float radius;
			kocmoc::core::component::ObjectBehaviour* objectBehaviour;
			
			bool selected;
			bool hovering;
		};
	}
}

#endif