#ifndef TETRIS_H
#define TETRIS_H

#include "GameState.h"

class Tetris : public GameState {
public:
  Tetris() : GameState(CRGB::Cyan) {}  // Choose a color for this game
  State* handleInput() override;
  void loop() override;
};

#endif
