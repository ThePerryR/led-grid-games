#ifndef TETRIS_H
#define TETRIS_H

#include "GameState.h"

#define GRID_WIDTH 10
#define GRID_HEIGHT 25

struct Tetromino {
  int x;        // X position
  int y;        // Y position
  int rotation; // Current rotation
  int shape[4][4]; // Shape of the tetromino
};

class Tetris : public GameState {
public:
  Tetris();  // Constructor declaration
  State* handleInput() override;
  void loop() override;
  virtual void updateJoystick(int xValue, int yValue, bool switchState, bool isButtonPressed) override;

private:
  void renderTetromino(const Tetromino& tetromino);
  void updateTetromino();
  bool isColliding(const Tetromino& tetromino);
  void moveTetromino(int dx, int dy);
  void rotateTetromino();

  Tetromino currentTetromino;
  int grid[GRID_HEIGHT][GRID_WIDTH];

  bool buttonPressed;  // Add this line
};

#endif
