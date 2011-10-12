#ifndef SPUTNIK_COMPONENT_ARCH_HPP
#define SPUTNIK_COMPONENT_ARCH_HPP

#include <kocmoc-core/componentSystem/Object.hpp>

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
		class Arch : public kocmoc::core::componentSystem::Object
		{
		public:
			
			Arch(kocmoc::core::util::Properties* props,
				 unsigned int instanceCount);

			void render(kocmoc::core::renderer::RenderPass pass,
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
