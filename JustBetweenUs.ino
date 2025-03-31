
#include <Bounce.h>
#include "./src/GlobalState/GlobalState.h"
#include "./src/MidiClock/MidiClock.h"
#include "./src/RotaryEncoder/RotaryEncoder.h"
#include "./src/MasterClock/MasterClock.h"
#include "./src/UiDisplay/UiDisplay.h"
#include "./src/UiState/UiState.h"
#include "./src/Waveform/Square.h"
#include "./src/Waveform/Triangle.h"
#include "./src/Waveform/Sine.h"

// pins
#define PIN_BTN 7
#define PIN_ENCODER_A 32
#define PIN_ENCODER_B 31
#define PIN_ENCODER_BTN 30
// pins - output pins
#define PIN_OUTPUT_1 24
#define PIN_OUTPUT_2 25
#define NUM_OUTPUTS 2
// this array also defines output index for the state
const int outputPins[NUM_OUTPUTS] = { PIN_OUTPUT_1, PIN_OUTPUT_2 };

// PWM config
// see https://www.pjrc.com/teensy/td_pulse.html
#define PWM_FREQUENCY 36621
#define PWM_RESOLUTION 12
#define PWM_MAX_VALUE ((1 << PWM_RESOLUTION) - 1)  // 2^12 - 1 = 4095

// state stuff
GlobalState state;
UiState uiState(state.getBpm(), state.getOutputSize());

// display stuff
UiDisplay display;

// clocks
const unsigned int CLOCK_PPQ = 192;
MasterClock masterClock(CLOCK_PPQ, state.getBpm(), 8);  // 8 quarter per cycle - the largest divider in modifiers
MidiClock midiClock(CLOCK_PPQ);

// controls
Bounce pushButton(PIN_BTN, 10);  // 10ms debounce
RotaryEncoder knob(PIN_ENCODER_A, PIN_ENCODER_B);
Bounce knobButton(PIN_ENCODER_BTN, 10);
unsigned int knobButtonPressedAt = 0;
bool knobButtonDown = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Just Betwen Us - setup begin");

  // configure pins
  pinMode(PIN_BTN, INPUT_PULLUP);
  pinMode(PIN_ENCODER_BTN, INPUT_PULLUP);

  // configure PWM output pins & register them in state
  analogWriteResolution(PWM_RESOLUTION);
  for(int i=0; i<NUM_OUTPUTS; i++){
    pinMode(outputPins[i], OUTPUT);
    analogWriteFrequency(outputPins[i], PWM_FREQUENCY);
    analogWrite(outputPins[i], 0);

    state.setOutputPin(i, outputPins[i]);
  }


  display.init();

  masterClock.setUserCallback(masterClockTick);

  display.update(state, uiState);
  delay(2000);
  uiState.setMode(UiState::Mode::BPM);
  display.update(state, uiState);
}

void loop() {

  // controls & state update

  knob.update();
  int direction = knob.hasTurned();
  if (direction) {
    uiState.turn(direction, state);
  }

  if (knobButton.update()) {
    if (knobButton.fallingEdge()) {  // press
      knobButtonPressedAt = millis();
      knobButtonDown = true;
    }
    if (knobButton.risingEdge()) {  // release
      knobButtonDown = false;
      unsigned int pressTimeMs = millis() - knobButtonPressedAt;
      if (pressTimeMs < 800) {
        uiState.click(state);
      }
    }
  }
  if (knobButtonDown && millis() - knobButtonPressedAt > 800) {
    uiState.longClick(state);
    knobButtonDown = false;  // this isn't true but we need it to avoid longClick looping
  }

  if (pushButton.update()) {
    if (pushButton.fallingEdge()) {
      state.togglePlayPause();
    }
  }

  // reacting to state change

  if (state.hasPlayingChanged()) {
    if (state.isPlaying()) {
      masterClock.start();
      midiClock.start();
    } else {
      masterClock.stop();
      midiClock.stop();
    }
  }

  if (state.hasBpmChanged()) {
    masterClock.setBpm(state.getBpm());
  }

  bool stateDirty = state.checkDirtyAndReset();
  bool uiStateDirty = uiState.checkDirtyAndReset();
  if (stateDirty || uiStateDirty) {
    display.update(state, uiState);
  }
}

// !! This is an interrupt
void masterClockTick(unsigned int clockTickCount) {
  midiClock.update(clockTickCount);

  for (unsigned int outputIndex = 0; outputIndex < state.getOutputSize(); outputIndex++) {
    OutputState output = state.getOutputReadOnly(outputIndex);

    float value;
    switch(ParamaterWave::ALL_WAVES[output.getWave()].type){
      case ParamaterWave::Type::SQUARE:
        value = squareWave(clockTickCount, CLOCK_PPQ, output.getPeriodInQuarters(), output.getWidth(), output.getPhase());
        break;
      case ParamaterWave::Type::TRIANGLE:
        value = triangleWave(clockTickCount, CLOCK_PPQ, output.getPeriodInQuarters(), output.getWidth(), output.getPhase());
        break;
      case ParamaterWave::Type::SINE:
        value = sineWave(clockTickCount, CLOCK_PPQ, output.getPeriodInQuarters(), output.getWidth(), output.getPhase());
        break;
    }

    unsigned int pin = output.getPin();

    analogWrite(pin, value * PWM_MAX_VALUE);
  }
}
