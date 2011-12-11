//  Created by Simon Wallner on 28.08.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef SPUTNIK_SPUTNIK_HPP
#define SPUTNIK_SPUTNIK_HPP

#include <kocmoc-core/types/Symbol.hpp>
#include <kocmoc-core/input/ButtonEventListener.hpp>
#include <kocmoc-core/scene/ImageLoader.hpp>
#include <kocmoc-core/renderer/Context.hpp>
#include <kocmoc-core/scene/AssetLoader.hpp>
#include <kocmoc-core/scene/FilmCamera.hpp>

#include <input/WiimoteInputManager.hpp>

#include "object/Monkey.hpp"

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
		
		kocmoc::core::scene::AssetLoader* getAssetLoader() {return assetLoader;}
		kocmoc::core::util::Properties* getProps() {return props;}
		kocmoc::core::scene::FilmCamera* getCamera() {return camera;}

	private:
		kocmoc::core::renderer::Context* context;
		kocmoc::core::util::Properties* props;
		kocmoc::core::scene::AssetLoader* assetLoader;
		kocmoc::core::scene::FilmCamera* camera;
		
		bool running;
		kocmoc::core::types::Symbol quit, screenShot, note, cursorX, cursorY, pos1, pos2;
		
		object::Monkey* monkey;
		kocmoc::core::scene::ImageLoader imageLoader;
		
		class InputCallback : public kocmoc::core::input::ButtonEventListener
		{
		public:
			InputCallback(Sputnik* _p)
			: p(_p)
			{}
			
			void buttonEventCallback(kocmoc::core::types::Symbol name, kocmoc::core::input::ButtonEvent event)
			{
				if (name == p->quit)
					p->running = false;
				
				else if (name == p->screenShot)
					p->imageLoader.screenShot();
				
				else if (name == p->pos1)
				{
					p->camera->setPosition(glm::vec3(0, 0, 4));
					p->camera->setTargetPosition(glm::vec3(0));
					p->camera->setUpVector(glm::vec3(0, 1, 0));
				}
				
				else if (name == p->pos2)
				{
					p->camera->setPosition(glm::vec3(400, 400, 404));
					p->camera->setTargetPosition(glm::vec3(400, 400, 400));
					p->camera->setUpVector(glm::vec3(0, 1, 0));
				}
				
				UNUSED event;
			}
			
		private:
			Sputnik* p;
		} ic;
		
		output::MIDIOut midiOut;

	};
}

#endif
