#include "LedDisplay.h"

CRGB LedDisplay::leds[NUM_LEDS];

void LedDisplay::clearGrid() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}
