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
			void add(component::Selectable* selectable)
			{
				world.push_back(selectable);
			}
			
			component::Selectable* rayIntersction(glm::vec3 startPoint,
												  glm::vec3 endPoint);
			
		private:
			typedef std::vector<component::Selectable* > SelectableList;
			SelectableList world;
		};
	}
}

#endif
