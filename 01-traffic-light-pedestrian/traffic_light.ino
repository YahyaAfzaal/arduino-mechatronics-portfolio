/*
  Project 01: Traffic Light & Pedestrian Crossing System

  Components: Red LED (pin 2), Yellow LED (pin 3), Green LED (pin 4),
  Push button (pin 7, INPUT_PULLUP)
*/

const int redPin = 2;
const int yellowPin = 3;
const int greenPin = 4;
const int buttonPin = 7;

enum State { GREEN, YELLOW, RED, WALK };
State currentState = GREEN;

unsigned long stateStartTime = 0;
const unsigned long greenDuration  = 5000;
const unsigned long yellowDuration = 2000;
const unsigned long redDuration    = 5000;
const unsigned long walkDuration   = 3000;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  setLights(false, false, true);   // start Green
  stateStartTime = millis();
}

void loop() {
  unsigned long now = millis();
  bool buttonPressed = (digitalRead(buttonPin) == LOW);

  // Pedestrian interrupt: cut the green phase short
  if (buttonPressed && currentState == GREEN) {
    currentState = YELLOW;
    stateStartTime = now;
  }

  switch (currentState) {
    case GREEN:
      setLights(false, false, true);
      if (now - stateStartTime >= greenDuration) {
        currentState = YELLOW;
        stateStartTime = now;
      }
      break;

    case YELLOW:
      setLights(false, true, false);
      if (now - stateStartTime >= yellowDuration) {
        currentState = RED;
        stateStartTime = now;
      }
      break;

    case RED:
      setLights(true, false, false);
      if (now - stateStartTime >= redDuration) {
        currentState = WALK;
        stateStartTime = now;
      }
      break;

    case WALK:
      setLights(true, false, false);   // Red stays on = "Walk" for pedestrians
      if (now - stateStartTime >= walkDuration) {
        currentState = GREEN;
        stateStartTime = now;
      }
      break;
  }
}

void setLights(bool red, bool yellow, bool green) {
  digitalWrite(redPin,    red    ? HIGH : LOW);
  digitalWrite(yellowPin, yellow ? HIGH : LOW);
  digitalWrite(greenPin,  green  ? HIGH : LOW);
}
