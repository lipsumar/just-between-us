#include "./UiState.h"
#include <Arduino.h>

UiState::UiState(unsigned int bpm, unsigned int outputCount)
  : currentMode(UiState::Mode::WELCOME), bpm(bpm), outputCount(outputCount) {}

void UiState::setDirty() {
  isDirty = true;
}

bool UiState::checkDirtyAndReset() {
  if (isDirty) {
    isDirty = false;
    return true;
  }
  return false;
}

UiState::Mode UiState::getMode() const {
  return currentMode;
}

void UiState::setMode(UiState::Mode mode) {
  currentMode = mode;
  setDirty();
}

bool UiState::isEditing() const {
  return editing;
}

unsigned int UiState::getBpm() const {
  return bpm;
}

unsigned int UiState::getCurrentOutputIndex() const {
  return currentOutputIndex;
}

unsigned int UiState::getCurrentOutputModifierIndex() const {
  return currentOutputModifierIndex;
}

unsigned int UiState::getCurrentParameterIndex() const {
  return currentParameterIndex;
}

unsigned int UiState::getCurrentParameterValue() const {
  return currentParameterValue;
}

void UiState::turn(int direction, GlobalState& state) {
  if (editing) {
    if (currentMode == Mode::BPM) {
      bpm += direction;

    } else if (currentMode == Mode::OUTPUT_MODIFIER) {
      currentOutputModifierIndex = Utils::cycleIndex(currentOutputModifierIndex, direction, Modifiers::COUNT);

    } else if (currentMode == Mode::OUTPUT_PARAMETER) {
      Parameters::Definition paramDef = Parameters::ALL_PARAMETERS[currentParameterIndex];
      switch (paramDef.valueType) {
        case Parameters::ValueType::PERCENT:
          if (direction > 0 && currentParameterValue < 100) {
            currentParameterValue++;
          } else if (direction < 0 && currentParameterValue > 0) {
            currentParameterValue--;
          }
          break;
        case Parameters::ValueType::INDEX:
          currentParameterValue = Utils::cycleIndex(currentParameterValue, direction, paramDef.maxIndex + 1);
          break;
      }
    }

  } else {
    if (currentMode == Mode::OUTPUT_PARAMETER) {
      currentParameterIndex = Utils::cycleIndex(currentParameterIndex, direction, Parameters::COUNT);
      Parameters::Definition paramDef = Parameters::ALL_PARAMETERS[currentParameterIndex];
      OutputState output = state.getOutputReadOnly(currentOutputIndex);
      switch (paramDef.valueType) {
        case Parameters::ValueType::PERCENT:
          currentParameterValue = Utils::floatToPercent(output.getParameterValue(paramDef.type));
          break;
        case Parameters::ValueType::INDEX:
          currentParameterValue = output.getIntParameterValue(paramDef.type);
          break;
      }


    } else {
      modeCycleIndex = Utils::cycleIndex(modeCycleIndex, direction, outputCount + 1);

      if (modeCycleIndex == 0) {
        currentMode = Mode::BPM;
      } else {
        currentOutputIndex = modeCycleIndex - 1;
        currentMode = Mode::OUTPUT_MODIFIER;
        currentOutputModifierIndex = state.getOutput(currentOutputIndex).getModifier();
      }
    }
  }
  setDirty();
}

void UiState::click(GlobalState& state) {
  if (editing) {
    editing = false;
    
    if (currentMode == Mode::BPM) {
      state.setBpm(bpm);
    } else if (currentMode == Mode::OUTPUT_MODIFIER) {
      OutputState& output = state.getOutput(currentOutputIndex);
      output.setModifier(currentOutputModifierIndex);
    } else if (currentMode == Mode::OUTPUT_PARAMETER) {
      OutputState& output = state.getOutput(currentOutputIndex);
      Parameters::Definition paramDef = Parameters::ALL_PARAMETERS[currentParameterIndex];
      switch(paramDef.valueType){
        case Parameters::ValueType::PERCENT:
          output.setParameterValue(paramDef.type, Utils::percentToFloat(currentParameterValue));
          break;
        case Parameters::ValueType::INDEX:
          output.setIntParameterValue(paramDef.type, currentParameterValue);
          break;
      }
      
    }

  } else {
    editing = true;
  }
  setDirty();
}

void UiState::longClick(GlobalState& state) {
  Serial.println("longClick");
  if (currentMode == UiState::Mode::OUTPUT_MODIFIER) {
    currentMode = UiState::Mode::OUTPUT_PARAMETER;
    currentParameterIndex = 0;
    currentParameterValue = Utils::floatToPercent(
      state.getOutputReadOnly(currentOutputIndex).getParameterValue(Parameters::ALL_PARAMETERS[currentParameterIndex].type));
  } else if (currentMode == UiState::Mode::OUTPUT_PARAMETER) {
    currentMode = UiState::Mode::OUTPUT_MODIFIER;
  }
  setDirty();
}
