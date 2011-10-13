#ifndef SPUTNIK_INPUT_WIIMOTE_EVENT_LISTENER_HPP
#define SPUTNIK_INPUT_WIIMOTE_EVENT_LISTENER_HPP

#include <kocmoc-core/types/Symbol.hpp>

namespace sputnik
{
	namespace input
	{
		/**
		 * Struct for wiimote analog input
		 * @note depending on the event, not all 3 values might be set
		 */
		struct WiimoteAnalogEvent
		{
			unsigned int controlerNumber;
			double x, y, z;
			
			WiimoteAnalogEvent(unsigned int _controlerNumber, double _x, double _y, double _z)
				: controlerNumber(_controlerNumber)
				, x(_x)
				, y(_y)
				, z(_z)
			{}
		};

		struct WiimoteButtonEvent
		{
			unsigned int controlerNumber;
			kocmoc::core::input::ButtonEvent::State state;
			
			WiimoteButtonEvent(unsigned int _controlerNumber,
							   kocmoc::core::input::ButtonEvent::State _state)
				: controlerNumber(_controlerNumber)
				, state(_state)
			{}
		};

		/**
		 * Callback function for the wiimote. The specialty about it is the
		 * added controller number, since we are dealing with more than one
		 * input device (possibly).
		 */
		class WiimoteEventListener
		{
		public:
			virtual void wiimoteAnalogEventCallback(kocmoc::core::types::Symbol name, WiimoteAnalogEvent event) = 0;
			virtual void wiimoteButtonEventCallback(kocmoc::core::types::Symbol name, WiimoteButtonEvent event) = 0;
		};
	}
}

#endif
