#ifndef SPUTNIK_COMPONENT_ORIGIN_DIST_TO_MIDI_HPP
#define SPUTNIK_COMPONENT_ORIGIN_DIST_TO_MIDI_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>

#include <kocmoc-core/compiler.h>

#include <output/MIDIOut.hpp>


namespace sputnik
{
	namespace component
	{
		class OriginDistToMidi : public kocmoc::core::componentSystem::Component
		{
		public:
			OriginDistToMidi(output::MIDIOut* _mOut, unsigned int _cc)
				: origin(glm::vec3(0))
				, cc(_cc)
				, mOut(_mOut)
			{}
			
			void init();
			void onUpdate(float deltaT, float t);
			
			glm::vec3 origin;
		
		private:
			unsigned int cc;
			kocmoc::core::component::ObjectBehaviour* ob;
			output::MIDIOut* mOut;			
		};
	}
}

#endif
