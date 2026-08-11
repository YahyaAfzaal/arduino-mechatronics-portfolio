/*
  Project 05: Sound-Activated Security Light

  Components: Sound sensor DO (pin 2), Red LED (pin 5), Green LED (pin 6),
              Passive buzzer (pin 9)
*/

const int soundPin  = 2;
const int redPin    = 5;
const int greenPin  = 6;
const int buzzerPin = 9;

unsigned long lastClapTime = 0;
int clapCount = 0;
const unsigned long clapWindow = 1000;   // ms allowed between two claps

void setup() {
  pinMode(soundPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  setSafeState();
}

void loop() {
  bool soundDetected = (digitalRead(soundPin) == HIGH);

  if (soundDetected) {
    unsigned long now = millis();

    if (now - lastClapTime <= clapWindow) {
      clapCount++;              // second clap arrived in time
    } else {
      clapCount = 1;            // too slow — start counting again
    }
    lastClapTime = now;

    triggerAlarm();

    if (clapCount >= 2) {
      tone(buzzerPin, 1500, 1000);   // double-clap: extended alert
      delay(1000);
      clapCount = 0;
    }

    delay(300);                 // debounce — one clap rings for a while
  } else {
    setSafeState();
  }
}

void triggerAlarm() {
  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, HIGH);
  tone(buzzerPin, 1000, 300);
  delay(300);
}

void setSafeState() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  noTone(buzzerPin);
}
