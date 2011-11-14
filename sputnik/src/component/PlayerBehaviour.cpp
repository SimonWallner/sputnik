#include "PlayerBehaviour.hpp"

using namespace sputnik::component;
using namespace sputnik::scene;

using namespace kocmoc::core::component;
using namespace kocmoc::core;
using namespace kocmoc::core::types;
using namespace kocmoc::core::input;

using glm::vec3;

PlayerBehaviour::PlayerBehaviour(SelectableWorld* world,
								   input::WiimoteInputManager* inputManager,
								   output::MIDIOut* _mOut,
								   unsigned int _cc)
	: Selectable(3.0f)
	, isHovering(false)
	, isSelected(false)
	, play(symbolize("player-play"))
	, mOut(_mOut)
	, cc(_cc)
	, playing(false)
{
	world->add(this);
	inputManager->registerButtonEventListener(play, this);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_BUTTON_A_PRESSED, play);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_BUTTON_A_RELEASED, play);
}

void PlayerBehaviour::init()
{
	ob = parent->getComponent<ObjectBehaviour>();
}

void PlayerBehaviour::onUpdate(float deltaT, float t)
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

void PlayerBehaviour::setHovering(bool isHovering)
{
	this->isHovering = isHovering;
}

void PlayerBehaviour::setSelected(bool isSelected)
{
	this->isSelected = isSelected;

	if (!isSelected)
	{
		ob->drag = vec3(0);	
	}
}

void PlayerBehaviour::drag(vec3 F)
{
	ob->drag = F;
}

glm::vec3 PlayerBehaviour::getPosition() const
{
	return ob->position;
}

void PlayerBehaviour::buttonEventCallback(Symbol name, ButtonEvent event)
{
	if (name == play && event.state == ButtonEvent::PRESSED && isSelected == true)
	{
		playing = !playing;
		if (playing)
			mOut->sendCC(cc, 1.0f);
		else
			mOut->sendCC(cc, 0.0f);
	}
}



