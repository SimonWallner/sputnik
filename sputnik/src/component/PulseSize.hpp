#ifndef SPUTNIK_COMPONENT_PULSE_SIZE
#define SPUTNIK_COMPONENT_PULSE_SIZE

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>
#include <kocmoc-core/math/math.hpp>

namespace sputnik
{
	namespace component
	{
		class PulseSize : public kocmoc::core::componentSystem::Component
		{
		public:
			PulseSize(float _minSize, float _maxSize, float _f, float _phase = 0)
				: minSize(_minSize)
				, maxSize(_maxSize)
				, f(_f)
				, phase(_phase)
			{}
			
			void init()
			{
				ob = parent->getComponent<kocmoc::core::component::ObjectBehaviour>();
			}
			
			void onUpdate(float deltaT, float t)
			{
				float q = (sin(t * 2 * kocmoc::core::math::pi * f - phase) + 1 ) * 0.5;
				float size = minSize + pow(q, 2.0f) * (maxSize - minSize);
				ob->scale = glm::vec3(size);

				UNUSED deltaT;
			}
			
		private:
			kocmoc::core::component::ObjectBehaviour* ob;
			float minSize;
			float maxSize;
			float f;
			float phase;

		};
	}
}

#endif
