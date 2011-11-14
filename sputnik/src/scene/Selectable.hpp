#ifndef SPUTNIK_SCENE_SELECTABLE_HPP
#define SPUTNIK_SCENE_SELECTABLE_HPP
#include <glm/glm.hpp>
#include <kocmoc-core/compiler.h>

namespace sputnik
{
	namespace scene
	{
		/**
		 * A selectable object interface with a boundith sphere.
		 * Implement at any object that needs to be selected.
		 */
		class Selectable
		{
		public:
			/**
			 * create a new selectable with the given diameter.
			 */
			Selectable(float _radius)
				: radius(_radius)
			{}
			
			virtual void setHovering(bool isHovering) {UNUSED isHovering;}
			virtual void setSelected(bool isSelected) {UNUSED isSelected;}

			
			/**
			 * Drag the selectable
			 * @param F dragging force in newton
			 */
			virtual void drag(glm::vec3 F) {UNUSED F;}
			virtual glm::vec3 getPosition() const = 0;

			float getRadius() const
			{
				return radius;
			}
			
		private:
			/**
			 * radious of the bounding sphere
			 */
			float radius;
		};
	}
}

#endif