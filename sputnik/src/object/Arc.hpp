#ifndef SPUTNIK_OBJECT_ARC_HPP
#define SPUTNIK_OBJECT_ARC_HPP

#include <kocmoc-core/componentSystem/Object.hpp>

#include <component/ArcBehaviour.hpp>
#include <input/WiimoteInputManager.hpp>

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
	namespace object
	{
		class Arc : public kocmoc::core::componentSystem::Object
		{
		public:
			Arc(kocmoc::core::util::Properties* props,
				input::WiimoteInputManager* inputManager,
				kocmoc::core::scene::FilmCamera* camera);

		private:
			component::ArcBehaviour* behaviour;
		};
	}
}

#endif
