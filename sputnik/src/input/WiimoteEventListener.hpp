#ifndef SPUTNIK_INPUT_WIIMOTE_EVENT_LISTENER_HPP
#define SPUTNIK_INPUT_WIIMOTE_EVENT_LISTENER_HPP

#include <kocmoc-core/types/Symbol.hpp>

namespace sputnik
{
	namespace input
	{
		struct WiimoteAnalogEvent
		{
			unsigned int controlerNumber;
			double value;
			
			WiimoteAnalogEvent(unsigned int _controlerNumber, double _value)
				: controlerNumber(_controlerNumber)
				, value(_value)
			{}
		};

		struct WiimoteButtonEvent
		{
			unsigned int controlerNumber;
			bool isPressed;
			
			WiimoteButtonEvent(unsigned int _controlerNumber, bool _isPressed)
			: controlerNumber(_controlerNumber)
			, isPressed(_isPressed)
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
