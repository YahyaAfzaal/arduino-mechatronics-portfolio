# 03 — Temperature Monitor (LM35 + parallel LCD)

Live temperature in °C on a 16×2 character display, read from an analog sensor.

## Demo

https://github.com/user-attachments/assets/45dee3ae-adcc-4d20-b09a-79567cbc7603

## How it works

The **LM35** is a purely analog sensor: it outputs 10 mV for every degree
Celsius. There is no library and no digital protocol — just a voltage on a pin.

Turning that into a temperature takes two steps:

```
voltage = raw * (5.0 / 1024.0)   // 10-bit ADC counts -> volts
tempC   = voltage * 100.0        // 10 mV per °C  ->  × 100
```

The `5.0` is the board's reference voltage and the `1024` comes from the ADC's
10-bit resolution. If the board is powered over a long USB cable and the 5 V rail
sags, every reading shifts — which is exactly why more precise builds use an
external voltage reference.

The display runs in **4-bit parallel mode**: six pins carry control and data
(RS, E, D4–D7) while D0–D3 are left unconnected. Each byte is sent as two
four-bit halves, trading a little speed for four fewer wires. This is the older,
more wiring-heavy alternative to an I2C backpack, which needs only two pins.

The trailing spaces in `lcd.print(" C   ")` are deliberate. The LCD does not
clear itself, so when the reading goes from `25.5` to `9.8` the leftover digit
would otherwise stay on screen.

## Wiring

| Component | Pin | Connects to |
|-----------|-----|-------------|
| LM35 | VCC (left, flat side facing you) | 5V |
| LM35 | OUT (middle) | A0 |
| LM35 | GND (right) | GND |
| LCD1602 | VDD / GND | 5V / GND |
| LCD1602 | VO | potentiometer wiper (contrast) |
| LCD1602 | RS / E | pin 7 / pin 8 |
| LCD1602 | RW | GND |
| LCD1602 | D4 / D5 / D6 / D7 | pins 9 / 10 / 11 / 12 |
| LCD1602 | D0–D3 | leave unconnected |
| LCD1602 | BLA / BLK | 5V / GND |
| Potentiometer | left / right | 5V / GND |

If the screen shows nothing or only black boxes after uploading, turn the
contrast potentiometer slowly — that is almost always the cause, not the code.

## Things to try

- Average several readings to smooth out jitter
- Track and display the minimum and maximum seen so far
