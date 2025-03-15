#pragma once

#include <cstddef>
#include "../ModifierDefinitions.h"
#include "../ParameterDefinitions.h"

class OutputState {
private:
  size_t modifier = Modifiers::defaultIndex;  
  //float level = 1.0; - can't do amplitude yet
  float width = 0.5;
  //float offset = 0.0; - can't do amplitude yet
  float phase = 0.0;
  unsigned int pin;

public:
  OutputState();

  void setModifier(size_t modifierIndex);
  size_t getModifier() const;
  const Modifiers::Definition& getModifierDefinition() const;
  float getPeriodInQuarters() const;

  // void setLevel(float level);
  // float getLevel() const;

  void setWidth(float width);
  float getWidth() const;

  // void setOffset(float offset);
  // float getOffset() const;

  void setPhase(float phase);
  float getPhase() const;

  float getParameterValue(Parameters::Type type) const;
  void setParameterValue(Parameters::Type type, float value);

  void setPin(unsigned int pin);
  unsigned int getPin() const;
};
