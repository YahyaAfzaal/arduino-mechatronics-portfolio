/*
  Project 04: Fire & Intrusion Safety Alarm

  Components: Fire sensor DO (pin 3), Ball switches (pin 7, INPUT_PULLUP),
              Buzzer (pin 4), Relay IN (pin 8)
*/

const int firePin       = 3;
const int ballSwitchPin = 7;
const int buzzerPin     = 4;
const int relayPin      = 8;

void setup() {
  pinMode(firePin, INPUT);
  pinMode(ballSwitchPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void loop() {
  bool fireDetected      = (digitalRead(firePin) == LOW);        // most modules pull LOW on detect
  bool intrusionDetected = (digitalRead(ballSwitchPin) == HIGH); // tilt / open reads HIGH

  if (fireDetected) {
    digitalWrite(relayPin, HIGH);   // exhaust fan / siren
    fastBeep();
  } else if (intrusionDetected) {
    digitalWrite(relayPin, HIGH);
    slowBeep();
  } else {
    digitalWrite(relayPin, LOW);
    noTone(buzzerPin);
  }
}

void fastBeep() {
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
}

void slowBeep() {
  digitalWrite(buzzerPin, HIGH);
  delay(400);
  digitalWrite(buzzerPin, LOW);
  delay(400);
}
