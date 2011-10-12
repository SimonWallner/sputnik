#ifndef SPUTNIK_OBJECT_SAMPLER_HPP
#define SPUTNIK_OBJECT_SAMPLER_HPP

#include <kocmoc-core/componentSystem/Object.hpp>

namespace sputnik
{
	namespace object
	{
		class Sampler : public kocmoc::core::componentSystem::Object
		{		
		public:
			Sampler(std::string name, kocmoc::core::util::Properties* props);
		};
	}
}

#endif