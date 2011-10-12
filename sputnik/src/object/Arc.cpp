#include "Arc.hpp"

#include <kocmoc-core/util/Properties.hpp>

using namespace sputnik::object;
using namespace sputnik::component;

using kocmoc::core::util::Properties;

Arc::Arc(Properties* _props, input::WiimoteInputManager* inputManager)
	: Object("Arc", _props)
{
	behaviour = new ArcBehaviour(props, 100, inputManager);
	addComponent(behaviour);
	registerRenderReceiver(behaviour);
	
	initComponents();
}