#ifndef SPUTNIK_INPUT_WIIMOTE_INPUT_MANAGER
#define SPUTNIK_INPUT_WIIMOTE_INPUT_MANAGER

#include <kocmoc-core/input/InputManager.hpp>

namespace sputnik
{
	namespace input
	{
		class WiimoteInputManager : public kocmoc::core::input::InputManager
		{
		public:
//			void registerWiimoteEventListener(kocmoc::core::types::Symbol name, WiiEventListener* lisener);
			void bindWiimoteEvent(int wiimoteEventSymbolicConstant, kocmoc::core::types::Symbol name);
			void pollWiimote(void);
			
			void dumpBindings(void);
		};
	}
}

#endif
