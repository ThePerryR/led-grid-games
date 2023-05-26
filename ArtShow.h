#ifndef ARTSHOW_H
#define ARTSHOW_H

#include "GameState.h"

struct Ball {
  int x;        // X position
  int y;        // Y position
  int width;    // Width of the ball
  int height;   // Height of the ball
  int dx;       // X velocity (speed and direction)
  int dy;       // Y velocity (speed and direction)
};

class ArtShow : public GameState {
public:
  ArtShow();  // Constructor declaration
  State* handleInput() override;
  void loop() override;

private:
  void renderBall(const Ball& ball);

  Ball ball;
  bool buttonPressed;
  int gridWidth;
  int gridHeight;
  bool hasHitWall;
};

#endif
