#include "Arch.hpp"

#include <kocmoc-core/util/Properties.hpp>

using namespace sputnik::object;
using namespace sputnik::component;

using kocmoc::core::util::Properties;

Arch::Arch(Properties* _props)
	: Object("Arch", _props)
{
	behaviour = new ArchBehaviour(props, 100);
	addComponent(behaviour);
	registerRenderReceiver(behaviour);
	
	initComponents();
}