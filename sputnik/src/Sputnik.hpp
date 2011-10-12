//  Created by Simon Wallner on 28.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef SPUTNIK_SPUTNIK_HPP
#define SPUTNIK_SPUTNIK_HPP

#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/scene/ImageLoader.hpp>
#include <kocmoc-core/renderer/Context.hpp>

#include <input/WiimoteInputManager.hpp>

#include "component/Monkey.hpp"

namespace kocmoc
{
	namespace core
	{
		namespace util
		{
			class Properties;
		}
	}
}

namespace sputnik
{
	
	/**
	 * The main game class. It is created in main() and does everything from
	 * there.
	 */
	class Sputnik
	{
	public:
		
		/**
		 * Create a new kocmoc.
		 * @param props basic properties with all relevant startup information
		 *			like command line arguments and so on
		 */
		Sputnik(kocmoc::core::util::Properties* props);
		Sputnik();
		~Sputnik();
		
		/**
		 * print the awesome ASCII art intro.
		 */
		void printIntro();

	private:
		kocmoc::core::renderer::Context* context;
		kocmoc::core::util::Properties* props;
		bool running;
		kocmoc::core::types::Symbol quit, screenShot, note, cursorX, cursorY;
		
		component::Monkey* monkey;
		kocmoc::core::scene::ImageLoader imageLoader;
		
		class InputCallback : public kocmoc::core::input::ButtonEventListener, public input::WiimoteEventListener
		{
		public:
			InputCallback(Sputnik* _p)
			: p(_p)
			{};
			
			void buttonEventCallback(kocmoc::core::types::Symbol name, kocmoc::core::input::ButtonEvent event)
			{
				if (name == p->quit && event.isPressed == true)
					p->running = false;
				else if (name == p->screenShot && event.isPressed == true)
					p->imageLoader.screenShot();
			}
			
			void wiimoteAnalogEventCallback(kocmoc::core::types::Symbol name, input::WiimoteAnalogEvent event)
			{
//				GLFWwindow windowHadle = p->context->getWindowHandle();
//				if (name == p->cursorX)
//					glfwSetMousePos(windowHadle, event.x * 720.0f, event.y * 400);
			}
			
			void wiimoteButtonEventCallback(kocmoc::core::types::Symbol name, input::WiimoteButtonEvent event)
			{}
			
		private:
			Sputnik* p;
		} ic;
		
		output::MIDIOut midiOut;

	};
}

#endif
