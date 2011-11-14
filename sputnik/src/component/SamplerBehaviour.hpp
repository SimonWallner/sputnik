#ifndef SPUTNIK_COMPONENT_SAMPLER_BEHAVIOUR_HPP
#define SPUTNIK_COMPONENT_SAMPLER_BEHAVIOUR_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>

#include <scene/Selectable.hpp>
#include <scene/SelectableWorld.hpp>

namespace sputnik
{
	namespace component
	{
		class SamplerBehaviour : public kocmoc::core::componentSystem::Component
							   , public scene::Selectable
		{
		public:
			SamplerBehaviour(scene::SelectableWorld* world);
			void init();
			void onUpdate(float deltaT, float t);
			
			// selectable interface
			void setHovering(bool isHovering);
			void setSelected(bool isSelected);
			void drag(glm::vec3 F);
			glm::vec3 getPosition() const;

		private:
			kocmoc::core::component::ObjectBehaviour* ob;
			bool isHovering;
			bool isSelected;
		};
	}
}

#endif
