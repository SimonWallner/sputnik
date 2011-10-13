#include "Selectable.hpp"

using namespace sputnik::component;
using namespace kocmoc::core::component;

void Selectable::init()
{
	objectBehaviour = parent->getComponent<ObjectBehaviour>();
}