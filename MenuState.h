#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.h"
#include "GameState.h"
#include "Tetris.h"
#include "ArtShow.h"
#include "Snake.h"

class MenuState : public State {
private:
  GameState* games[3] = { new Tetris(), new Snake(), new ArtShow() };
  size_t NUM_GAMES;
  size_t selectedGameIndex;
  bool buttonPressed;
public:
  MenuState();
  virtual ~MenuState();
  State* handleInput() override;
  void loop() override;
  void selectNextGame();
  virtual void updateJoystick(int xValue, int yValue, bool switchState, bool isButtonPressed) override;
};

#endif