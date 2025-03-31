#pragma once

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../GlobalState/GlobalState.h"
#include "../UiState/UiState.h"
#include "../ModifierDefinitions.h"
#include "../ParameterDefinitions.h"
#include "../Utils.h"
#include "./Bitmaps.h"

#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32


class UiDisplay {
  private:
    Adafruit_SSD1306 display;

    void renderWelcome();
    void renderBpm(const GlobalState& state, const UiState& uiState);
    void renderOutputModifier(const GlobalState& state, const UiState& uiState);
    void renderOutputParameter(const GlobalState& state, const UiState& uiState);
    void renderError();

    void renderPlayPause(bool isPlaying);

    const unsigned int topTextY = 10;
    const unsigned int bottomTextY = 30;
  public:
    UiDisplay();
    void init();
    void update(const GlobalState& state, const UiState& uiState);
};
