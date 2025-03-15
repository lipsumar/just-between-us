#include <sys/_intsup.h>
#include "./UiDisplay.h"

UiDisplay::UiDisplay()
  : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
}

void UiDisplay::init() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
}

void UiDisplay::update(const GlobalState& state, const UiState& uiState) {
  switch (uiState.getMode()) {
    case UiState::Mode::WELCOME: renderWelcome(); break;
    case UiState::Mode::BPM: renderBpm(state, uiState); break;
    case UiState::Mode::OUTPUT_MODIFIER: renderOutputModifier(state, uiState); break;
    case UiState::Mode::OUTPUT_PARAMETER: renderOutputParameter(state, uiState); break;
    default:
      renderError();
  }
}

void UiDisplay::renderWelcome() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(8, 28);
  display.println(F("[ Just Between Us ]"));
  display.display();
}

void UiDisplay::renderBpm(const GlobalState& state, const UiState& uiState) {
  display.clearDisplay();
  renderPlayPause(state.isPlaying());

  display.setTextColor(WHITE);

  // BPM label
  display.setCursor(33, topTextY);
  display.setTextSize(1);
  display.print("BPM");

  // BPM value
  unsigned int bpm = state.getBpm();
  if (uiState.isEditing()) {
    display.setTextColor(BLACK);
    display.fillRect(29, bottomTextY - 4, 60, 29, WHITE);
    bpm = uiState.getBpm();
  }
  display.setCursor(33, bottomTextY);
  display.setTextSize(3);

  display.printf("%d", bpm);

  display.display();
}



void UiDisplay::renderOutputModifier(const GlobalState& state, const UiState& uiState) {
  display.clearDisplay();
  renderPlayPause(state.isPlaying());

  display.setTextColor(WHITE);

  // output number label
  display.setTextSize(1);
  display.setCursor(9, topTextY);
  display.write("OUT:");
  // output number value
  display.setTextSize(3);
  display.setCursor(12, bottomTextY);
  display.printf("%u", uiState.getCurrentOutputIndex() + 1);

  display.drawLine(39, 4, 39, 60, WHITE);
  display.drawLine(40, 4, 40, 60, WHITE);

  // modifier label
  display.setTextSize(1);
  display.setCursor(52, topTextY);
  display.write("MODIFIER:");
  // modifier value

  OutputState output = state.getOutputReadOnly(uiState.getCurrentOutputIndex());
  const char* modValue = output.getModifierDefinition().displayValue;
  if (uiState.isEditing()) {
    display.setTextColor(BLACK);
    display.fillRect(49, bottomTextY - 4, 72, 29, WHITE);
    modValue = Modifiers::ALL_MODIFIERS[uiState.getCurrentOutputModifierIndex()].displayValue;
  }
  display.setTextSize(3);
  display.setCursor(52, bottomTextY);
  display.write(modValue);

  display.display();
}



void UiDisplay::renderOutputParameter(const GlobalState& state, const UiState& uiState) {
  display.clearDisplay();
  renderPlayPause(state.isPlaying());

  display.setTextColor(WHITE);

  Parameters::Definition paramDef = Parameters::ALL_PARAMETERS[uiState.getCurrentParameterIndex()];

  // output label & value
  display.setTextSize(1);
  display.setCursor(9, topTextY);
  display.printf("OUTPUT:%u", uiState.getCurrentOutputIndex() + 1);

  // param label
  display.setTextSize(3);
  display.setCursor(12, bottomTextY);
  display.print(paramDef.displayName);

  display.drawLine(72, 4, 72, 60, WHITE);
  display.drawLine(73, 4, 73, 60, WHITE);

  // param value label
  display.setTextSize(1);
  display.setCursor(98, topTextY);
  display.write("%");

  // param value
  OutputState output = state.getOutputReadOnly(uiState.getCurrentOutputIndex());
  unsigned int value = Utils::floatToPercent(output.getParameterValue(paramDef.type));
  if (uiState.isEditing()) {
    display.setTextColor(BLACK);
    value = uiState.getCurrentParameterValue();
    if (value < 100) {
      display.fillRect(79, bottomTextY - 4, 42, 29, WHITE);
    } else {
      display.fillRect(76, bottomTextY - 4, 50, 29, WHITE);
    }
  }
  display.setTextSize(3);
  if (value < 100) {
    display.setCursor(83, bottomTextY);
  } else {
    display.setCursor(74, bottomTextY);
  }

  display.print(value);


  display.display();
}

void UiDisplay::renderPlayPause(bool isPlaying) {
  display.setTextColor(WHITE);
  display.setTextSize(1);
  if (isPlaying) {
    display.drawChar(120, 5, 0x10, WHITE, BLACK, 1);
  } else {
    display.drawChar(120, 5, 0xDC, WHITE, BLACK, 1);
    display.drawChar(124, 5, 0xDC, WHITE, BLACK, 1);
  }
}

void UiDisplay::renderError() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(49, 14);
  display.print("x");
  display.setCursor(73, 14);
  display.print("x");

  // ⌐ ── ¬
  display.setCursor(56, 26);
  display.write(0xA9);
  display.setCursor(61, 25);
  display.write(0xC3);
  display.setCursor(66, 26);
  display.write(0xAA);

  display.setCursor(49, 44);
  display.print("ERROR");

  display.display();
}