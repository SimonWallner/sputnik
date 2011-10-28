#ifndef SPUTNIK_OBJECT_STAR_FIELD_HPP
#define SPUTNIK_OBJECT_STAR_FIELD_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/renderer/RenderMesh21.hpp>

namespace sputnik
{
	namespace component
	{
		class StarField : public kocmoc::core::componentSystem::Component
		{
		public:
			StarField(kocmoc::core::util::Properties* _props)
				: props(_props)
			{}
			
			void init();
			
			void onRender(kocmoc::core::renderer::RenderPass pass,
						  kocmoc::core::scene::Camera* camera);
			
		private:
			kocmoc::core::util::Properties* props;
			kocmoc::core::renderer::RenderMesh21* mesh;
		};
	}
}

#endif
