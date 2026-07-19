\# Smart Automatic Plant Watering System



An automated, smart irrigation system built with Arduino. This project monitors soil temperature and moisture level to water plants automatically, while offering physical manual overrides through three distinct operating modes.



\---



\## 📌 Key Features

\*   \*\*Three Operational Modes:\*\* 

&#x20;   \*   `AUTO`: Water pumps automatically based on soil moisture thresholds.

&#x20;   \*   `FORCE ON`: Manual override to run the pump indefinitely.

&#x20;   \*   `FORCE OFF`: Manual override to completely disable the pump (useful for maintenance).

\*   \*\*Precision Sensors:\*\* Uses a waterproof DS18B20 sensor for soil temperature and a capacitive soil moisture sensor (resistant to corrosion).

\*   \*\*Safe Power Isolation:\*\* Utilizes a 5V relay module to isolate the Arduino logic board from the high-current DC water pump power circuit.

\*   \*\*Real-time Diagnostics:\*\* Outputs temperature, moisture, active mode, and pump status over the Serial Monitor at 1-second intervals.



\---



\## 🛠️ Hardware Requirements

\*   \*\*Microcontroller:\*\* Arduino Uno (or compatible board)

\*   \*\*Temperature Sensor:\*\* DS18B20 Waterproof Temperature Sensor (requires a `4.7kΩ` pull-up resistor)

\*   \*\*Moisture Sensor:\*\* Capacitive Soil Moisture Sensor v1.2 / v2.0

\*   \*\*Switching:\*\* 5V Single-Channel Relay Module

\*   \*\*Actuator:\*\* 5V-9V DC Submersible Water Pump

\*   \*\*Power Supply:\*\* Separate external battery pack or DC adapter for the water pump (e.g., 4x AA batteries)

\*   \*\*Inputs:\*\* 1x Tactile Push-Button (for mode switching)

\*   \*\*Misc:\*\* Breadboard, jumper wires, tubing, and a water reservoir



\---



\## 🔌 Circuit Wiring \& Connections



> ⚠️ \*\*CRITICAL SAFETY NOTE:\*\* Do not power the DC water pump directly from the Arduino's `5V` pin. The motor's current draw can damage the microcontroller. Always route the pump's power through the relay module connected to an external power source.



\### 1. Control Connections (Relay, Button, Sensors to Arduino)

| Component | Pin on Component | Arduino Pin | Notes |

| :--- | :--- | :--- | :--- |

| \*\*DS18B20 Temp Sensor\*\* | VCC / GND / DATA | 5V / GND / D2 | Place a `4.7kΩ` resistor between VCC and DATA. |

| \*\*Moisture Sensor\*\* | VCC / GND / AOUT | 5V / GND / A0 | Standard capacitive analog output. |

| \*\*Push-Button Switch\*\* | Pin 1 / Pin 2 | D4 / GND | Configured as `INPUT\_PULLUP` in code. |

| \*\*5V Relay Module\*\* | VCC / GND / IN | 5V / GND / D3 | Logic signal side. |



\### 2. High-Current Power Connections (Relay to Pump \& Battery)

\*   \*\*External Battery (+)\*\* ➡️ Relay \*\*COM\*\* (Common) Terminal

\*   Relay \*\*NO\*\* (Normally Open) Terminal ➡️ \*\*Pump (+)\*\* Wire

\*   \*\*Pump (-)\*\* Wire ➡️ \*\*External Battery (-)\*\* Terminal



\---



\## 💻 Software \& Libraries



This project requires the following Arduino libraries. You can install them directly via the Arduino Library Manager (`Sketch` -> `Include Library` -> `Manage Libraries`):



1\.  \*\*OneWire\*\* (by Paul Stoffregen)

2\.  \*\*DallasTemperature\*\* (by Miles Burton)



\### Configuration Notes

Open `automatic\_watering.ino` and adjust the following variable if necessary:

\*   `DRY\_THRESHOLD`: Adjust this value based on your specific capacitive sensor calibration (lower values represent wetter soil; higher values represent drier soil).



\---



\## 🚀 Getting Started



1\. \*\*Clone the repository:\*\*

&#x20;  ```bash

&#x20;  git clone \[https://github.com/Kronos5508/Arduino-smart-watering.git](https://github.com/Kronos5508/Arduino-smart-watering.git)

