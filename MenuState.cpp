#include "MenuState.h"
#include "Tetris.h"  // Include all your game state headers
#include "Snake.h"
#include "LedDisplay.h"
#include "LedIndexes.h"

MenuState::MenuState() {
  NUM_GAMES = sizeof(games) / sizeof(games[0]);
  games[0] = new Tetris();  // Add your games here
  games[1] = new Snake();
  selectedGameIndex = 0;
}

State* MenuState::handleInput() {
    // handle the input and return the next state
    return nullptr;  // for now, return nullptr
}

void MenuState::loop() {
  // Clear the grid
  LedDisplay::clearGrid();

  // Calculate the starting row for the first game to center the menu
  int startRow = (25 - NUM_GAMES * 2 + 1) / 2;

  // Render the menu
  for (size_t i = 0; i < NUM_GAMES; i++) {
    // Get the color of the game
    CRGB color = games[i]->getColor();

    // Determine the row for this game
    int row = startRow + i * 2;

    // Render a row of LEDs for this game
    // Note the start of the loop is now at 2, and the end is at < 8
    for (int j = 2; j < 8; j++) {
      int index = ledIndexes[row][j];
      LedDisplay::getLeds()[index] = color;
    }
  }

  // Update the LEDs
  FastLED.show();
}

MenuState::~MenuState() {
  for (size_t i = 0; i < NUM_GAMES; i++) {
    delete games[i];
  }
}

