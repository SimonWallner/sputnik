#ifndef SPUTNIK_COMPONENT_TEXT_LABEL_HPP
#define SPUTNIK_COMPONENT_TEXT_LABEL_HPP

#include <string>

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/gl.h>
#include <kocmoc-core/component/PointSprite.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>
#include <kocmoc-core/util/Properties.hpp>

namespace sputnik
{
	namespace component
	{
		class TextLabel : public kocmoc::core::componentSystem::Component
		{
		public:
			TextLabel(kocmoc::core::util::Properties* _props, std::string _text)
				: props(_props)			
				, text(_text)
			{}
			
			void init();
			void onRender(kocmoc::core::renderer::RenderPass pass,
						  kocmoc::core::scene::Camera* camera);
			void onUpdate(float deltaT, float t);
			
		private:
			kocmoc::core::util::Properties* props;
			std::string text;
			
			kocmoc::core::component::PointSprite* sprite;
			kocmoc::core::component::ObjectBehaviour* objectBehaviour;
		};
	}
}

#endif
