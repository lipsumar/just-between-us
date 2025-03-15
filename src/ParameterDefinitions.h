#pragma once


namespace Parameters {
enum class Type {
  WIDTH,
  PHASE
};

struct Definition {
  Type type;
  const char* displayName;
};

const Definition ALL_PARAMETERS[] = {
  { Type::WIDTH, "Wdt" },
  { Type::PHASE, "Pha" }
};

const size_t COUNT = sizeof(ALL_PARAMETERS) / sizeof(Definition);

}
