#ifndef SPUTNIK_SCENE_SELECTABLE_WORLD_HPP
#define SPUTNIK_SCENE_SELECTABLE_WORLD_HPP

#include <component/Selectable.hpp>

#include <vector>

namespace sputnik
{
	namespace scene
	{
		class SelectableWorld
		{
		public:
			/**
			 * Add selectable object to the world
			 */
			void add(component::Selectable* selectable)
			{
				world.push_back(selectable);
			}
			
			/**
			 * intersect world object with a ray
			 * @return the instersecting object that hast the smallest positive
			 *	distance from the startPoint and is not further away than
			 *	endPoint. If no intersectin object is found NULL is returned
			 */
			component::Selectable* rayIntersction(glm::vec3 startPoint,
												  glm::vec3 endPoint);
			
		private:
			typedef std::vector<component::Selectable* > SelectableList;
			SelectableList world;
		};
	}
}

#endif
