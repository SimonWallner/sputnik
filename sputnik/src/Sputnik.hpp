//  Created by Simon Wallner on 28.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef SPUTNIK_SPUTNIK_HPP
#define SPUTNIK_SPUTNIK_HPP

#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/scene/ImageLoader.hpp>

#include <output/MIDIOut.hpp>

#include "component/Ship.hpp"

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
		Sputnik(void);
		~Sputnik(void);
		
		/**
		 * print the awesome ASCII art intro.
		 */
		void printIntro(void);

	private:
		kocmoc::core::util::Properties* props;
		bool running;
		kocmoc::core::types::Symbol quit, screenShot, note;
		
		component::Ship* ship;
		kocmoc::core::scene::ImageLoader imageLoader;
		
		class InputCallback : public kocmoc::core::input::ButtonEventListener
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
				else if (name == p->note && event.isPressed == true)
				{
					p->midiOut.sendCC(12, 99999);
					p->midiOut.sendNote(21, -42);
				}
			}
		private:
			Sputnik* p;
		} ic;
		
		void init(void);
		
		output::MIDIOut midiOut;

	};
}

#endif
