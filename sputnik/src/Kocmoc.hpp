//
//  Kocmoc.hpp
//  kocmoc
//
//  Created by Simon Wallner on 28.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KOCMOC_KOCMOC_HPP
#define KOCMOC_KOCMOC_HPP

#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/scene/ImageLoader.hpp>

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
	
	/**
	 * The main game class. It is created in main() and does everything from
	 * there.
	 */
	class Kocmoc
	{
	public:
		
		/**
		 * Create a new kocmoc.
		 * @param props basic properties with all relevant startup information
		 *			like command line arguments and so on
		 */
		Kocmoc(core::util::Properties* props);
		~Kocmoc(void);
		
		/**
		 * print the awesome ASCII art intro.
		 */
		void printIntro(void);

	private:
		core::util::Properties* props;
		bool running;
		core::types::Symbol quit, screenShot;
		
		component::Ship* ship;
		core::scene::ImageLoader imageLoader;
		
		class KeyWatcher : public core::input::ButtonEventListener
		{
		public:
			KeyWatcher(Kocmoc* _p)
			: p(_p)
			{};
			
			void buttonEventCallback(core::types::Symbol name, core::input::ButtonEvent event)
			{
				if (name == p->quit && event.isPressed == true)
					p->running = false;
				else if (name == p->screenShot && event.isPressed == true)
					p->imageLoader.screenShot();
			}
		private:
			Kocmoc* p;
		} kw;
		
		void init(void);
	};
}

#endif
