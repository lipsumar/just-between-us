#include "OutputState.h"

OutputState::OutputState() {
}

void OutputState::setModifier(size_t modifierIndex) {
  this->modifier = modifierIndex;
}

size_t OutputState::getModifier() const {
  return modifier;
}

const Modifiers::Definition& OutputState::getModifierDefinition() const {
  return Modifiers::ALL_MODIFIERS[modifier];
}


float OutputState::getPeriodInQuarters() const {
  const auto& mod = getModifierDefinition();
  switch (mod.type) {
    case Modifiers::Type::MULTIPLY:
      return 1.0 / mod.value;
    case Modifiers::Type::DIVIDE:
      return mod.value;
    default:
      return 1.0;
  }
}

// void OutputState::setLevel(float level) {
//   this->level = level;
// }
// float OutputState::getLevel() const {
//   return level;
// }

void OutputState::setWidth(float width) {
  this->width = width;
}
float OutputState::getWidth() const {
  return width;
}

// void OutputState::setOffset(float offset) {
//   this->offset = offset;
// }
// float OutputState::getOffset() const {
//   return offset;
// }

void OutputState::setPhase(float phase) {
  this->phase = phase;
}
float OutputState::getPhase() const {
  return phase;
}

float OutputState::getParameterValue(Parameters::Type type) const {
  switch (type) {
    case Parameters::Type::WIDTH:
      return width;
    case Parameters::Type::PHASE:
      return phase;
    default:
      return 0.0;
  }
}
void OutputState::setParameterValue(Parameters::Type type, float value){
  switch (type) {
    case Parameters::Type::WIDTH:
      width = value;
      break;
    case Parameters::Type::PHASE:
      phase = value;
      break;
  }
}

void OutputState::setPin(unsigned int pin) {
  this->pin = pin;
}

unsigned int OutputState::getPin() const {
  return pin;
}
