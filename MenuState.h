#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.h"
#include "GameState.h"
#include "Tetris.h"
#include "Snake.h"

class MenuState : public State {
private:
  GameState* games[2] = { new Tetris(), new Snake() };
  size_t NUM_GAMES;
  size_t selectedGameIndex;
public:
  MenuState();
  virtual ~MenuState();
  State* handleInput() override;
  void loop() override;
  void selectNextGame();
};

#endif
