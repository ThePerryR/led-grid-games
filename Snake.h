#ifndef SNAKE_H
#define SNAKE_H

#include "GameState.h"

class Snake : public GameState {
public:
  Snake() : GameState(CRGB(0x00FF00)) {}  // Choose a color for this game
  State* handleInput() override;
  void loop() override;
};

#endif
