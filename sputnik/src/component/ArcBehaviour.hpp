#ifndef SPUTNIK_COMPONENT_ARC_BEHAVIOUR_HPP
#define SPUTNIK_COMPONENT_ARC_BEHAVIOUR_HPP

#include <kocmoc-core/componentSystem/Component.hpp>

#include <glm/glm.hpp>

#include <input/WiimoteInputManager.hpp>

namespace kocmoc
{
	namespace core
	{
		namespace renderer
		{
			class RenderMesh;
		}
		
		namespace util
		{
			class Properties;
		}
	}
}

namespace sputnik
{
	namespace component
	{
		class ArcBehaviour : public kocmoc::core::componentSystem::Component
		{
		public:
			
			ArcBehaviour(kocmoc::core::util::Properties* props,
				 unsigned int instanceCount);

			void onRender(kocmoc::core::renderer::RenderPass pass,
						kocmoc::core::scene::Camera* camera);
			
			void init();
			
			void setStart(glm::vec3 _start)
			{
				start = _start;
			}
			
			void setEnd(glm::vec3 _end)
			{
				end = _end;
			}
		
		private:
			kocmoc::core::renderer::RenderMesh* instancedMesh;
			kocmoc::core::util::Properties* props;
			unsigned int instanceCount;
			glm::vec3 start, end;
			
			class InputCallback : public input::WiimoteEventListener
			{
			public:
				InputCallback(ArcBehaviour* _p)
					: p(_p)
				{}
				
				void wiimoteAnalogEventCallback(kocmoc::core::types::Symbol name, input::WiimoteAnalogEvent event) {}
				void wiimoteButtonEventCallback(kocmoc::core::types::Symbol name, input::WiimoteButtonEvent event) {}
				
			private:
				ArcBehaviour* p;
			} ic;
		};
	}
}

#endif
