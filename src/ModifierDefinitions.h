#pragma once


namespace Modifiers {

enum class Type {
  MULTIPLY,
  DIVIDE,
  ON,
  OFF,
  PULSE_START,
  PULSE_END
};

struct Definition {
  Type type;
  float value;
  const char* displayValue;
};

const Definition ALL_MODIFIERS[] = {
  // { Type::ON, 0.0f, "ON" },
  // { Type::OFF, 0.0f, "OFF" },
  // { Type::PULSE_START, 0.0f, "P>" },
  // { Type::PULSE_END, 0.0f, "P<" },
  { Type::DIVIDE, 8.0f, "/8" },
  { Type::DIVIDE, 4.0f, "/4" },
  { Type::DIVIDE, 3.0f, "/3" },
  { Type::DIVIDE, 2.0f, "/2" },
  { Type::DIVIDE, 1.5f, "/1.5" },      // Dotted
  { Type::DIVIDE, 1.33333f, "/1.3" },  // Triplet
  { Type::MULTIPLY, 1.0f, "x1" },
  { Type::MULTIPLY, 1.33333f, "x1.3" },  // Triplet
  { Type::MULTIPLY, 1.5f, "x1.5" },      // Dotted
  { Type::MULTIPLY, 2.0f, "x2" },
  { Type::MULTIPLY, 3.0f, "x3" },
  { Type::MULTIPLY, 4.0f, "x4" },
  { Type::MULTIPLY, 8.0f, "x8" }, // This is the slowest we get. If getting any slower, the MasterClock's quartersPerCycle needs to be adjusted
};
const size_t defaultIndex = 6;

// Number of modifiers
const size_t COUNT = sizeof(ALL_MODIFIERS) / sizeof(Definition);
}