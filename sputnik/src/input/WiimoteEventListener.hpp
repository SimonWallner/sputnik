#ifndef SPUTNIK_INPUT_WIIMOTE_EVENT_LISTENER_HPP
#define SPUTNIK_INPUT_WIIMOTE_EVENT_LISTENER_HPP

#include <kocmoc-core/types/Symbol.hpp>

namespace sputnik
{
	namespace input
	{
		struct WiimoteEvent
		{
			unsigned int controlerNumber;
			double value;
			
			WiimoteEvent(unsigned int _controlerNumber, double _value)
				: controlerNumber(_controlerNumber)
				, value(_value)
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
			virtual void wiimoteEventCallback(kocmoc::core::types::Symbol name, WiimoteEvent event) = 0;
		};
	}
}

#endif
