#ifndef	SPUTNIK_OUTPUT_MUSIC_CONTROL_OUT_HPP
#define SPUTNIK_OUTPUT_MUSIC_CONTROL_OUT_HPP

namespace sputnik
{
	namespace output
	{
		/**
		 * MIDI abtraction layer
		 * @note Terminology is taken from MIDI
		 */
		class MusicControlOut
		{
		public:	
			/**
			 * send a control change message
			 * @param number number of the control
			 * @param value new value. value must be in [0, 1]
			 */
			virtual void sendCC(int number, float value) = 0;
			
			/**
			 * Send a note message
			 * @param note the MIDI note number
			 * @param velocity velocity/value of the note. this must be in [0, 1]
			 */
			virtual void sendNote(int note, float velocity) = 0;
		};
	}
}

#endif
