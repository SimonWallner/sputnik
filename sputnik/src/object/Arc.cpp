#include "Arc.hpp"

#include <kocmoc-core/util/Properties.hpp>

using namespace sputnik::object;
using namespace sputnik::component;

using kocmoc::core::util::Properties;

Arc::Arc(Properties* props, input::WiimoteInputManager* inputManager,
		 kocmoc::core::scene::FilmCamera* camera,
		 scene::SelectableWorld* world)
	: Object("Arc", props)
{
	ArcBehaviour* behaviour = new ArcBehaviour(props, 1000, inputManager, camera, world);
	addComponent(behaviour);
	registerRenderReceiver(behaviour);
	
	initComponents();
}