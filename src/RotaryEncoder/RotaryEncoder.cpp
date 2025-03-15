// RotaryEncoder.cpp
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(uint8_t pinA, uint8_t pinB)
  : knob(pinA, pinB) // Proper initialization
{
  // Additional setup if needed
}

void RotaryEncoder::update() {
  int rawValue = knob.read();
  
  // Check if the value is at a stable position (multiple of encoderMultiple)
  if (rawValue % encoderMultiple == 0) {
    // Only process if we're at a new stable position
    if (rawValue != lastStableValue) {
      // Calculate direction: -1 for left, 1 for right
      if (rawValue > lastStableValue) {
        lastDirection = 1; // Turned right
      } else {
        lastDirection = -1; // Turned left
      }
      
      // Save the new stable position
      lastStableValue = rawValue;
      
      // Update the step value
      currentStep = rawValue / encoderMultiple;
    } else {
      // At a stable position but no change
      lastDirection = 0;
    }
  } else {
    // We're between detents, no change to report
    lastDirection = 0;
  }
}

int RotaryEncoder::hasTurned() {
  // Returns direction of turn: -1 (left), 0 (no change), 1 (right)
  return lastDirection;
}

int RotaryEncoder::getCurrentStep() {
  // Return the current step position
  return currentStep;
}