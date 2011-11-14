#ifndef SPUTNIK_COMPONENT_SPEED_TO_MIDI_HPP
#define SPUTNIK_COMPONENT_SPEED_TO_MIDI_HPP

#include <kocmoc-core/componentSystem/Component.hpp>
#include <kocmoc-core/component/ObjectBehaviour.hpp>

#include <output/MIDIOut.hpp>

namespace sputnik
{
	namespace component
	{
		class SpeedToMidi : public kocmoc::core::componentSystem::Component
		{
		public:
			/**
			 * @param _cc cc output channel
			 */
			SpeedToMidi(output::MIDIOut* _mOut, unsigned int _cc)
				: cc(_cc)
				, mOut(_mOut)
			{}
			
			void init();
			void onUpdate(float deltaT, float t);
			
		private:
			unsigned int cc;
			kocmoc::core::component::ObjectBehaviour* ob;
			output::MIDIOut* mOut;
		};
	}
}

#endif
