# Pin Configuration – Smart Rider Safety System

This document describes the Arduino pin connections used for helmet
detection, alcohol detection, eye blink detection, and motor control.

---

## Microcontroller
- Board: Arduino UNO / Nano
- Operating Voltage: 5V
- Logic Level: 5V

---

## Sensor & Actuator Pin Mapping

| Component | Sensor Type | Arduino Pin | Pin Mode | Description |
|---------|------------|-------------|----------|-------------|
| IR Eye Blink Sensor | Digital | D2 | INPUT | Detects eye closure (LOW = eyes closed) |
| MQ-5 Alcohol Sensor | Analog | A0 | INPUT | Detects alcohol level from breath |
| Ultrasonic Sensor (Trig) | HC-SR04 | D8 | OUTPUT | Sends ultrasonic pulse |
| Ultrasonic Sensor (Echo) | HC-SR04 | D9 | INPUT | Receives echo signal |
| Buzzer | Active Buzzer | D12 | OUTPUT | Audible warning |
| LED Indicator | On-board / External | D13 | OUTPUT | Visual alert |
| Motor Relay / Driver | Relay / Driver | D7 | OUTPUT | Controls motor ON/OFF |

---

## Threshold Values

| Parameter | Value | Description |
|---------|------|-------------|
| Alcohol Threshold | 400 | Alcohol detection limit (adjust after calibration) |
| Helmet Distance | 10 cm | Distance below this means helmet is worn |

---

## Logic Conditions

| Condition | Action |
|---------|--------|
| Helmet not worn | Motor OFF, Alarm ON |
| Alcohol detected | Motor OFF, Alarm ON |
| Eyes closed | Motor OFF, Alarm ON |
| All safe | Motor ON, Alarm OFF |

---

## Power Connections

- Arduino 5V → Sensors VCC
- Arduino GND → Sensors GND
- Motor powered via external supply through relay
- **All grounds must be common**

---

## Notes & Best Practices

- Allow MQ-5 sensor **5–10 seconds warm-up**
- Do not power motor directly from Arduino
- Use relay or motor driver for motor control
- Adjust thresholds based on real testing

---

## Firmware File

