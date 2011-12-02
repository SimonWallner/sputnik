#ifndef SPUTNIK_OBJECT_WAY_POINT_HPP
#define SPUTNIK_OBJECT_WAY_POINT_HPP

#include <kocmoc-core/ComponentSystem/Object.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>

#include <scene/SelectableWorld.hpp>
#include <output/MIDIOut.hpp>
#include <component/OriginDrag.hpp>
#include <component/OriginDistToMidi.hpp>
#include <sputnik.hpp>

namespace sputnik
{
	namespace object
	{
		class WayPoint : public kocmoc::core::componentSystem::Object
		{
		public:
			WayPoint(Sputnik* sputnik,
					 scene::SelectableWorld* world,
					 output::MIDIOut* mOut,
					 unsigned int cc);
			
			void setPosition(glm::vec3 position)
			{
				ob->position = position;
				originDrag->origin = position;
				originDistToMidi->origin = position;
			}
			
			void setRotation(glm::quat rotation)
			{
				ob->rotation = rotation;
			}
			
		private:
			kocmoc::core::component::ObjectBehaviour* ob;
			component::OriginDrag* originDrag;
			component::OriginDistToMidi* originDistToMidi;
		};
	}
}


#endif
