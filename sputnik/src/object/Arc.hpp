#ifndef SPUTNIK_OBJECT_ARC_HPP
#define SPUTNIK_OBJECT_ARC_HPP

#include <kocmoc-core/componentSystem/Object.hpp>

#include <component/ArcBehaviour.hpp>

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
			Arc(kocmoc::core::util::Properties* props);

		private:
			component::ArcBehaviour* behaviour;
		};
	}
}

#endif
