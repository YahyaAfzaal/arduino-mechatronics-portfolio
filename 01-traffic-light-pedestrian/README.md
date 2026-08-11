# 01 — Traffic Light & Pedestrian Crossing

A four-state traffic light that a pedestrian can interrupt with a button press.

## Demo

https://github.com/user-attachments/assets/90e22006-a04a-4df0-9ff5-0517b9a02494

## How it works

The sketch runs a **finite state machine** with four states: `GREEN`, `YELLOW`,
`RED` and `WALK`. Each state knows how long it should last, and `loop()` checks
on every pass whether that time has elapsed.

Timing uses `millis()` rather than `delay()`. This matters: `delay()` freezes the
whole board, so a button press during a delay would be missed entirely. By
comparing `millis() - stateStartTime` against the state's duration, the board
stays responsive the entire time.

The button uses `INPUT_PULLUP`, so the pin idles HIGH and reads LOW when pressed —
no external pull-down resistor needed. Pressing it during `GREEN` jumps straight
to `YELLOW`, cutting the green phase short. Pressing during any other state does
nothing, which is correct: the crossing is already on its way.

## Timings

| State | Duration |
|-------|----------|
| Green | 5 s |
| Yellow | 2 s |
| Red | 5 s |
| Walk | 3 s |

## Wiring

| Component | Leg | Connects to |
|-----------|-----|-------------|
| Red LED | long (+) | 220 Ω resistor → pin 2 |
| Red LED | short (−) | GND |
| Yellow LED | long (+) | 220 Ω resistor → pin 3 |
| Yellow LED | short (−) | GND |
| Green LED | long (+) | 220 Ω resistor → pin 4 |
| Green LED | short (−) | GND |
| Push button | leg 1 | pin 7 |
| Push button | leg 2 | GND (no resistor — internal pull-up is used) |

If only one resistor is available, tie all three LED cathodes to a common node
and run a single 220 Ω resistor from there to GND.

## Things to try

- Change the durations and watch how the cycle feels
- Add a separate pedestrian LED that lights only during `WALK`
- Add a minimum green time so the button can't be spammed
