# ⚡ Shock Alert System

A real-time AC voltage monitoring and SMS alert system built on **Arduino Nano** using the **ZMPT101B** voltage sensor, **SSD1306 OLED display**, and **SIM800L GSM module**. When a dangerous voltage spike is detected (above 50V), the system automatically sends an SMS alert with a GPS location link to a predefined emergency contact.

---

## 📸 Project Overview

```
[AC Line] ──► [ZMPT101B Sensor] ──► [Arduino Nano] ──► [SSD1306 OLED]
                                          │
                                     [SIM800L GSM]
                                          │
                                    SMS Alert 📱
```

---

## 🧰 Hardware Requirements

| Component              | Specification / Model       | Quantity |
|------------------------|-----------------------------|----------|
| Microcontroller        | Arduino Nano                | 1        |
| AC Voltage Sensor      | ZMPT101B                    | 1        |
| Display                | SSD1306 OLED (128×64, I2C)  | 1        |
| GSM Module             | SIM800L                     | 1        |
| SIM Card               | Any GSM-enabled SIM         | 1        |
| Power Supply           | 5V (for Arduino + SIM800L)  | 1        |
| Connecting Wires       | Jumper wires (M-M / M-F)    | As needed|
| Breadboard / PCB       | —                           | 1        |

> ⚠️ **Safety Warning:** The ZMPT101B sensor interfaces with mains AC voltage. Ensure proper insulation and follow electrical safety practices. Do not touch live terminals. This project is intended for individuals trained in electrical safety.

---

## 📦 Software & Libraries

Install the following libraries via **Arduino Library Manager** (`Sketch → Include Library → Manage Libraries`):

| Library                  | Purpose                        |
|--------------------------|--------------------------------|
| `Adafruit SSD1306`       | OLED display driver            |
| `Adafruit GFX Library`   | Graphics primitives for OLED   |
| `ZMPT101B`               | AC RMS voltage measurement     |
| `SoftwareSerial`         | UART for SIM800L communication |
| `Wire`                   | I2C communication (built-in)   |

---

## 🔌 Pin Configuration

### ZMPT101B → Arduino Nano

| ZMPT101B Pin | Arduino Nano Pin |
|--------------|-----------------|
| OUT (AO)     | A0              |
| VCC          | 5V              |
| GND          | GND             |

### SSD1306 OLED → Arduino Nano (I2C)

| OLED Pin | Arduino Nano Pin |
|----------|-----------------|
| VCC      | 3.3V / 5V       |
| GND      | GND             |
| SDA      | A4              |
| SCL      | A5              |

### SIM800L → Arduino Nano (SoftwareSerial)

| SIM800L Pin | Arduino Nano Pin |
|-------------|-----------------|
| TXD         | D5 (RX)         |
| RXD         | D6 (TX)         |
| VCC         | 4.2V (external) |
| GND         | GND             |

> ⚠️ **Note:** SIM800L requires a stable **3.7–4.2V supply at up to 2A** peak. Do **not** power it directly from Arduino's 5V pin. Use a dedicated Li-Ion cell or a proper buck converter.

---

## ⚙️ How It Works

1. **Boot Sequence:** On startup, the OLED displays initialization messages and checks SIM800L connectivity.
2. **Voltage Monitoring:** The ZMPT101B sensor continuously reads AC RMS voltage on analog pin `A0`.
3. **OLED Display:** Live voltage readings are rendered on the OLED in large text (128×64 pixels) every second.
4. **Threshold Detection:** If voltage exceeds **50V RMS**, the system triggers an SMS alert.
5. **SMS Alert:** The SIM800L sends a pre-configured SMS with a **Google Maps GPS location link** to the emergency contact number.
6. **Alert Confirmation:** The OLED displays "SMS Sent Successfully!" after the message is dispatched.

---

## 📲 SMS Alert Format

When a voltage spike is detected (>50V), the following SMS is sent:

```
Shock Alert https://maps.google.com/?q=<LAT>,<LON>
```

> 💡 The GPS coordinates are currently **hardcoded** in the firmware. For dynamic location tracking, integrate a **GPS module (e.g., NEO-6M)** in future revisions.

---

## 🛠️ Configuration

Edit the following values in the source code before uploading:

```cpp
// Voltage threshold (in Volts RMS) to trigger alert
if (voltage > 50) { sms(); }

// Emergency contact number (with country code)
sendSMS("+91XXXXXXXXXX", "Shock Alert https://maps.google.com/?q=LAT,LON");

// ZMPT101B Sensitivity (calibrate per sensor unit)
#define SENSITIVITY 500.0f

// AC Mains Frequency
ZMPT101B voltageSensor(A0, 50.0);   // 50 Hz for India; use 60.0 for USA
```

---

## 📋 Calibration Guide

The ZMPT101B sensitivity value varies per unit. To calibrate:

1. Connect a known AC voltage source (e.g., a regulated transformer output).
2. Use a multimeter to read the actual RMS voltage.
3. Adjust `SENSITIVITY` in the code until `voltageSensor.getRmsVoltage()` matches the multimeter reading.
4. Typical range: **400.0 – 600.0**

---

## 🗂️ Project Structure

```
shock-alert-system/
├── shock_alert_system.ino      # Main Arduino sketch
├── README.md                   # Project documentation
└── schematic/
    └── circuit_diagram.png     # (Add your schematic here)
```

---

## 🚀 Getting Started

1. **Clone / Download** this repository.
2. **Install** all required libraries listed above.
3. **Edit** the phone number and GPS coordinates in the sketch.
4. **Calibrate** the ZMPT101B sensitivity for your unit.
5. **Wire** the components as per the pin configuration table.
6. **Upload** the sketch to Arduino Nano via Arduino IDE.
7. Open **Serial Monitor** (9600 baud) to debug voltage readings.

---

## 🔮 Future Improvements

- [ ] Integrate NEO-6M GPS module for real-time dynamic location in SMS
- [ ] Add alert cooldown timer to prevent repeated SMS on sustained spike
- [ ] Add a buzzer for local audio alert
- [ ] Log voltage readings to SD card for post-event analysis
- [ ] Wi-Fi version using ESP32 + Telegram / WhatsApp Bot alerts
- [ ] PCB design for a compact enclosure-ready form factor

---

## ⚠️ Disclaimer

This project involves **mains AC voltage**, which is **lethal**. It is intended for **educational and prototyping purposes only**. The author assumes no responsibility for any injury, damage, or misuse arising from this project. Always follow local electrical safety regulations and consult a qualified electrician before working with mains power.

---

## 👨‍💻 Author

**Pankaj Joshi**
- 🌐 [theelectronicscreator.com](https://theelectronicscreator.com)
- 📺 [YouTube – The Electronics Creator](https://youtube.com/@theelectronicscreator)
- 💻 [GitHub – pankajjoshiyt](https://github.com/pankajjoshiyt)

---

## 📄 License

This project is open-source under the [MIT License](LICENSE).
