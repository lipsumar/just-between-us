// RotaryEncoder.h
#pragma once
#include <Encoder.h>

class RotaryEncoder {
  private:
    Encoder knob;
    int lastStableValue = 0;
    int encoderMultiple = 4; // Step size 
    int currentStep = 0;
    int lastDirection = 0;

  public:
    RotaryEncoder(uint8_t pinA, uint8_t pinB);
    void update();
    int hasTurned(); // Will return -1 (left), 0 (no change), or 1 (right)
    int getCurrentStep();
};