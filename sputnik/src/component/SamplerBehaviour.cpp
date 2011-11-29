#include "SamplerBehaviour.hpp"

#include <scene/Selectable.hpp>

using namespace sputnik::component;
using namespace sputnik::scene;

using namespace kocmoc::core::component;
using namespace kocmoc::core;
using namespace kocmoc::core::types;
using namespace kocmoc::core::input;

using glm::vec3;

SamplerBehaviour::SamplerBehaviour(SelectableWorld* world,
								   input::WiimoteInputManager* inputManager,
								   output::MIDIOut* _mOut,
								   unsigned int _cc)
	: Selectable(3.0f)
	, isHovering(false)
	, isSelected(false)
	, play(symbolize("sampler-play"))
	, mOut(_mOut)
	, cc(_cc)
{
	world->add(this);
	inputManager->registerButtonEventListener(play, this);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_BUTTON_A_PRESSED, play);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_BUTTON_A_RELEASED, play);
}

void SamplerBehaviour::init()
{
	ob = parent->getComponent<ObjectBehaviour>();
}

void SamplerBehaviour::onUpdate(float deltaT, float t)
{
	
	if (isSelected)
	{
		ob->scale = vec3(1.5f);
	}
	else
	{	
		if (isHovering)
			ob->scale = vec3(1.2f);
		else
			ob->scale = vec3(1.0f);
	}

	UNUSED deltaT;
	UNUSED t;
}

void SamplerBehaviour::setHovering(bool isHovering)
{
	this->isHovering = isHovering;
}

void SamplerBehaviour::setSelected(bool isSelected)
{
	// output the position to facilitate placement in scene.
	std::cout <<" position: (" << ob->position.x << " | " << ob->position.y << " | " << ob->position.z << ")" << std::endl;

	
	this->isSelected = isSelected;

	if (!isSelected)
	{
		ob->drag = vec3(0);	
		mOut->sendCC(cc, 0.0f);
	}
}

void SamplerBehaviour::drag(vec3 F)
{
	ob->drag += F;
}

glm::vec3 SamplerBehaviour::getPosition() const
{
	return ob->position;
}

void SamplerBehaviour::buttonEventCallback(Symbol name, ButtonEvent event)
{
	if (name == play && event.state == ButtonEvent::PRESSED && isSelected == true)
		mOut->sendCC(cc, 1.0f);
	
	else if (name == play && event.state == ButtonEvent::RELEASED && isSelected == true)
		mOut->sendCC(cc, 0.0f);
}



