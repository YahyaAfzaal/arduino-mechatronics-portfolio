# 04 — Fire & Intrusion Safety Alarm

Two independent hazards, two distinguishable alarm patterns, one relay output.

## How it works

Both sensors are read as plain digital inputs, but they are **active in opposite
directions** — which is the detail worth understanding here:

- The **fire sensor module** has its own comparator on board. Its digital output
  idles HIGH and is pulled LOW when flame is detected, so the code tests for LOW.
- The **ball switches** are simple tilt contacts. With `INPUT_PULLUP` the pin
  idles HIGH and the switch pulls it LOW when closed — so a HIGH reading means
  the contact has opened, i.e. the enclosure was tilted or moved.

Getting these polarities backwards is the most common way this build fails
silently, and it is not something the wiring diagram tells you — it comes from
how each module is designed.

Fire is checked first in the `if`/`else if` chain, so it wins if both trigger at
once. That ordering is a deliberate safety choice.

The two beep patterns (100 ms vs 400 ms) let someone tell the two alarms apart
from another room without looking at the board.

## Known limitation

The beep functions use `delay()`, so the board is unresponsive while beeping.
For an alarm this is tolerable — it is already in its final state — but the
`millis()` approach from project 01 would be the more robust design, and would
allow the alarm to keep monitoring the other sensor while sounding.

## Wiring

| Component | Pin | Connects to |
|-----------|-----|-------------|
| Fire sensor | VCC / GND | 5V / GND |
| Fire sensor | DO | pin 3 |
| Ball switch ×2 | leg 1 | pin 7 |
| Ball switch ×2 | leg 2 | GND |
| Buzzer | + (longer) | pin 4 |
| Buzzer | − (shorter) | GND |
| Relay | VCC / GND | 5V / GND |
| Relay | IN | pin 8 |

## Things to try

- Rewrite the beeps with `millis()` so both sensors stay live during an alarm
- Add a latch so the alarm stays on until manually reset
