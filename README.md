# ⚡ Arduino PowerManagement

[![Check Arduino](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/check-arduino.yml) [![Compile Examples](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/compile-examples.yml) [![Spell Check](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/spell-check.yml/badge.svg)](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/spell-check.yml) [![Sync Labels](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/sync-labels.yml/badge.svg)](https://github.com/cristidragomir97/Arduino_PowerManagement/actions/workflows/sync-labels.yml)

The Arduino Pro Power Management Library serves as a comprehensive and sophisticated toolkit tailored for Arduino Pro boards, encompassing the Portenta H7, Portenta C33, and Nicla Vision. 
This library streamlines the interaction with complex hardware components such as the PF1550 Power Management Integrated Circuit (PMIC) and the MAX17162 LiPo Fuel Gauge. 
By abstracting the intricacies of direct hardware manipulation, it presents a user-friendly, functionality-oriented interface.

Core Components of the Library
The library is organized into three primary objects, each addressing specific aspects of power management:

**Board**:
This object centralizes control over the power distribution within the board. It allows users to enable or disable specific power rails, catering to the needs of energy-efficient designs. 
This level of control not only aids in power conservation but also provides flexibility in managing the board's operational aspects.

**Charger**:
Focused on battery charging dynamics, this object provides a detailed insight into charging parameters. Users can monitor and adjust these parameters, ensuring optimal charging conditions and extending the lifespan of the battery.
Battery:

Dedicated to battery management, this object enables real-time monitoring of battery usage. By keeping track of various battery parameters, users can optimize their applications for better energy efficiency and battery longevity.
Enhanced Power Saving Modes
In addition to power rail management and battery handling, the library introduces advanced power-saving features:

Sleep Mode:

This mode offers a significant reduction in power consumption while maintaining a state of minimal activity. It's ideal for applications requiring periodic wake-ups or brief intervals of inactivity.
Deep Sleep Mode:

For scenarios demanding drastic power conservation, the Deep Sleep Mode drastically reduces the board's power usage. It's suitable for long-duration, battery-dependent applications where occasional wake-ups are sufficient.
By integrating these modes, the library provides a versatile approach to power management, ranging from fine-tuning power distribution to invoking deep power-saving states. This makes it an invaluable resource for developing energy-efficient and battery-conscious Arduino Pro board applications.

## Examples 
* **/examples/Battery** - Demonstrates battery metrics monitoring.
* **/examples/Charger** - Illustrates charger status monitoring and control.
* **/examples/DeepSleep_WakeFromPin** - Demonstrates how wake up the board from deep sleep using a wakeup pin (Available only on Portenta C33)
* **/examples/DeepSleep_WakeFromRTC** - Demonstrates how use the RTC to wake the board from deep sleep. (Available only on Portenta C33)
* **/examples/Powershell** - Provides an interactive shell on the serial port that allows you to interact with any aspect of this library. 

## 👀 Instructions

1. Download and install this library
2. Check compatibility with your platform
3. Check out the examples or read the documentation [here](./docs).


## ✨ Features
* Monitor current and average battery metrics (viltage, current, percentage, temperature)
* Monitor battery health metrics (power cycles, temperature, reported capacity)
* Monitor and control charging
* Save significant amounts of power by sending the boards into Sleep and Deep Sleep modes (only available for Portenta C33 for now)
* Toggle and set voltages on different power rails of the board
    * On Nicla Vision 
        * Enable and disable the external power rail
        * Enable and disable the camera power rail      
        * Change voltage on external power rail
    * On Portenta C33 
        * Enable and disable the external power rail
        * Enable and disable the communication (ESP32, secure element) power rail 
        * Change voltage on the external power rail 
        * Change Reference and analog voltage
        * 
    * On Portenta H7
        * Enable and disable the external power rail
        * Change voltage on external power rail



## 📖 Documentation
For more information about this library please read the documentation [here](./docs).
