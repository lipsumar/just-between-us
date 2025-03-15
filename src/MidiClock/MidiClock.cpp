#include "./MidiClock.h"


const unsigned char MIDI_CLOCK = 0xF8;     // MIDI timing clock
const unsigned char MIDI_START = 0xFA;     // MIDI start
const unsigned char MIDI_CONTINUE = 0xFB;  // MIDI continue
const unsigned char MIDI_STOP = 0xFC;      // MIDI stop
const int MIDI_PPQ = 24;


MidiClock::MidiClock(unsigned int masterClockPpq) {
  masterClockDivider = masterClockPpq / MIDI_PPQ;
}

void MidiClock::update(unsigned int clockTickCount) {
  if (clockTickCount % masterClockDivider == 0) {
    usbMIDI.sendRealTime(MIDI_CLOCK);
  }
}

void MidiClock::start() {
  usbMIDI.sendRealTime(MIDI_START);
}

void MidiClock::stop() {
  usbMIDI.sendRealTime(MIDI_STOP);
}