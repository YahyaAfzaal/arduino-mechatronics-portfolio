/*
  Project 03: Temperature Monitor (LM35 + parallel LCD1602)

  Components: LM35 (A0), LCD1602 in 4-bit parallel mode, potentiometer (contrast)

  LCD wiring:
    GND -> GND        RS -> pin 7        D4 -> pin 9
    VDD -> 5V         RW -> GND          D5 -> pin 10
    VO  -> pot wiper  E  -> pin 8        D6 -> pin 11
    BLK -> GND        BLA -> 5V          D7 -> pin 12
*/

#include <LiquidCrystal.h>

// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int lm35Pin = A0;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  int lm35Raw = analogRead(lm35Pin);

  float voltage = lm35Raw * (5.0 / 1024.0);   // ADC counts -> volts
  float tempC   = voltage * 100.0;            // LM35 outputs 10 mV per °C

  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(0, 1);
  lcd.print(tempC, 1);
  lcd.print(" C   ");        // trailing spaces clear leftover characters

  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.println(" C");

  delay(500);
}
