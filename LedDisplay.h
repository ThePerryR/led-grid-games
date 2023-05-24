#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include <FastLED.h>

class LedDisplay {
private:
  static constexpr uint16_t NUM_LEDS = 250;
  static CRGB leds[NUM_LEDS];
public:
  static CRGB* getLeds() { return leds; }
  static uint16_t getNumLeds() { return NUM_LEDS; }
  static void clearGrid();
};

#endif
