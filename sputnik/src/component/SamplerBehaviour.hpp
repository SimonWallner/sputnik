#ifndef SPUTNIK_COMPONENT_SAMPLER_BEHAVIOUR_HPP
#define SPUTNIK_COMPONENT_SAMPLER_BEHAVIOUR_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>

#include <component/Selectable.hpp>

namespace sputnik
{
	namespace component
	{
		class SamplerBehaviour : public kocmoc::core::componentSystem::Component
		{
		public:
			void init();
			void onUpdate(float deltaT, float t);
			
		private:
			kocmoc::core::component::ObjectBehaviour* ob;
			Selectable* selectable;
		};
	}
}


#endif