#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
private:
  uint8_t pin;
  bool lastButtonState;
  unsigned long lastDebounceTime;
  static constexpr unsigned long DEBOUNCE_DELAY = 50;  // Let's say it's 50ms

public:
  explicit Button(uint8_t pin) : pin(pin), lastButtonState(HIGH), lastDebounceTime(0) {}

  void setup() {
    pinMode(pin, INPUT_PULLUP);
  }

  bool isPressed() {
    bool reading = digitalRead(pin);
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }
    bool pressed = !reading && (millis() - lastDebounceTime > DEBOUNCE_DELAY);
    lastButtonState = reading;
    return pressed;
  }
};

#endif
