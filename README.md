# ESP32 Wi-Fi RSSI Motion Detector

A simple beginner-friendly ESP32 project that detects movement using Wi-Fi signal strength changes.

This project uses an **ESP32 DevKit V1** and a nearby Wi-Fi source such as a **phone hotspot** or **Wi-Fi router**. When a person moves between the ESP32 and the Wi-Fi source, the received signal strength changes. The ESP32 detects that change and shows **Motion Detected** in the Serial Monitor while turning on the onboard LED.

---

## Project Goal

The goal of this project is to build a very simple live sensing system using an ESP32.

The ESP32 connects to Wi-Fi and continuously reads the signal strength value known as **RSSI**.

RSSI means:

```text
Received Signal Strength Indicator
```

When a person moves near or between the Wi-Fi source and ESP32, the RSSI value changes. If the change is larger than a defined threshold, the ESP32 assumes motion has happened.

---

## What This Project Can Do

This project can:

* Detect basic movement near the ESP32 and Wi-Fi signal path
* Print live RSSI values in the Serial Monitor
* Turn on the onboard LED when motion is detected
* Work with a phone hotspot or normal Wi-Fi router
* Help you understand the basic idea of Wi-Fi sensing

---

## What This Project Cannot Do

This is a simple RSSI-based project, so it cannot accurately do advanced sensing.

It cannot reliably:

* Detect a completely still person
* Count the number of people
* Detect breathing or heart rate
* Track body pose
* Work as a professional security alarm
* Replace real PIR, radar, camera, or CSI-based sensing systems

This is a first-step experiment before moving into real CSI-based sensing.

---

## Hardware Required

| Component                     | Quantity | Notes                              |
| ----------------------------- | -------: | ---------------------------------- |
| ESP32 DevKit V1               |        1 | Classic ESP32 development board    |
| USB cable                     |        1 | For programming and power          |
| Phone hotspot or Wi-Fi router |        1 | Must support 2.4 GHz Wi-Fi         |
| Laptop/PC                     |        1 | For Arduino IDE and Serial Monitor |

Optional:

| Component    | Purpose                        |
| ------------ | ------------------------------ |
| Buzzer       | Sound alert                    |
| External LED | Visual alert                   |
| OLED display | Show RSSI and detection status |
| Power bank   | Portable testing               |

---

## Recommended Physical Setup

Place the Wi-Fi source and ESP32 apart from each other.

Example:

```text
Phone Hotspot / Router  --->  Walking Area  --->  ESP32 DevKit V1
```

Best testing conditions:

* Keep the phone/router fixed in one position
* Keep the ESP32 fixed in one position
* Keep 2 to 5 meters distance between them
* Walk between the phone/router and ESP32
* Do not move the phone during testing
* Use 2.4 GHz Wi-Fi, not 5 GHz

The ESP32 DevKit V1 usually supports only 2.4 GHz Wi-Fi.

---

## Software Required

Install:

1. Arduino IDE
2. ESP32 board support package for Arduino IDE
3. USB driver if required:

   * CP210x driver, or
   * CH340 driver, depending on your ESP32 board

---

## Arduino IDE Setup

In Arduino IDE:

1. Open Arduino IDE
2. Go to **File > Preferences**
3. Add this URL in **Additional Boards Manager URLs**:

```text
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

4. Go to **Tools > Board > Boards Manager**
5. Search:

```text
esp32
```

6. Install **esp32 by Espressif Systems**
7. Select board:

```text
ESP32 Dev Module
```

8. Select the correct port:

```text
Tools > Port
```

9. Set Serial Monitor baud rate to:

```text
115200
```

---

---

## How to Upload

1. Connect ESP32 DevKit V1 to your laptop
2. Select board:

```text
Tools > Board > ESP32 Arduino > ESP32 Dev Module
```

3. Select port:

```text
Tools > Port > Your ESP32 Port
```

4. Click **Upload**
5. Open Serial Monitor
6. Set baud rate:

```text
115200
```

If upload fails, hold the **BOOT** button on the ESP32 while uploading.

---

## Using Phone Hotspot

You can use your phone hotspot as the Wi-Fi source.

Recommended setup:

```text
Phone Hotspot  --->  Walking Path  --->  ESP32
```

Important:

* Keep the phone still
* Keep the ESP32 still
* Use 2.4 GHz hotspot
* Keep distance around 2 to 5 meters
* Do not test while holding the phone
* Do not move the hotspot after calibration

If your phone has an option like **Maximize Compatibility**, enable it. This usually forces 2.4 GHz Wi-Fi.

---

## Testing Procedure

Follow this order:

1. Place your phone/router in one fixed position
2. Place ESP32 around 2 to 5 meters away
3. Upload the code
4. Open Serial Monitor
5. Keep the area still during calibration
6. Wait until you see:

```text
System Ready!
```

7. Walk between the phone/router and ESP32
8. Watch Serial Monitor

Expected output:

```text
Baseline: -55 dBm | Current: -56 dBm | Difference: 1 | No Motion
Baseline: -55 dBm | Current: -63 dBm | Difference: 8 | Motion Detected!
Baseline: -55 dBm | Current: -54 dBm | Difference: 1 | No Motion
```

---

## Adjusting Sensitivity

The main value to tune is:

```cpp
int threshold = 6;
```

Use this guide:

| Threshold | Sensitivity    | Use Case                                    |
| --------: | -------------- | ------------------------------------------- |
|    3 to 4 | Very sensitive | Detects small changes, more false positives |
|    5 to 7 | Balanced       | Good starting range                         |
|   8 to 12 | Less sensitive | Fewer false positives                       |
|       13+ | Very strict    | Only strong movement detected               |

Recommended starting value:

```cpp
int threshold = 6;
```

If it detects motion even when nobody moves, increase the threshold.

If it does not detect movement, decrease the threshold.

---

## Troubleshooting

### ESP32 cannot connect to Wi-Fi

Check:

* Wi-Fi name is correct
* Password is correct
* Hotspot/router is using 2.4 GHz
* ESP32 is close enough to the Wi-Fi source
* Phone hotspot allows new devices

---

### RSSI value is not changing

Try:

* Increase distance between ESP32 and phone/router
* Walk directly between ESP32 and Wi-Fi source
* Place both devices at table height
* Avoid testing too close, like less than 1 meter
* Try using a normal router instead of phone hotspot

---

### Too many false detections

Try:

```cpp
int threshold = 8;
```

or:

```cpp
int threshold = 10;
```

Also make sure:

* Phone/router is not moving
* ESP32 is not moving
* Room fan is not moving objects near the signal path
* Calibration is done when the room is still

---

### LED is not turning on

Some ESP32 boards use a different onboard LED pin.

Try changing:

```cpp
const int ledPin = 2;
```

to:

```cpp
const int ledPin = 5;
```

or connect an external LED with resistor to a GPIO pin.

---

## Project Folder Structure

Recommended folder structure:

```text
esp32-wifi-motion-detector/
│
├── README.md
│
└── esp32_wifi_motion_detector/
    └── esp32_wifi_motion_detector.ino
```

The Arduino sketch folder and `.ino` file should have the same name.

Example:

```text
esp32_wifi_motion_detector/
esp32_wifi_motion_detector.ino
```

---

## How It Works

The ESP32 connects to a Wi-Fi network and reads RSSI.

RSSI is measured in dBm.

Example values:

```text
-40 dBm = strong signal
-60 dBm = medium signal
-80 dBm = weak signal
```

During startup, the ESP32 calculates a baseline RSSI.

Example:

```text
Baseline RSSI: -55 dBm
```

Then it keeps reading the current RSSI.

If the current RSSI changes too much from the baseline, the ESP32 detects motion.

Example:

```text
Baseline RSSI: -55 dBm
Current RSSI: -63 dBm
Difference: 8
Motion Detected
```

The detection logic is:

```text
If RSSI difference > threshold:
    Motion Detected
Else:
    No Motion
```

---

## Accuracy Notes

This project is experimental.

RSSI is a very basic signal value. It is affected by:

* Human movement
* Walls
* Doors
* Furniture
* Phone/router position
* Wi-Fi interference
* Distance
* Antenna direction
* Other nearby Wi-Fi networks

Because of this, results will not always be perfect.

This is best used as a learning project, not a production security system.

---

## Best Testing Environment

For best results:

* Use a quiet room
* Keep devices fixed
* Avoid too many people moving around
* Use a consistent distance
* Calibrate when nobody is moving
* Keep the ESP32 and phone/router away from metal surfaces
* Test different positions

---

## Possible Improvements

After this basic version works, the project can be improved by adding:

* Moving average filter
* Auto recalibration button
* Buzzer alert
* OLED display
* Web dashboard
* Data logging to CSV
* MQTT integration
* Home Assistant integration
* ESP32 web server
* Real CSI-based sensing using ESP-IDF
* ESP32-S3 upgrade for better sensing experiments

---

## Next Version Ideas

### Version 1

Basic Serial Monitor detection.

### Version 2

Add LED and buzzer alert.

### Version 3

Create a web dashboard hosted on ESP32.

### Version 4

Send detection data to laptop using MQTT or WebSocket.

### Version 5

Use ESP32 CSI instead of RSSI for better sensing.

### Version 6

Upgrade to ESP32-S3 and try advanced CSI sensing platforms.

---

## Example Future Output

A future dashboard could show:

```text
Status: Motion Detected
RSSI: -63 dBm
Baseline: -55 dBm
Difference: 8
Sensitivity: Medium
Wi-Fi: Connected
Device: ESP32 DevKit V1
```

---

## Important Limitation Compared to RuView

RuView-style sensing uses Wi-Fi CSI and is mainly designed for newer boards like ESP32-S3 or ESP32-C6.

This project uses a classic ESP32 DevKit V1 and simple RSSI readings.

So this project is not a replacement for RuView.

It is a beginner-friendly first step toward understanding Wi-Fi-based sensing.

---

## Final Summary

This project proves that a simple ESP32 DevKit V1 can be used for basic Wi-Fi movement detection.

It is simple, cheap, and beginner-friendly.

The best setup is:

```text
Phone Hotspot or Wi-Fi Router  --->  Walking Area  --->  ESP32 DevKit V1
```

Start with RSSI detection first. Once this works, move toward real CSI-based sensing for more accurate and advanced applications.


My love for robotics never ends !!
HEHEHEHE Suwarna This side 