#pragma once

float squareWave(
  unsigned int time,
  unsigned int ppq,  // aka. resolution
  float periodInQuarters,
  float width,
  float phase) {

  // how many ticks in a period
  float cycleLength = ppq * periodInQuarters;

  // where are we in the cycle (0-1.0)
  float normalizedPosition = fmod((time + (phase * cycleLength)), cycleLength) / cycleLength;

  return normalizedPosition < width ? 1.0 : 0.0;
}
