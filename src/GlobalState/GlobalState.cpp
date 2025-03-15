#include "./GlobalState.h"

GlobalState::GlobalState()
  : bpm(120), playing(false), playingChanged(false), bpmChanged(false) {}

bool GlobalState::checkDirtyAndReset() {
  if (isDirty) {
    isDirty = false;
    return true;
  }
  return false;
}

unsigned int GlobalState::getBpm() const {
  return bpm;
}

void GlobalState::setBpm(unsigned int bpm_) {
  bpm = bpm_;
  bpmChanged = true;
  isDirty = true;
}

bool GlobalState::hasBpmChanged() {
  if (bpmChanged) {
    bpmChanged = false;
    return true;
  }
  return false;
}

bool GlobalState::isPlaying() const {
  return playing;
}

void GlobalState::togglePlayPause() {
  playing = !playing;
  playingChanged = true;
  isDirty = true;
}

bool GlobalState::hasPlayingChanged() {
  if (playingChanged) {
    playingChanged = false;
    return true;
  }
  return false;
}

unsigned int GlobalState::getOutputSize() const {
  return outputs.size();
}

OutputState& GlobalState::getOutput(unsigned int index) {
  return outputs[index];
}

const OutputState& GlobalState::getOutputReadOnly(unsigned int index) const {
  return outputs[index];
}

void GlobalState::setOutputPin(unsigned int outputIndex, unsigned int pin){
  outputs[outputIndex].setPin(pin);
}

