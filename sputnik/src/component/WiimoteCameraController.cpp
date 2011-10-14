#include "WiimoteCameraController.hpp"

#include <math.h>

#include <kocmoc-core/math/math.hpp>

using namespace sputnik::component;
using namespace sputnik::input;
using namespace kocmoc::core::types;
using namespace glm;

using kocmoc::core::util::Properties;

WiimoteCameraController::WiimoteCameraController(kocmoc::core::scene::FilmCamera* _camera,
												 input::WiimoteInputManager* inputManager,
												 Properties* props)
	: camera(_camera)
	, ic(this)
{
	float deadX = props->getFloat(symbolize("wiimote-dead-zone-x"));
	float deadY = props->getFloat(symbolize("wiimote-dead-zone-y"));
	
	deadZone = vec2(deadX, deadY);
	
	inputManager->registerWiimoteEventListener(pointer, &ic);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_CURSOR_RELATIVE_X_Y, pointer);
}

void WiimoteCameraController::InputCallback::wiimoteAnalogEventCallback(Symbol name,
																	   WiimoteAnalogEvent event)
{
	if (name == p-> pointer)
		p->pointerMoved(event.x, event.y);
}

void WiimoteCameraController::pointerMoved(float x, float y)
{
	float nX = x * 2.0f - 1.0f;
	float nY = y * 2.0f - 1.0f;
	
	float mapX = deadZoneMap(nX, deadZone.x);
	float mapY = deadZoneMap(nY, deadZone.y);
	
	float rateHori = 1.0f;
	float rateVert = 1.0f;
	
	camera->tumble(lastDeltaT * rateHori * accelerate(mapX),
				   lastDeltaT * rateVert * accelerate(mapY));
}

float WiimoteCameraController::deadZoneMap(float value, float dead)
{
	if (value < -dead)
		return (value + dead) / (1.0f - dead);
	
	if (value > dead)
		return (value - dead) / (1.0f - dead);
	
	return 0.0f;
}

float WiimoteCameraController::accelerate(float value)
{
	return pow(value, 2.0f) * kocmoc::core::math::sign(value);
}

