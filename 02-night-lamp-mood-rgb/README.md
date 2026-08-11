# 02 — Night Lamp with Mood RGB

A lamp that switches itself on when the room gets dark, in a colour you pick with
a knob.

## Demo

https://github.com/user-attachments/assets/03e9187c-1816-4165-b0d2-416f4cbd88ab

## How it works

Two analog inputs drive everything. The **LDR** sits in a voltage divider with a
10 kΩ resistor, so `analogRead()` returns a number that tracks room brightness.
In this kit the reading is non-inverted — more light gives a higher number — so
the lamp turns on when the value falls *below* `darkThreshold`.

The **potentiometer** feeds a second analog pin. Its 0–1023 range is mapped to a
hue value of 0–255, and `hueToRGB()` converts that single number into three PWM
values. This is why one knob can sweep through the whole colour wheel instead of
needing three separate controls.

All three LED pins (5, 6, 9) are PWM-capable, which is what makes colour mixing
possible — `analogWrite()` varies brightness rather than just switching on/off.

## Calibrating the threshold

`darkThreshold = 500` is a starting point, not a magic number. Open the Serial
Monitor, note the reading with the lights on and again with the room dark, then
set the threshold roughly between the two.

## Wiring

| Component | Pin/Leg | Connects to |
|-----------|---------|-------------|
| LDR | leg 1 | 5V |
| LDR | leg 2 | A0, and 10 kΩ resistor → GND |
| 10 kΩ resistor | leg 1 | same node as LDR leg 2 / A0 |
| 10 kΩ resistor | leg 2 | GND |
| Potentiometer | middle (wiper) | A1 |
| Potentiometer | left / right | 5V / GND |
| Red LED | long (+) | resistor → pin 5 |
| Green LED | long (+) | resistor → pin 6 |
| White LED | long (+) | resistor → pin 9 |
| All LEDs | short (−) | GND |

A white LED stands in for blue on pin 9, so the colour sweep is not a true
spectrum — it still mixes smoothly, just with a washed-out end of the range.

## Things to try

- Add hysteresis so the lamp doesn't flicker at the threshold
- Fade in over a second instead of snapping on
