#pragma once

#include <array>
#include "../OutputState/OutputState.h"

class GlobalState {
  private:
    bool isDirty;
    unsigned int bpm;
    bool playing;
    bool playingChanged;
    bool bpmChanged;
    std::array<OutputState, 2> outputs;

  public:
    GlobalState();

    bool checkDirtyAndReset();

    unsigned int getBpm() const;
    void setBpm(unsigned int bpm);
    bool hasBpmChanged();

    bool isPlaying() const;
    void togglePlayPause();
    bool hasPlayingChanged();

    unsigned int getOutputSize() const;
    OutputState& getOutput(unsigned int index);
    const OutputState& getOutputReadOnly(unsigned int index) const;

    void setOutputPin(unsigned int outputIndex, unsigned int pin);
};
