#pragma once

#include <MIDI.h>

class MidiClock {
  private:
    unsigned int masterClockDivider;
  public:
    MidiClock(unsigned int masterClockPpq);
    void start();
    void stop();
    void update(unsigned int clockTickCount);
};
