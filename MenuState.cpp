#include "MenuState.h"
#include "Tetris.h"  // Include all your game state headers
#include "Snake.h"
#include "ArtShow.h"
#include "LedDisplay.h"
#include "LedIndexes.h"

#define JOYSTICK_THRESHOLD 20

MenuState::MenuState() {
  NUM_GAMES = sizeof(games) / sizeof(games[0]);
  games[0] = new Tetris();  // Add your games here
  games[1] = new Snake();
  selectedGameIndex = 0;
  buttonPressed = false;    // Initialize it as false
}

State* MenuState::handleInput() {
  // If the button was pressed, transition to the selected game's state
  if (buttonPressed) {
    buttonPressed = false;  // Reset the button press state
    return games[selectedGameIndex];  // Return the selected game's state
  }
  return nullptr;  // Stay in the current state
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

  // Show which menu option is selected
  int selectedIndex = startRow + selectedGameIndex * 2;
  int leftLedIndex = ledIndexes[selectedIndex][1]; // leftmost LED of the row
  int rightLedIndex = ledIndexes[selectedIndex][8]; // rightmost LED of the row
  CRGB selectColor = CRGB::White; // Or any other color that you'd like
  LedDisplay::getLeds()[leftLedIndex] = selectColor;
  LedDisplay::getLeds()[rightLedIndex] = selectColor;

  // Update the LEDs
  FastLED.show();
}
// Add this to your class definition
int lastJoystickY = 0;
unsigned long lastMoveTime = 0; // Last time the joystick moved
const unsigned long joystickMoveInterval = 320; 
void MenuState::updateJoystick(int xValue, int yValue, bool switchState, bool isButtonPressed) {
    // Handle button press
    if (isButtonPressed) {
      buttonPressed = true;  // Set it to true when the joystick's button is pressed
    }

   // Handle joystick movements
  if (abs(yValue - 512) > JOYSTICK_THRESHOLD) {
      unsigned long currentTime = millis();
      if (currentTime - lastMoveTime >= joystickMoveInterval) {
          if ((yValue - 512) > 0 && (lastJoystickY - 512) >= 0) {
              Serial.println("UP");
              selectedGameIndex = (selectedGameIndex + 1) % NUM_GAMES; // joystick moved up
              lastMoveTime = currentTime; // Update the last move time
          } else if ((yValue - 512) < 0 && (lastJoystickY - 512) <= 0) {
              Serial.println("DOWN");
              selectedGameIndex = (selectedGameIndex + NUM_GAMES - 1) % NUM_GAMES; // joystick moved down
              lastMoveTime = currentTime; // Update the last move time
          }
      }
  }
  lastJoystickY = yValue; // remember the last y position
}

MenuState::~MenuState() {
}

