#pragma once

namespace Utils {
inline unsigned int cycleIndex(unsigned int index, int direction, unsigned int size) {
  int newIndex = index + direction;
  if (newIndex >= static_cast<int>(size)) {
    return 0;
  }
  if (newIndex < 0) {
    return static_cast<unsigned int>(size - 1);
  }
  return newIndex;
}

inline unsigned int floatToPercent(float f) {
  return f * 100;
}

inline float percentToFloat(unsigned int pc) {
  return static_cast<float>(pc) / 100;
}

}
