#pragma once

#include <IntervalTimer.h>

class MasterClock {
private:
  static MasterClock* instance;
  static void timerCallbackStatic();

  void timerCallback();
  
  
  unsigned int tickCount;
  IntervalTimer timer;
  unsigned int ppq;
  unsigned int bpm;
  unsigned int quartersPerCycle;
  bool running;
  float getInterval();
  void (*userCallback)(unsigned int tickCount);


public:
  MasterClock(unsigned int ppq, unsigned int bpm, unsigned int quartersPerCycle);
  void setBpm(unsigned int bpm);
  void start();
  void stop();
  void setUserCallback(void (*callback)(unsigned int tickCount));
};
