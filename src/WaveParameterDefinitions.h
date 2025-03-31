
namespace ParamaterWave {
enum class Type {
  SQUARE,
  TRIANGLE,
  SINE
};

struct Definition {
  Type type;
  const char *displayName;
};

const Definition ALL_WAVES[] = {
  { Type::SQUARE, "SQUARE" },
  { Type::TRIANGLE, "TRIANGLE" },
  { Type::SINE, "SINE" }
};

const size_t COUNT = sizeof(ALL_WAVES) / sizeof(Definition);
}