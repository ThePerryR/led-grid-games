#include "Tetris.h"
#include "MenuState.h"

State* Tetris::handleInput() {
  // When the button is pressed, go back to the menu
  return new MenuState();
}

void Tetris::loop() {
  // Implement the game logic here
  // You can use the color member variable when controlling the LED grid
}
