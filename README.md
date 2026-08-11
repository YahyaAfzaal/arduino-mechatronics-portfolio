# Arduino Mechatronics Portfolio

A running series of Arduino builds, each one adding a technique the next build
needs. Everything here was wired by hand on a breadboard at home.

Each folder holds the sketch, a wiring table, and an explanation of *why* the
code is written the way it is — not just what it does.

---

## Built so far

| # | Project | Concept introduced |
|---|---------|--------------------|
| [01](01-traffic-light-pedestrian) | **Traffic Light & Pedestrian Crossing** | Finite state machine · non-blocking `millis()` timing · `INPUT_PULLUP` |
| [02](02-night-lamp-mood-rgb) | **Night Lamp with Mood RGB** | Analog input · voltage divider · PWM colour mixing · threshold calibration |
| [03](03-temperature-monitor-lm35) | **Temperature Monitor** | ADC maths · analog sensor scaling · parallel LCD in 4-bit mode |
| [04](04-fire-intrusion-alarm) | **Fire & Intrusion Alarm** | Active-LOW vs active-HIGH inputs · priority logic · relay switching |
| [05](05-sound-activated-light) | **Sound-Activated Security Light** | Event timing windows · software debouncing · `tone()` on a passive buzzer |

## Next in the series

IR remote automation · 8×8 dot matrix with a 74HC595 shift register ·
stepper precision positioning · joystick servo pan ·
**RFID access & logging system** (capstone)

---

## Hardware

Arduino UNO, a 830-point breadboard, and a general-purpose component kit —
LEDs, resistors, LDRs, LM35, fire and sound sensor modules, ball switches,
buzzers, relay, LCD1602, 74HC595, servo, stepper, RFID and a keypad.

## Running a sketch

1. Open the `.ino` file from the project folder in the Arduino IDE
2. Wire the board to match that project's wiring table
3. Select **Arduino UNO** and the correct port, then upload

Any external libraries a sketch needs are listed in its own README.

---

## Notes

Thresholds like `darkThreshold` and the sound sensor's sensitivity are
environment-dependent. They are starting points — expect to check the Serial
Monitor and adjust them for your own room.
