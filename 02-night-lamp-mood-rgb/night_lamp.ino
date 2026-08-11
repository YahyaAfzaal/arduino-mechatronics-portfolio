/*
  Project 02: Automatic Night Lamp with Mood RGB

  Components: LDR (A0), Potentiometer (A1), RGB LED (pins 5, 6, 9 — PWM)
  Note: a white LED is used in place of blue on pin 9.
*/

const int ldrPin = A0;
const int potPin = A1;

const int redPin   = 5;
const int greenPin = 6;
const int bluePin  = 9;

const int darkThreshold = 500;   // tune for your LDR and room

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  int potValue = analogRead(potPin);

  if (ldrValue < darkThreshold) {
    // Dark -> lamp ON, colour chosen by the potentiometer
    int hue = map(potValue, 0, 1023, 0, 255);
    int r, g, b;
    hueToRGB(hue, r, g, b);
    analogWrite(redPin, r);
    analogWrite(greenPin, g);
    analogWrite(bluePin, b);
  } else {
    // Bright -> lamp OFF
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }

  delay(50);
}

// Convert a hue (0-255) into R, G, B components at full saturation
void hueToRGB(int hue, int &r, int &g, int &b) {
  int region    = hue / 43;
  int remainder = (hue - (region * 43)) * 6;

  int p = 0;
  int q = 255 - ((255 * remainder) >> 8);
  int t = (255 * remainder) >> 8;

  switch (region) {
    case 0:  r = 255; g = t;   b = p;   break;
    case 1:  r = q;   g = 255; b = p;   break;
    case 2:  r = p;   g = 255; b = t;   break;
    case 3:  r = p;   g = q;   b = 255; break;
    case 4:  r = t;   g = p;   b = 255; break;
    default: r = 255; g = p;   b = q;   break;
  }
}
