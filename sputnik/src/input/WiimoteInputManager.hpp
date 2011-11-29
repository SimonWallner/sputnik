#ifndef SPUTNIK_INPUT_WIIMOTE_INPUT_MANAGER
#define SPUTNIK_INPUT_WIIMOTE_INPUT_MANAGER

// symbolic constants for wiimote events
#define WIIMOTE_EVENT_BUTTON_A_PRESSED			0
#define WIIMOTE_EVENT_BUTTON_B_PRESSED			1
#define WIIMOTE_EVENT_BUTTON_1_PRESSED			2
#define WIIMOTE_EVENT_BUTTON_2_PRESSED			3
#define WIIMOTE_EVENT_BUTTON_MINUS_PRESSED		4
#define WIIMOTE_EVENT_BUTTON_PLUS_PRESSED		5
#define WIIMOTE_EVENT_BUTTON_LEFT_PRESSED		6
#define WIIMOTE_EVENT_BUTTON_RIGHT_PRESSED		7
#define WIIMOTE_EVENT_BUTTON_UP_PRESSED			8
#define WIIMOTE_EVENT_BUTTON_DOWN_PRESSED		9
#define WIIMOTE_EVENT_BUTTON_HOME_PRESSED		10
#define WIIMOTE_EVENT_BUTTON_Z_PRESSED			11
#define WIIMOTE_EVENT_BUTTON_C_PRESSED			12

#define WIIMOTE_EVENT_BUTTON_A_RELEASED			20
#define WIIMOTE_EVENT_BUTTON_B_RELEASED			21
#define WIIMOTE_EVENT_BUTTON_1_RELEASED			22
#define WIIMOTE_EVENT_BUTTON_2_RELEASED			23
#define WIIMOTE_EVENT_BUTTON_MINUS_RELEASED		24
#define WIIMOTE_EVENT_BUTTON_PLUS_RELEASED		25
#define WIIMOTE_EVENT_BUTTON_LEFT_RELEASED		26
#define WIIMOTE_EVENT_BUTTON_RIGHT_RELEASED		27
#define WIIMOTE_EVENT_BUTTON_UP_RELEASED		28
#define WIIMOTE_EVENT_BUTTON_DOWN_RELEASED		29
#define WIIMOTE_EVENT_BUTTON_HOME_RELEASED		30
#define WIIMOTE_EVENT_BUTTON_Z_RELEASED			31
#define WIIMOTE_EVENT_BUTTON_C_RELEASED			32

#define WIIMOTE_EVENT_BUTTON_A_HELD			40
#define WIIMOTE_EVENT_BUTTON_B_HELD			41
#define WIIMOTE_EVENT_BUTTON_1_HELD			42
#define WIIMOTE_EVENT_BUTTON_2_HELD			43
#define WIIMOTE_EVENT_BUTTON_MINUS_HELD		44
#define WIIMOTE_EVENT_BUTTON_PLUS_HELD		45
#define WIIMOTE_EVENT_BUTTON_LEFT_HELD		46
#define WIIMOTE_EVENT_BUTTON_RIGHT_HELD		47
#define WIIMOTE_EVENT_BUTTON_UP_HELD		48
#define WIIMOTE_EVENT_BUTTON_DOWN_HELD		49
#define WIIMOTE_EVENT_BUTTON_HOME_HELD		50
#define WIIMOTE_EVENT_BUTTON_Z_HELD			51
#define WIIMOTE_EVENT_BUTTON_C_HELD			52


#define	WIIMOTE_EVENT_CURSOR_RELATIVE_X_Y	100
#define WIIMOTE_EVENT_DOT_0_X_Y_SIZE		101
#define WIIMOTE_EVENT_DOT_1_X_Y_SIZE		102
#define WIIMOTE_EVENT_DOT_2_X_Y_SIZE		103
#define WIIMOTE_EVENT_DOT_3_X_Y_SIZE		104

#define	WIIMOTE_EVENT_NUNCHUCK_ANALOG_X_Y	110


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
			
			~WiimoteInputManager();
			
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
			void bindWiimoteEvent(int wiimoteEventSymbolicConstant, kocmoc::core::types::Symbol name);
			
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
			
			CWii* wii; // Defaults to 4 remotes
			std::vector<CWiimote> wiimotes;
			
			float lastPointerX, lastPointerY;
			
			void handleEvent(CWiimote& wiimote, unsigned int controllerNumber);
			void handleStatus(CWiimote& wiimote, unsigned int controllerNumber);
			
			void notifyButtonListeners(int wiimoteEventSymbolicConstant,
									   kocmoc::core::input::ButtonEvent event,
									   unsigned int controllerNumber);
			void notifyAnalogListeners(int wiimoteEventSymbolicConstant,
									   WiimoteAnalogEvent event);
			// enable or disable IR tracking on the fly, to avoid spinning
			bool trackIR;
		};
	}
}

#endif
