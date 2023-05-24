#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include <FastLED.h>

class GameState : public State {
protected:
  CRGB color;  // Each game can have a unique color
public:
  GameState(CRGB color) : color(color) {}
  virtual ~GameState() {}  // Ensure destructor is virtual

  // Getter for the color
  CRGB getColor() { return color; }

  // The game-specific logic would be implemented in the subclasses
};

#endif