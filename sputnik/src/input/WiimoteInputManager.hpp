#ifndef SPUTNIK_INPUT_WIIMOTE_INPUT_MANAGER
#define SPUTNIK_INPUT_WIIMOTE_INPUT_MANAGER

// symbolic constants for wiimote events
#define WIIMOTE_EVENT_BUTTON_A			0
#define WIIMOTE_EVENT_BUTTON_B			1
#define WIIMOTE_EVENT_BUTTON_1			2
#define WIIMOTE_EVENT_BUTTON_2			3
#define WIIMOTE_EVENT_BUTTON_MINUS		4
#define WIIMOTE_EVENT_BUTTON_PLUS		5
#define WIIMOTE_EVENT_BUTTON_LEFT		6
#define WIIMOTE_EVENT_BUTTON_RIGHT		7
#define WIIMOTE_EVENT_BUTTON_UP			8
#define WIIMOTE_EVENT_BUTTON_DOWN		9
#define WIIMOTE_EVENT_BUTTON_HOME		10

#define	WIIMOTE_EVENT_CURSOR_RELATIVE_X		101
#define	WIIMOTE_EVENT_CURSOR_RELATIVE_Y		102


#include <wiic/wiicpp.h>

#include <kocmoc-core/input/InputManager.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/input/AnalogEventListener.hpp>


#include <input/WiimoteEventListener.hpp>

namespace sputnik
{
	namespace input
	{
		class WiimoteInputManager : public kocmoc::core::input::InputManager
		{
		public:
			WiimoteInputManager(GLFWwindow);
			
			/**
			 * register a callback, for a given name.
			 */
			void registerWiimoteEventListener(kocmoc::core::types::Symbol name, WiimoteEventListener* listener)
			{
				wiimoteEventListeners.insert(WiimoteEventPair(name, listener));
			}
			
			/**
			 * Bind a wiimote event to a name.
			 */
			void bindWiimoteEvent(int wiimoteEventSymbolicConstant, kocmoc::core::types::Symbol name)
			{
				wiimoteEventBindings.insert(WiimoteBindingPair(wiimoteEventSymbolicConstant, name));
			}
			
			/**
			 * poll the wiimotes and fire the callbacks
			 */
			void pollWiimote(void);
			
			/**
			 * dumpt the bindings
			 */
			void dumpBindings(void);
			
		private:
			typedef std::multimap<kocmoc::core::types::Symbol, WiimoteEventListener* > WiimoteEventListenerMultiMap;
			typedef std::pair<kocmoc::core::types::Symbol, WiimoteEventListener* > WiimoteEventPair;
			typedef std::multimap<int, kocmoc::core::types::Symbol> WiimoteBindings;
			typedef std::pair<int, kocmoc::core::types::Symbol> WiimoteBindingPair;
			
			WiimoteEventListenerMultiMap wiimoteEventListeners;
			WiimoteBindings wiimoteEventBindings;
			
			CWii wii; // Defaults to 4 remotes
			std::vector<CWiimote>* wiimotes;
			
			void handleEvent(CWiimote& wiimote, unsigned int controllerNumber);
			void handleStatus(CWiimote& wiimote, unsigned int controllerNumber);
			
			void notifyButtonListeners(int wiimoteEventSymbolicConstant,
									   kocmoc::core::input::ButtonEvent event,
									   unsigned int controllerNumber);
			void notifyAnalogListeners(int wiimoteEventSymbolicConstant,
									  kocmoc::core::input::AnalogEvent event,
									  unsigned int controllerNumber);
		};
	}
}

#endif
