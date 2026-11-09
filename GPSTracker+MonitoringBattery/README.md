# 🛰️ IoT Real-Time GPS Tracking & Battery Telemetry System

A compact, wireless asset tracking system built with the **ESP32** microcontroller and the **u-blox NEO-6M GPS** module. This device tracks real-time geographic coordinates of physical objects and transmits telemetry data—including location coordinates and remaining battery percentage—to a centralized cloud monitoring dashboard.

---

## 📌 Key Features

* **Real-Time Geospatial Tracking:** Obtains precise latitude, longitude, altitude, and speed via multi-satellite constellation tracking.
* **Battery Level Monitoring:** Measures remaining battery voltage and percentage using an analog voltage divider circuit with a $100\text{ k}\Omega$ resistor network.
* **Integrated Power Management:** Rechargeable lithium-ion battery support with an onboard TP4056 charging module.
* **Cloud Dashboard Visualization:** Transmits payload telemetry over wireless protocols (Wi-Fi / MQTT / HTTP) for real-time map plotting and battery state-of-charge (SoC) analytics.
* **Ultra-Low Power Optimization:** Capable of entering deep-sleep modes between GPS transmission intervals to maximize operating lifespan.

---

## ⚙️ How It Works

```
 ┌─────────────────┐       ┌─────────────────┐
 │ Li-ion Battery  │ ────► │ TP4056 Charger  │ ────► System 3.3V / 5V Bus
 └────────┬────────┘       └─────────────────┘              │
          │                                                 ▼
          │ (Voltage Divider via 100kΩ)             ┌───────────────┐
          └───────────────────────────────────────► │     ESP32     │ ◄─── (UART TX/RX) ─── [ NEO-6M GPS Module ]
                                                    │Microcontroller│                             ▲
                                                    └───────┬───────┘                             │
                                                            │                              (Satellite Signals)
                                                            ▼ (Wi-Fi / MQTT / HTTP)               │
                                                    ┌───────────────┐                     📡 GNSS Satellites
                                                    │ Cloud / Web   │
                                                    │  Dashboard    │ (Live Map & Battery Gauge)
                                                    └───────────────┘
```

1. **System Power-Up:** The lithium battery supplies current through the charging and regulation module, powering up the ESP32 and NEO-6M GPS sensor.
2. **Satellite Acquisition:** Upon boot, the NEO-6M search engine locks onto available GNSS satellite signals, indicated by its onboard fix LED.
3. **NMEA Data Stream:** Once locked, the GPS module streams standardized NMEA sentences ($GPRMC, $GPGGA) over serial communication (UART) to the ESP32.
4. **Data Parsing & Battery Calculation:**
   * The ESP32 parses valid coordinate points (Latitude, Longitude) using the `TinyGPS++` library.
   * Concurrently, the ESP32 reads the analog voltage across the $100\text{ k}\Omega$ resistor divider network on an ADC pin, calculating the battery level:
     $$V_{\text{bat}} = V_{\text{ADC}} \times \left( \frac{R_1 + R_2}{R_2} \right)$$
5. **Telemetry Transmission:** The compiled payload (coordinates, timestamp, and battery percentage) is published to the monitoring dashboard for remote visualization.

---

## 🛠️ Hardware Specifications

| Component | Quantity | Role / Description |
| :--- | :---: | :--- |
| **ESP32 Development Board** | 1 | 32-bit dual-core MCU with built-in Wi-Fi & Bluetooth |
| **u-blox NEO-6M GPS Module** | 1 | High-precision position engine with ceramic patch antenna |
| **Lithium Battery (18650 / LiPo 3.7V)** | 1 | Primary portable power source |
| **TP4056 Charging Module** | 1 | Constant-current/constant-voltage (CC/CV) Li-ion charge controller |
| **$100\text{ k}\Omega$ Resistor** | 1+ | Precision resistor for voltage divider ADC measurement |
| **Enclosure & Wiring** | — | Portable casing and jumper connections |

---

## 🔌 Pin Configuration

| Component Pin | ESP32 Pin | Function / Description |
| :--- | :--- | :--- |
| **NEO-6M VCC** | `3.3V` / `5V` | Module power input |
| **NEO-6M GND** | `GND` | Common ground rail |
| **NEO-6M TX** | `GPIO 4` (RX2) | Hardware Serial data from GPS to ESP32 |
| **NEO-6M RX** | `GPIO 2` (TX2) | Serial commands from ESP32 to GPS |
| **TP4056 OUT+** | `VIN` / `5V` | Power supply line to MCU |
| **TP4056 OUT-** | `GND` | System common ground |
| **Battery Divider Node** | `GPIO 33` | Analog voltage input for battery percentage sensing |

---

## 🖥️ Monitoring Dashboard

The cloud/local web dashboard provides the operator with:

* **Interactive Map:** Displays marker pins pinpointing the tracked asset with automatic updates.
* **Coordinate History:** Breadcrumb trails logging path movements, speed, and timestamps.
* **Battery Gauge Widget:** Visual progress meter displaying real-time battery status ($0\%\text{--}100\%$) with low-battery warning alerts.
* **Device Telemetry Status:** Connection heartbeat and satellite fix status indicator.

---

## 🚀 Getting Started

### 1. Software Prerequisites
* [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/)
* Install the following libraries via the Library Manager:
  * `TinyGPSPlus` (by Mikal Hart)
  * `WiFi` (Built-in ESP32)
  * `PubSubClient` (if using MQTT) or `ArduinoJson`

### 2. Calibration & Configuration
1. Update your network credentials (`SSID`, `PASSWORD`) and dashboard endpoints in the configuration file.
2. Calibrate the ADC conversion factor against a multimeter measurement to ensure accurate battery percentage readouts.
3. Flash the code to the ESP32 board.

### 3. Field Testing
* Position the device outdoors with an unobstructed view of the sky for the initial satellite lock (Cold Start typically takes 30–60 seconds).
* Open the serial monitor at `115200 baud` to verify NMEA coordinate extraction.

---

## 📜 License

This project is licensed under the [MIT License](LICENSE) - you are free to use, modify, and distribute it for personal and commercial applications.
