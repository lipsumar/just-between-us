#pragma once

#include "./WaveParameterDefinitions.h"

namespace Parameters {
enum class Type {
  WAVE,
  WIDTH,
  PHASE
};

enum class ValueType {
  PERCENT,
  INDEX
};

struct Definition {
  Type type;
  const char* displayName;
  ValueType valueType;
  unsigned int maxIndex;  // only used for ValueType::INDEX
};

const Definition ALL_PARAMETERS[] = {
  { Type::WAVE, "Wav", ValueType::INDEX, ParamaterWave::COUNT - 1 },
  { Type::WIDTH, "Wdt", ValueType::PERCENT, 0 },
  { Type::PHASE, "Pha", ValueType::PERCENT, 0 }
};

const size_t COUNT = sizeof(ALL_PARAMETERS) / sizeof(Definition);

}

