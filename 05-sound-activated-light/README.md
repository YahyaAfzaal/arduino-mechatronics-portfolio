# 05 — Sound-Activated Security Light

A clap-triggered alert that can tell a single clap from a double clap.

## Demo

https://github.com/user-attachments/assets/14337612-b486-4102-afb5-2b49814ba2d1

## How it works

The sound sensor module does the hard part: an on-board potentiometer sets a
sensitivity threshold, and its digital output goes HIGH whenever the noise level
crosses it. The Arduino only sees a yes/no signal, not a volume.

The interesting logic is the **double-clap detection**, and it works purely on
timestamps:

- Every detection records `millis()` into `lastClapTime`
- If the next detection arrives within `clapWindow` (1000 ms), `clapCount` goes up
- If it arrives later, the count resets to 1 — that clap starts a new attempt

So a "double clap" is not two sounds recognised together; it is one sound plus
the memory of how long ago the previous one happened. That pattern — storing a
timestamp and comparing later — is the same idea behind the traffic light's state
timer.

The 300 ms `delay()` is a **debounce**. A single clap is not one clean pulse; it
rattles the sensor several times over a few milliseconds. Without the delay, one
clap would register as three or four and instantly trip the double-clap branch.

Green means idle, red means triggered, and `tone()` drives the passive buzzer at
a chosen frequency — 1000 Hz for a normal alert, 1500 Hz for the double-clap.

## Wiring

| Component | Pin | Connects to |
|-----------|-----|-------------|
| Sound sensor | VCC / GND | 5V / GND |
| Sound sensor | DO | pin 2 |
| Red LED | long (+) | resistor → pin 5 |
| Green LED | long (+) | resistor → pin 6 |
| Both LEDs | short (−) | GND |
| Passive buzzer | + | pin 9 |
| Passive buzzer | − | GND |

The buzzer must be the **passive** one — `tone()` needs to drive the frequency
itself. An active buzzer has its own oscillator and will only ever produce one
pitch.

## Things to try

- Make the double clap toggle the light on/off instead of just beeping louder
- Tune `clapWindow` — too long and unrelated noises pair up as a "double"
