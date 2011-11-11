#ifndef SPUTNIK_COMPONENT_WIIMOTE_CAMERA_CONTROLLER_HPP
#define SPUTNIK_COMPONENT_WIIMOTE_CAMERA_CONTROLLER_HPP

#include <iostream>

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/scene/FilmCamera.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>

#include <input/WiimoteInputManager.hpp>
#include <input/WiimoteEventListener.hpp>


namespace sputnik
{
	namespace component
	{
		/**
		 * Camera controller class that takes user input and moves the camera
		 * accordingly.
		 */
		class WiimoteCameraController : public kocmoc::core::componentSystem::Component
		{
		public:
			WiimoteCameraController(kocmoc::core::scene::FilmCamera* _camera,
									input::WiimoteInputManager* inputManager,
									kocmoc::core::util::Properties* props);
			
			void onUpdate(const float deltaT)
			{
				lastDeltaT = deltaT;
			}
			
		private:
			kocmoc::core::scene::FilmCamera* camera;
			
			kocmoc::core::types::Symbol pointer, analogStick, nunchuckC, nunchuckZ;
			
			float lastDeltaT;
			
			glm::vec2 deadZone;
			glm::vec2 nDeadZone;
			
			/**
			 * the pointer moved to the given position in [0, 1]x[0, 1]
			 */
			void pointerMoved(float x, float y);
			void nunchuckAnalog(float x, float y);
			
			/**
			 * Map a value to the dead zone
			 *
			 * 1							/
			 * |						   /
			 * |						  /
			 * |	 |<   dead zone  >|  /
			 * |-1 ----------- 0 -----------1
			 * |	 /
			 * |    /
			 * |   /
			 * -1 /
			 *
			 * @param value [-1, 1]
			 * @param dead positive deadzone value in [0, 1]
			 */
			float deadZoneMap(float value, float dead);
			
			/**
			 * acceleration maping function
			 * @param value in [-1, 1]
			 * @return [-1, 1]
			 */
			float accelerate(float value);
			
			
			class InputCallback : public input::WiimoteEventListener, public kocmoc::core::input::ButtonEventListener
			{
			public:
				InputCallback(WiimoteCameraController* _p)
					: p(_p)
				{}
				
				void wiimoteAnalogEventCallback(kocmoc::core::types::Symbol name, input::WiimoteAnalogEvent event);
				void wiimoteButtonEventCallback(kocmoc::core::types::Symbol name, input::WiimoteButtonEvent event)
				{
					UNUSED name;
					UNUSED event;
				}
				void buttonEventCallback(kocmoc::core::types::Symbol name, kocmoc::core::input::ButtonEvent event);
				
			private:
				WiimoteCameraController* p;
			} ic;
		};
	}
}

#endif
