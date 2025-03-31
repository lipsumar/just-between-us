#pragma once

#include <cstddef>
#include "../ModifierDefinitions.h"
#include "../ParameterDefinitions.h"

class OutputState {
private:
  size_t modifier = Modifiers::defaultIndex;  
  size_t wave = 0;
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

  void setWave(int wave);
  int getWave() const;

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
  int getIntParameterValue(Parameters::Type type) const;
  void setIntParameterValue(Parameters::Type type, int value);
  const char* getParameterValueDisplayName(Parameters::Type type, size_t index) const;

  void setPin(unsigned int pin);
  unsigned int getPin() const;
};
