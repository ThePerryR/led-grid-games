#include <FastLED.h>
#include "Button.h"
#include "LedDisplay.h"
#include "MenuState.h"

constexpr uint8_t DATA_PIN = 24;
constexpr uint8_t BUTTON_PIN = 26;

Button button(BUTTON_PIN);
State* currentState;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(LedDisplay::getLeds(), LedDisplay::getNumLeds());
  button.setup();
  currentState = new MenuState();
}

void loop() {
  if (button.isPressed()) {
    State* newState = currentState->handleInput();
    if (newState != nullptr) {
      delete currentState;
      currentState = newState;
    }
  }
  currentState->loop();
}
