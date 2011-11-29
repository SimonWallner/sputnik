#ifndef SPUTNIK_OBJECT_SAMPLER_HPP
#define SPUTNIK_OBJECT_SAMPLER_HPP

#include <kocmoc-core/componentSystem/Object.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>

#include <scene/SelectableWorld.hpp>
#include <output/MIDIout.hpp>
#include <input/WiimoteInputManager.hpp>

namespace sputnik
{
	namespace object
	{
		class Sampler : public kocmoc::core::componentSystem::Object
		{		
		public:
			Sampler(std::string name,
					kocmoc::core::util::Properties* props,
					scene::SelectableWorld* world,
					input::WiimoteInputManager* inputManager,
					output::MIDIOut* mOut,
					unsigned int cc,
					std::string modelName = "sphere1-model-name");
			
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