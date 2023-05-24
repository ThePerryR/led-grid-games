#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.h"
#include "GameState.h"

constexpr size_t NUM_GAMES = 1;

class MenuState : public State {
private:
  GameState* games[NUM_GAMES];
  size_t selectedGameIndex;
public:
  MenuState();
  virtual ~MenuState();
  State* handleInput() override;
  void loop() override;
  void selectNextGame();
};

#endif
