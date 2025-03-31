#pragma once

float triangleWave(
  unsigned int time,
  unsigned int ppq,  // aka. resolution
  float periodInQuarters,
  float width,
  float phase) {

  // how many ticks in a period
  float cycleLength = ppq * periodInQuarters;

  // where are we in the cycle (0-1.0)
  float normalizedPosition = fmod((time + (phase * cycleLength)), cycleLength) / cycleLength;

  if (normalizedPosition < width) {
    // rising
    return normalizedPosition / width;
  } else {
    // falling
    return 1 - ((normalizedPosition - width) / (1 - width));
  }
}