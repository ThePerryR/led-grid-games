#include <FastLED.h>
#include <SPI.h>
#include <Ethernet.h>
#include "Button.h"
#include "LedDisplay.h"
#include "MenuState.h"

constexpr uint8_t DATA_PIN = 1;
constexpr uint8_t BUTTON_PIN = 26;
constexpr uint8_t JOYSTICK_X_PIN = A0;  // Joystick X-axis pin
constexpr uint8_t JOYSTICK_Y_PIN = A1;  // Joystick Y-axis pin
constexpr uint8_t JOYSTICK_SWITCH_PIN = 28;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetClient client;


Button button(BUTTON_PIN);
State* currentState;

void makeGETRequest() {
  char server[] = "httpbin.org";  // replace with your server's address
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /get HTTP/1.1");
    client.println("Host: httpbin.org");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}


void setup() {
  Serial.begin(9600);  // or 57600, or 115200 depending on your needs


  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  // server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());


  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(LedDisplay::getLeds(), LedDisplay::getNumLeds());
  button.setup();
  Serial.println("SETUP");
  currentState = new MenuState();
  Serial.println("SETUP2");

  makeGETRequest();
}

void loop() {
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  State* newState = currentState->handleInput();
  if (newState != nullptr) {
    Serial.println("BIGGG");
    delete currentState;
    currentState = newState;
  }

  int joystickXValue = analogRead(JOYSTICK_X_PIN);
  int joystickYValue = analogRead(JOYSTICK_Y_PIN);
  bool joystickSwitchState = digitalRead(JOYSTICK_SWITCH_PIN);
  bool isButtonPressed = button.isPressed();

  currentState->updateJoystick(joystickXValue, joystickYValue, joystickSwitchState, isButtonPressed);

  currentState->loop();
}
