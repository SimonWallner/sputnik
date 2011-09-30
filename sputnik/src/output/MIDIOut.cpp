#include "MIDIOut.hpp"

#include <vector>

#include <kocmoc-core/compiler.h>

using namespace sputnik::output;

MIDIOut::MIDIOut()
{
	/* code partially derived from the provided tutorial code. */
	
	midiOut = new RtMidiOut;
	midiOut->openVirtualPort("sputnik MIDI breakout");
}

MIDIOut::~MIDIOut()
{
	midiOut->closePort();
	delete midiOut;
}

void MIDIOut::sendCC(int number, float value)
{
	std::vector<unsigned char> message;
	message.push_back(0); // channel 0
	message.push_back(number);
	message.push_back(value);
	
	midiOut->sendMessage(&message);
}

void MIDIOut::sendNote(int note, float velocity)
{
	UNUSED note;
	UNUSED velocity;
}
