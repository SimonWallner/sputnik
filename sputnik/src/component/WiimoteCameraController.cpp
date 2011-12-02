#include "WiimoteCameraController.hpp"

#include <math.h>

#include <kocmoc-core/math/math.hpp>

using namespace kocmoc::core::input;
using namespace sputnik::component;
using namespace sputnik::input;
using namespace kocmoc::core::types;
using namespace glm;

using kocmoc::core::util::Properties;

WiimoteCameraController::WiimoteCameraController(kocmoc::core::scene::FilmCamera* _camera,
												 input::WiimoteInputManager* inputManager,
												 Properties* props)
	: camera(_camera)
	, pointer(symbolize("wiimote-pointer"))
	, analogStick(symbolize("nunchuck-analog-stick"))
	, nunchuckC(symbolize("nunchuck-C"))
	, nunchuckZ(symbolize("nunchuck-Z"))
	, ic(this)
{
	float deadX = props->getFloat(symbolize("wiimote-dead-zone-x"));
	float deadY = props->getFloat(symbolize("wiimote-dead-zone-y"));
	float nDeadX = props->getFloat(symbolize("nunchuck-dead-zone-x"));
	float nDeadY = props->getFloat(symbolize("nunchuck-dead-zone-y"));
	
	deadZone = vec2(deadX, deadY);
	nDeadZone = vec2(nDeadX, nDeadY);
	
	inputManager->registerWiimoteEventListener(pointer, &ic);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_CURSOR_RELATIVE_X_Y, pointer);
	inputManager->registerWiimoteEventListener(analogStick, &ic);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_NUNCHUCK_ANALOG_X_Y, analogStick);
	
	inputManager->registerButtonEventListener(nunchuckC, &ic);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_BUTTON_C_HELD, nunchuckC);
	inputManager->registerButtonEventListener(nunchuckZ, &ic);
	inputManager->bindWiimoteEvent(WIIMOTE_EVENT_BUTTON_Z_HELD, nunchuckZ);	
}

void WiimoteCameraController::InputCallback::wiimoteAnalogEventCallback(Symbol name,
																	   WiimoteAnalogEvent event)
{
	if (name == p->pointer)
		p->pointerMoved(event.x, event.y);
	
	if (name == p->analogStick)
		p->nunchuckAnalog(event.x, event.y);
}

void WiimoteCameraController::InputCallback::buttonEventCallback(Symbol name,
																 ButtonEvent event)
{
	float rate = 30.0f;
	
	if (name == p->nunchuckC)
		p->camera->dolly(vec3(0, rate, 0) * p->lastDeltaT);
	
	if (name == p->nunchuckZ)
		p->camera->dolly(vec3(0, -rate, 0) * p->lastDeltaT);
	
	UNUSED event;
}

void WiimoteCameraController::nunchuckAnalog(float x, float y)
{
	float mapX = deadZoneMap(x, nDeadZone.x);
	float mapY = deadZoneMap(y, nDeadZone.y);
	
	float rate = 50.0f;
	
	camera->dolly(glm::vec3(accelerate(mapX), 0,accelerate(mapY) ) * lastDeltaT * rate);
}

void WiimoteCameraController::pointerMoved(float x, float y)
{
	float nX = x * 2.0f - 1.0f;
	float nY = y * 2.0f - 1.0f;
	
	float mapX = deadZoneMap(nX, deadZone.x);
	float mapY = deadZoneMap(nY, deadZone.y);
	
	float rateHori = 2.0f;
	float rateVert = 2.0f;
	
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

