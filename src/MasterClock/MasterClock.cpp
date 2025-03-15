#include "./MasterClock.h"

MasterClock* MasterClock::instance = nullptr;

MasterClock::MasterClock(unsigned int ppq, unsigned int bpm, unsigned int quartersPerCycle)
  : tickCount(0), timer(), ppq(ppq), bpm(bpm), quartersPerCycle(quartersPerCycle), running(false) {
  instance = this;
}

void MasterClock::timerCallbackStatic() {
  if (instance) {
    instance->timerCallback();
  }
}

void MasterClock::timerCallback() {
  if (userCallback) {
    userCallback(tickCount);
  }

  tickCount++;
  if (tickCount >= (ppq * quartersPerCycle)) {
    tickCount = 0;
  }
}

float MasterClock::getInterval() {
  return (60.0 * 1000000.0) / (bpm * ppq);
}

void MasterClock::setBpm(unsigned int _bpm) {
  bpm = _bpm;
  if (running) {
    timer.update(getInterval());
  }
}


void MasterClock::start() {
  running = true;
  tickCount = 0;
  float interval = getInterval();
  timer.begin(timerCallbackStatic, interval);
}

void MasterClock::stop() {
  running = false;
  timer.end();
}

void MasterClock::setUserCallback(void (*callback)(unsigned int tickCount)) {
  userCallback = callback;
}
