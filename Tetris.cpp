#include "Tetris.h"
#include "LedDisplay.h"
#include "LedIndexes.h"

const int TETROMINO_SIZE = 4;

Tetris::Tetris() : GameState(CRGB::White), currentTetromino{5, 0, 0, {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}}} {
  buttonPressed = false;
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      grid[i][j] = 0;
    }
  }
}

State* Tetris::handleInput() {
  // Implement input handling here.
  // You'll need to read from the joystick and buttons, and update the current tetromino's position and rotation accordingly.
  // Don't forget to check for collisions with the grid edges and existing blocks!
  return nullptr;
}

void Tetris::loop() {
  LedDisplay::clearGrid();

  if (buttonPressed) {
    buttonPressed = false;  // Reset the button press state
    rotateTetromino();
  }
  
  updateTetromino();

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      if (grid[i][j]) {
        LedDisplay::getLeds()[ledIndexes[i][j]] = color;
      }
    }
  }

  renderTetromino(currentTetromino);

  FastLED.show();

  delay(200);
}

void Tetris::updateJoystick(int xValue, int yValue, bool switchState, bool isButtonPressed) {
  // xValue has a range from 0 to 1024
  // Assuming xValue around 512 is the resting position
  // Values significantly less than 512 move the tetromino to the left
  // Values significantly greater than 512 move the tetromino to the right
  if (xValue < 412) {  // Choose a threshold like 412 (512 - 100) to avoid sensitivity
    moveTetromino(-1, 0);  // Move left
  } else if (xValue > 612) {  // Choose a threshold like 612 (512 + 100) to avoid sensitivity
    moveTetromino(1, 0);  // Move right
  }

  // Rotate the tetromino if the button is pressed
  if (isButtonPressed) {
    rotateTetromino();
  }

  // If switchState is true, it implies that the player wants to pause or quit the game
  // We'll handle this in `handleInput()`, so here we just set `buttonPressed`
  if (switchState) {
    buttonPressed = true;
  }
}

void Tetris::renderTetromino(const Tetromino& tetromino) {
  for (int i = 0; i < TETROMINO_SIZE; i++) {
    for (int j = 0; j < TETROMINO_SIZE; j++) {
      if (tetromino.shape[i][j]) {
        int x = tetromino.x + j;
        int y = tetromino.y + i;
        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
          LedDisplay::getLeds()[ledIndexes[y][x]] = color;
        }
      }
    }
  }
}

void Tetris::updateTetromino() {
  moveTetromino(0, 1);
}

bool Tetris::isColliding(const Tetromino& tetromino) {
  for (int i = 0; i < TETROMINO_SIZE; i++) {
    for (int j = 0; j < TETROMINO_SIZE; j++) {
      if (tetromino.shape[i][j]) {
        int x = tetromino.x + j;
        int y = tetromino.y + i;
        if (x < 0 || x >= GRID_WIDTH || y >= GRID_HEIGHT || (y >= 0 && grid[y][x])) {
          return true;
        }
      }
    }
  }
  return false;
}

void Tetris::moveTetromino(int dx, int dy) {
  currentTetromino.x += dx;
  currentTetromino.y += dy;
  if (isColliding(currentTetromino)) {
    currentTetromino.x -= dx;
    currentTetromino.y -= dy;
  }
}

void Tetris::rotateTetromino() {
  int oldRotation = currentTetromino.rotation;
  currentTetromino.rotation = (currentTetromino.rotation + 1) % 4;
  // TODO: Update currentTetromino.shape based on rotation
  if (isColliding(currentTetromino)) {
    currentTetromino.rotation = oldRotation;
    // TODO: Update currentTetromino.shape based on oldRotation
  }
}
