#include "ArtShow.h"
#include "LedDisplay.h"
#include "LedIndexes.h"

const int BALL_SIZE = 2;
const int BALL_SPEED = 1;

ArtShow::ArtShow() : GameState(CRGB::White), ball{5, 12, BALL_SIZE, BALL_SIZE, BALL_SPEED, BALL_SPEED}, hasHitWall(false) {
  // Constructor definition
  gridWidth = LedDisplay::getWidth();
  gridHeight = LedDisplay::getHeight();
}

State* ArtShow::handleInput() {
  // When the button is pressed, go back to the menu
  return nullptr;
}

void ArtShow::loop() {
  // Clear the grid
  LedDisplay::clearGrid();

  // Update ball position
  ball.x += ball.dx;
  ball.y += ball.dy;

  // Check for collision with the edges
  if (ball.x <= 0 || ball.x >= gridWidth - BALL_SIZE) {
    ball.dx *= -1; // Reverse horizontal direction
    hasHitWall = true; // Set the flag to indicate a wall hit
  }

  if (ball.y <= 0 || ball.y >= gridHeight - BALL_SIZE) {
    ball.dy *= -1; // Reverse vertical direction
    hasHitWall = true; // Set the flag to indicate a wall hit
  }

  // Change color if the ball has hit a wall
  if (hasHitWall) {
    color = CRGB(random(256), random(256), random(256)); // Change color randomly
    hasHitWall = false; // Reset the flag
  }

  // Render the ball on the LED grid
  renderBall(ball);

  // Update the LEDs
  FastLED.show();

  // Add delay to control the speed of the animation
  delay(100);
}

void ArtShow::renderBall(const Ball& ball) {
  for (int i = ball.y; i < ball.y + ball.height; i++) {
    for (int j = ball.x; j < ball.x + ball.width; j++) {
      int index = ledIndexes[i][j];
      LedDisplay::getLeds()[index] = color;
    }
  }
}
