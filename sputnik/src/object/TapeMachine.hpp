#ifndef SPUTNIK_OBJECT_TAPE_MACHINE_HPP
#define SPUTNIK_OBJECT_TAPE_MACHINE_HPP

#include <kocmoc-core/componentSystem/Object.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>

#include <scene/SelectableWorld.hpp>
#include <output/MIDIout.hpp>
#include <input/WiimoteInputManager.hpp>

namespace sputnik
{
	namespace object
	{
		class TapeMachine : public kocmoc::core::componentSystem::Object
		{		
		public:
			TapeMachine(std::string name,
					kocmoc::core::util::Properties* props,
					scene::SelectableWorld* world,
					output::MIDIOut* mOut,
					unsigned int cc,
					std::string modelName = "sphere3-model-name");
			
			void setPosition(glm::vec3 position)
			{
				objectBehaviour->position = position;
			}
			
			void setRotation(glm::quat rotation)
			{
				objectBehaviour->rotation = rotation;
			}
		
		private:
			kocmoc::core::component::ObjectBehaviour* objectBehaviour;
		};
	}
}

#endif