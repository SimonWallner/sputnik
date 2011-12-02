#include "MIDIOut.hpp"

#include <vector>

#include <kocmoc-core/compiler.h>
#include <kocmoc-core/math/math.hpp>

using namespace sputnik::output;
using namespace kocmoc::core::math;

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
	unsigned char normlisedValue = min(max(value * 127.0f, 0.0f), 127.0f);
	
	// check the cache to save midi bandwith
	CCCache::const_iterator ci = ccCache.find(number);
	if (ci != ccCache.end() && ci->second == normlisedValue)
		return;
	
	std::vector<unsigned char> message;
	message.push_back(176); // CC???
	message.push_back(number);
	message.push_back(normlisedValue);
	
	midiOut->sendMessage(&message);
	
	ccCache[number] = normlisedValue;
}

void MIDIOut::sendNote(int note, float velocity)
{
	std::vector<unsigned char> message;
	message.push_back(144); // note on???
	message.push_back(note);
	
	unsigned char normlisedVelocity = min(max(velocity * 127.0f, 0.0f), 127.0f);
	message.push_back(normlisedVelocity);

	midiOut->sendMessage(&message);
}
