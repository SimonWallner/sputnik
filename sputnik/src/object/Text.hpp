#ifndef SPUTNIK_OBJECT_TEXT_HPP
#define SPUTNIK_OBJECT_TEXT_HPP

#include <kocmoc-core/componentSystem/Object.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>

namespace sputnik
{
	namespace object
	{
		class Text : public kocmoc::core::componentSystem::Object
		{
		public:
			Text(kocmoc::core::util::Properties* props,
				 std::string text);
			
			void setPosition(glm::vec3 position)
			{
				ob->position = position;
			}
			
			void setRotation(glm::quat rotation)
			{
				ob->rotation = rotation;
			}
			
		private:
			kocmoc::core::component::ObjectBehaviour* ob;
		};
	}
}

#endif
