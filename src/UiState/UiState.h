#pragma once

#include "../GlobalState/GlobalState.h"
#include "../ParameterDefinitions.h"
#include "../Utils.h"

class UiState {
public:
  enum class Mode {
    WELCOME,
    BPM,
    OUTPUT_MODIFIER,
    OUTPUT_PARAMETER
  };

private:

  bool editing = false;
  bool isDirty = false;
  void setDirty();

  Mode currentMode;
  unsigned int bpm;

  unsigned int outputCount;
  int modeCycleIndex = 0;
  unsigned int currentOutputIndex = 0;
  unsigned int currentOutputModifierIndex = 0;

  unsigned int currentParameterIndex = 0;
  unsigned int currentParameterValue = 0;

public:
  UiState(unsigned int bpm, unsigned int outputCount);

  bool checkDirtyAndReset();

  Mode getMode() const;
  void setMode(UiState::Mode mode);
  bool isEditing() const;
  unsigned int getBpm() const;
  unsigned int getCurrentOutputIndex() const;
  unsigned int getCurrentOutputModifierIndex() const;

  unsigned int getCurrentParameterIndex() const;
  unsigned int getCurrentParameterValue() const;

  void turn(int direction, GlobalState& state);
  void click(GlobalState& state);
  void longClick(GlobalState& state);
};

/*

Wave    Wav
Level   Lvl
Offset  Ofs
Width   Wdt
Phase   Pha
Delay   Del
Dly     Dly
Slop    Slo
Skip    Skp
Loop    Lop | Loo
Quant   Qua
Logic   Log

*/