#ifndef SPUTNIK_OUTPUT_MIDI_OUT_HPP
#define SPUTNIK_OUTPUT_MIDI_OUT_HPP

#include "MusicControlOut.hpp"

#include <rtmidi/RtMidi.h>

namespace sputnik
{
	namespace output
	{
		class MIDIOut : public MusicControlOut
		{
		public:
			MIDIOut(void);
			~MIDIOut(void);
			
			virtual void sendCC(int number, float value);
			virtual void sendNote(int note, float velocity);
			
		private:
			RtMidiOut* midiOut;
		};
	}
}



#endif
