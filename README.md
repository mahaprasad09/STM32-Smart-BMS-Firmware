
# STM32 EV Smart Battery Management System (BMS) Firmware

An embedded C firmware implementation for a Smart Battery Management System (BMS) built for electric vehicle (EV) battery monitoring and safety logic, featuring live cloud telemetry integration via ThingSpeak.

---

## 📌 System Architecture & Features

* **ADC Voltage Sensing:** Converts raw 12-bit ADC signals (0 - 4095) into pin voltage and scales it across a 2:1 resistor divider to monitor full pack potential.
* **Multi-Layer Safety Logic:** Continuous boundary protection rules that control an emergency hardware relay:
  * **Over-Voltage Cutoff:** Triggered if V_battery > 4.2V
  * **Under-Voltage Cutoff:** Triggered if V_battery < 3.0V
  * **Over-Temperature Cutoff:** Triggered if T_pack > 50.0°C
* **Cloud Telemetry:** Pre-formats live diagnostic data into HTTP GET parameter strings for real-time streaming to a ThingSpeak cloud dashboard.

---

## 🛠️ Hardware & Software Stack

| Component | Description |
| :--- | :--- |
| **Microcontroller** | STM32F103C8T6 (ARM Cortex-M3 "Blue Pill") |
| **IDE / Toolchain** | STM32CubeIDE / GNU ARM Embedded Toolchain |
| **Language** | Embedded C (`stdint.h`, `stdio.h`) |
| **Cloud Service** | ThingSpeak IoT Analytics |

---

## 📊 Safety Logic & Relay State Table

| Battery State | Monitored Parameter | Protection Action | Relay Status |
| :--- | :--- | :--- | :--- |
| Normal | 3.0V <= V <= 4.2V and T <= 50°C | System Nominal | 1 (CLOSED / Power ON) |
| Over-Voltage | V > 4.2V | Trip Emergency Relay | 0 (OPEN / Power OFF) |
| Under-Voltage | V < 3.0V | Trip Emergency Relay | 0 (OPEN / Power OFF) |
| Over-Temp | T > 50°C | Trip Emergency Relay | 0 (OPEN / Power OFF) |

---

## 📡 Telemetry Message Format

Sensor readings and safety relay states are continuously serialized into an HTTP-compliant GET telemetry request buffer:

`GET /update?api_key=YOUR_WRITE_API_KEY&field1=VOLTAGE&field2=TEMP&field3=RELAY_STATUS`
