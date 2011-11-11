#ifndef SPUTNIK_COMPONENT_WIIMOTE_DEBUGGER_HPP
#define SPUTNIK_COMPONENT_WIIMOTE_DEBUGGER_HPP

#include <kocmoc-core/componentSystem/Object.hpp>
#include <kocmoc-core/component/OverlayQuad.hpp>

#include <input/WiimoteInputManager.hpp>
#include <input/WiimoteEventListener.hpp>

namespace sputnik
{
	namespace component
	{
		class WiimoteDebugger : public kocmoc::core::componentSystem::Object
		{
		public:
			WiimoteDebugger(std::string name, kocmoc::core::util::Properties* props,
							sputnik::input::WiimoteInputManager* _inputManager,
							unsigned int controllerNumber);
			
			void init(void);
		private:
			input::WiimoteInputManager* inputManager;
			kocmoc::core::component::OverlayQuad* markers[4];
			kocmoc::core::component::OverlayQuad* cursor;
			kocmoc::core::types::Symbol dot0, dot1, dot2, dot3, cursorSymbol;
			unsigned int controllerNumber;
			unsigned int frameWidth, frameHeight;
			
			class InputCallback : public input::WiimoteEventListener
			{
			public:
				InputCallback(WiimoteDebugger* _p)
				{
					p = _p;
				}
				
				void wiimoteAnalogEventCallback(kocmoc::core::types::Symbol name, input::WiimoteAnalogEvent event);
				void wiimoteButtonEventCallback(kocmoc::core::types::Symbol name, input::WiimoteButtonEvent event)
				{
					UNUSED name;
					UNUSED event;
				}
				
			private:
				WiimoteDebugger* p;
			} ic;
		};
	}
}

#endif
