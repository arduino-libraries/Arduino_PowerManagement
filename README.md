# ⚡ Arduino PowerManagement

[![Check Arduino](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/check-arduino.yml) [![Compile Examples](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/compile-examples.yml) [![Spell Check](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/spell-check.yml/badge.svg)](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/spell-check.yml) [![Sync Labels](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/sync-labels.yml/badge.svg)](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/sync-labels.yml)

The Arduino Pro Power Management Library serves as a comprehensive and sophisticated power management toolkit tailored for Arduino Pro boards, encompassing the Portenta H7, Portenta C33, and Nicla Vision. 

This library streamlines the interaction with complex hardware components such as the [PF1550 Power Management Integrated Circuit](https://www.nxp.com/docs/en/data-sheet/PF1550.pdf) (PMIC) and the [MAX17262 LiPo Fuel Gauge](https://www.analog.com/media/en/technical-documentation/data-sheets/MAX17262.pdf) and presents a user-friendly, functionality-oriented interface.

## ✅ Supported Boards

- Arduino Portenta H7
- Arduino Nicla Vision (Low power features not supported yet)
- Arduino Portenta C33

## Core Components of the Library
The library is organized into three primary parts, each addressing specific aspects of power management:

### 🔋 Battery
Dedicated to battery management, this class enables real-time monitoring of battery usage and health. By keeping track of various battery parameters, users can optimize their applications for better energy efficiency and battery longevity.

### 🔌 Charger
Focused on battery charging dynamics, this class provides a detailed insight into charging parameters. Users can monitor and adjust these parameters, ensuring optimal charging conditions and extending the lifespan of the battery.

### ⚙️ Board
This class centralizes control over the power distribution within the board. It allows users to enable or disable specific power rails, catering to the needs of energy-efficient designs. 
In addition to power rail management and battery handling, the library provides power-saving features:

-  **Sleep**
This mode offers a significant reduction in power consumption while maintaining a state of minimal activity. 
It's ideal for applications requiring periodic wake-ups or brief intervals of inactivity. This sleep mode resumes the operation from the last operation.
You can manually enable this sleep mode on the Portenta C33, on the H7 and Nicla Vision however, this is automatically handled by mbed. 

- **Deep Sleep**
For scenarios demanding drastic power conservation, the Deep Sleep Mode drastically reduces the board's power usage. It's suitable for long-duration, battery-dependent applications where occasional wake-ups are sufficient. This mode restarts the board on wakeup, effectively running the `setup()` function again. 


## Examples 
- [Battery](./examples/Battery/Battery.ino) - Demonstrates battery metrics monitoring.
- [Charger](./examples/Charger/Charger.ino) - Illustrates charger status monitoring and control.
- [DeepSleep_WakeFromPin](./examples/DeepSleep_WakeFromPin/DeepSleep_WakeFromPin.ino) - Demonstrates how to wake up the board from deep sleep using a wakeup pin.
- [DeepSleep_WakeFromRTC_C33](./examples/DeepSleep_WakeFromRTC/DeepSleep_WakeFromRTC_C33.ino) - Demonstrates how to use the RTC to wake the Portenta C33 from deep sleep.
- [DeepSleep_WakeFromRTC_H7](./examples/DeepSleep_WakeFromRTC/DeepSleep_WakeFromRTC_H7.ino) - Demonstrates how to use the RTC to wake the Portenta H7 from deep sleep.
- [Powershell](./examples/Powershell/Powershell.ino) - Provides an interactive shell on the serial port that allows you to interact with any aspect of this library. 

## 👀 Instructions

1. Check compatibility with your platform
2. Download and install this library through the Arduino IDE, the Arduino CLI or by manually downloading it.
3. Check out the examples or read the documentation [here](./docs).


## ✨ Features
- Monitor current and average battery metrics (voltage, current, percentage, temperature)
- Monitor battery health metrics (power cycles, temperature, reported capacity)
- Monitor and control charging
- Save significant amounts of power by sending the boards into Sleep and Deep Sleep modes (only available for Portenta C33 for now)
- Toggle and set voltages on different power rails of the board
    - On Nicla Vision 
        - Enable and disable the external power rail
        - Enable and disable the camera power rail      
        - Change voltage on external power rail
    - On Portenta C33 
        - Enable and disable the external power rail
        - Enable and disable the communication power rail (ESP32, secure element)
        - Change voltage on the external power rail 
    - On Portenta H7
        - Enable and disable the external power rail
        - Change voltage on external power rail

## 📖 Documentation
For more information on how to use this library please read the documentation [here](./docs).

> [!NOTE]  
> The Low Power functionality on the Portenta H7 and Nicla Vision are still experimental. It works well on some chip revisions while on other chip revisions it will go to sleep and never wake up unless you manually restart the board. If your board doesn't wake up from sleep, please create a Github Issue and let us know your board version. You can find the 4-digit number on the back of the board next to the High Density connector that is on the opposite side from the USB connector. 
