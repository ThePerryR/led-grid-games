#ifndef STATE_H
#define STATE_H

class State {
public:
  virtual ~State() {}  // Always make base class destructor virtual
  virtual State* handleInput() = 0;
  virtual void loop() = 0;
  virtual void updateJoystick(int xValue, int yValue, bool switchState, bool isButtonPressed) {}
};

#endif
