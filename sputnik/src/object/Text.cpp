#include "Text.hpp"

#include <component/TextLabel.hpp>

using namespace sputnik::object;
using namespace sputnik::component;

using namespace kocmoc::core::component;

Text::Text(kocmoc::core::util::Properties* props,
		   std::string text)
	: Object(text, props)
{
	ob = new ObjectBehaviour();
	addComponent(ob);
	
	TextLabel* textLabel = new TextLabel(props, text);
	addComponent(textLabel);
	registerRenderReceiver(textLabel);
	registerUpdateReceiver(textLabel);
	
	initComponents();
}
