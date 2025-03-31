#pragma once

float sineWave(
  unsigned int time,
  unsigned int ppq,  // aka. resolution
  float periodInQuarters,
  float width,
  float phase) {

  // how many ticks in a period
  float cycleLength = ppq * periodInQuarters;

  // where are we in the cycle (0-1.0)
  float normalizedPosition = fmod((time + (phase * cycleLength)), cycleLength) / cycleLength;

  // @TODO take width into account to skew the sine
  return (sin(normalizedPosition * 2 * M_PI) + 1) / 2;
}