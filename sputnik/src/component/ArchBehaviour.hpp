#ifndef SPUTNIK_COMPONENT_ARCH_BEHAVIOUR_HPP
#define SPUTNIK_COMPONENT_ARCH_BEHAVIOUR_HPP

#include <kocmoc-core/componentSystem/Component.hpp>

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
		class ArchBehaviour : public kocmoc::core::componentSystem::Component
		{
		public:
			
			ArchBehaviour(kocmoc::core::util::Properties* props,
				 unsigned int instanceCount);

			void onRender(kocmoc::core::renderer::RenderPass pass,
						kocmoc::core::scene::Camera* camera);
			
			void init();
		
		private:
			kocmoc::core::renderer::RenderMesh* instancedMesh;
			kocmoc::core::util::Properties* props;
			unsigned int instanceCount;
		};
	}
}

#endif
