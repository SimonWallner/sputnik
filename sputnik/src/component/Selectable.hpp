#ifndef SPUTNIK_COMPONENT_SELECTABLE_HPP
#define SPUTNIK_COMPONENT_SELECTABLE_HPP

#include <scene/Selectable.hpp>
#include <kocmoc-core/componentSystem/Component.hpp>

namespace sputnik
{
	namespace component
	{
		class Selectable : public kocmoc::core::componentSystem::Component
						 , public scene::Selectable
		{
		public:
			Selectable(unsigned int radius)
				: scene::Selectable(radius)
			{}
			
			void init()
			{
				ob = parent->getComponent<kocmoc::core::component::ObjectBehaviour>();
			}
			
			float getIsHovering() {return isHovering;}
			float getIsSelected() {return isSelected;}
			
			glm::vec3 getPosition() const
			{
				return ob->position;
			}
			
			void drag(glm::vec3 F)
			{
				ob->drag = F;
			}
			
		private:
			kocmoc::core::component::ObjectBehaviour* ob;
			bool isHovering;
			bool isSelected;
		};
	}
}

#endif
