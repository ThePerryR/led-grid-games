#include "Snake.h"
#include "MenuState.h"

State* Snake::handleInput() {
  // When the button is pressed, go back to the menu
  return new MenuState();
}

void Snake::loop() {
  // Implement the game logic here
  // You can use the color member variable when controlling the LED grid
}
