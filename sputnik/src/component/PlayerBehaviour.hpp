#ifndef SPUTNIK_COMPONENT_PLAYER_BEHAVIOUR_HPP
#define SPUTNIK_COMPONENT_PLAYER_BEHAVIOUR_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>

#include <scene/Selectable.hpp>
#include <scene/SelectableWorld.hpp>
#include <input/WiimoteInputManager.hpp>
#include <output/MIDIOut.hpp>

namespace sputnik
{
	namespace component
	{
		class PlayerBehaviour : public kocmoc::core::componentSystem::Component
							  , public scene::Selectable
							  , public kocmoc::core::input::ButtonEventListener
		{
		public:
			PlayerBehaviour(scene::SelectableWorld* world,
							 input::WiimoteInputManager* inputManager,
							 output::MIDIOut*,
							 unsigned int _cc);
			void init();
			void onUpdate(float deltaT, float t);
			
			// selectable interface
			void setHovering(bool isHovering);
			void setSelected(bool isSelected);
			void drag(glm::vec3 F);
			glm::vec3 getPosition() const;
			
			// button event
			void buttonEventCallback(kocmoc::core::types::Symbol name, kocmoc::core::input::ButtonEvent event);

		private:
			kocmoc::core::component::ObjectBehaviour* ob;
			bool isHovering;
			bool isSelected;
			
			kocmoc::core::types::Symbol play;
			
			output::MIDIOut* mOut;
			unsigned int cc;
			
			bool playing;
		};
	}
}

#endif
