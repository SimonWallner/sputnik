#ifndef SPUTNIK_OBJECT_ARCH_HPP
#define SPUTNIK_OBJECT_ARCH_HPP

#include <kocmoc-core/componentSystem/Object.hpp>

#include <component/ArchBehaviour.hpp>

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
		class Arch : public kocmoc::core::componentSystem::Object
		{
		public:
			Arch(kocmoc::core::util::Properties* props);

		private:
			component::ArchBehaviour* behaviour;
		};
	}
}

#endif
