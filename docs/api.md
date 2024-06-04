# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class ` [`Battery`](#class_battery) | This class provides a detailed insight into the battery's health and usage.
`class ` [`Board`](#class_board) | Represents a board with power management capabilities.
`class ` [`Charger`](#class_charger) | Class for controlling charging parameters and monitoring charging status.
`class ` [`MAX1726Driver`](#class_m_a_x1726_driver) | Driver class for the MAX1726 Fuel Gauge IC.
`struct ` [`BatteryCharacteristics`](#struct_battery_characteristics) | This struct contains the characteristics of the battery.

# class `Battery` <a id="class_battery" class="anchor"></a>

This class provides a detailed insight into the battery's health and usage.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Battery`](#class_battery_1a36a6234c583e3b3506f4a77e3eb49989) | Initializes the battery object with default values for capacity (0mAh) and empty voltage (3.3V). |
| [`Battery`](#class_battery_1a64cc106078933ec547418bb649936d0e) | Initializes the battery object with the given battery characteristics. |
| [`begin`](#class_battery_1ad1ef0c48a213f0ad607f08fca6b30d96) | Initializes the battery communication and configuration. |
| [`isConnected`](#class_battery_1af280ded5baecec455934785c317df299) | Checks if a battery is connected to the system. |
| [`voltage`](#class_battery_1add29e37e363157d436d60d2679e4893c) | Reads the current voltage of the battery. Voltage is usually between 3.0V and 4.2V. |
| [`averageVoltage`](#class_battery_1a90aedc34714a42b3ba38e34db6736cf4) | Reads an average of voltage readings of the battery. |
| [`minimumVoltage`](#class_battery_1abde4f669d71076bfc09e4004e3369664) | Returns the minimum voltage value measured since the last device reset. At power-up the minimum voltage value is set to FFh (the maximum). |
| [`maximumVoltage`](#class_battery_1a7baebfaf75aff02842a5eab7ce1629e7) | Returns the maximum voltage value measured since the last device reset. At power-up the maximum voltage value is set to 00h (the minimum). |
| [`resetMaximumMinimumVoltage`](#class_battery_1a2d4bde0fc0207f0a103f67be970cc412) | Resets the minimum and maximum voltage values. |
| [`current`](#class_battery_1addc7658b5425f6bfabb8e55c7f73fd33) | Reads the current flowing from the battery at the moment. Negative values indicate that the battery is charging, positive values indicate that the battery is discharging. When no battery is connected, the value is -1. |
| [`averageCurrent`](#class_battery_1ab74143421658d9aafb05535558a315dc) | Reads an average of current readings of the battery. |
| [`minimumCurrent`](#class_battery_1a04fb9f935964dc4cad7673d581a4e701) | Reads the minimum current values measured since the last device reset. Note: The resolution of the minimum current value is 160mA so the value is rounded to the nearest 160mA. |
| [`maximumCurrent`](#class_battery_1a06bbac275505bd55f54904dde086ea72) | Reads the maximum current values measured since the last device reset. Note: The resolution of the minimum current value is 160mA so the value is rounded to the nearest 160mA. |
| [`resetMaximumMinimumCurrent`](#class_battery_1a86b64cfdb23050cc77a66c1e03750b42) | Resets the minimum and maximum current values. |
| [`power`](#class_battery_1acc75ec11734cdc2f877e11a122ebf164) | Reads the current power of the battery in milliwatts (mW). This value is calculated based on the current and voltage of the battery. |
| [`averagePower`](#class_battery_1a41ff59184770622e77ba133818996793) | Reads an average of power readings of the battery in milliwatts (mW). This value is calculated based on the current and voltage of the battery. |
| [`internalTemperature`](#class_battery_1a3967e87e3ff5bdfbfb99681902d31464) | Reads the current temperature of the internal die of the battery gauge chip. |
| [`averageInternalTemperature`](#class_battery_1a658633cd49a8b594f6a8e75a126e6b5d) | Reads an average of internal temperature readings of the battery. Note: If the battery temperature was read before, this function will change the configuration to read the internal temperature. You will have to await a couple of temperature readings before getting a meaningful average temperature. |
| [`percentage`](#class_battery_1a2f7cd7878c7e3b8227ff38e18c8f65e2) | Reads the battery's state of charge (SOC). This value is based on both the voltage and the current of the battery as well as compensation for the battery's age and temperature and discharge rate. |
| [`remainingCapacity`](#class_battery_1a769e8dddd81779757b8399660b084734) | Reads the remaining capacity of the battery. In combination with [current()](#class_battery_1addc7658b5425f6bfabb8e55c7f73fd33), this value can be used to estimate the remaining time until the battery is empty. |
| [`fullCapacity`](#class_battery_1afb54a909c0fa3e5d7aed34026a441c49) | Returns the full capacity of the battery. For this to work, the capacity of the battery must be set when initializing the battery object.  |
| [`isEmpty`](#class_battery_1a91fab7f1d3534f6f657e5868ee9af95a) | Checks if the battery is empty. Returns false once the cell voltage rises above the recovery threshold. |
| [`timeToEmpty`](#class_battery_1af7775216c6a4278af417f8ebdfd94dbe) | Calculates the estimated time until the battery is empty.  |
| [`timeToFull`](#class_battery_1a6eaae4e71787908063ad64ee58ba09d2) | Calculates the estimated time until the battery is fully charged. The value is determined by learning from the experience of prior charge cycles.  |

## Members

### `Battery` <a id="class_battery_1a36a6234c583e3b3506f4a77e3eb49989" class="anchor"></a>

```cpp
Battery()
```

Initializes the battery object with default values for capacity (0mAh) and empty voltage (3.3V).

<hr />

### `Battery` <a id="class_battery_1a64cc106078933ec547418bb649936d0e" class="anchor"></a>

```cpp
Battery( BatteryCharacteristics batteryCharacteristics)
```

Initializes the battery object with the given battery characteristics.

#### Parameters
* `batteryCharacteristics` The characteristics of the battery.
<hr />

### `begin` <a id="class_battery_1ad1ef0c48a213f0ad607f08fca6b30d96" class="anchor"></a>

```cpp
bool begin(bool enforceReload)
```

Initializes the battery communication and configuration.

#### Parameters
* `enforceReload` If set to true, the battery gauge config will be reloaded. 

#### Returns
True if the initialization was successful, false otherwise.
<hr />

### `isConnected` <a id="class_battery_1af280ded5baecec455934785c317df299" class="anchor"></a>

```cpp
boolean isConnected()
```

Checks if a battery is connected to the system.

#### Returns
True if a battery is connected, false otherwise
<hr />

### `voltage` <a id="class_battery_1add29e37e363157d436d60d2679e4893c" class="anchor"></a>

```cpp
float voltage()
```

Reads the current voltage of the battery. Voltage is usually between 3.0V and 4.2V.

#### Returns
The current voltage in volts (V).
<hr />

### `averageVoltage` <a id="class_battery_1a90aedc34714a42b3ba38e34db6736cf4" class="anchor"></a>

```cpp
float averageVoltage()
```

Reads an average of voltage readings of the battery.

#### Returns
The average voltage in volts (V).
<hr />

### `minimumVoltage` <a id="class_battery_1abde4f669d71076bfc09e4004e3369664" class="anchor"></a>

```cpp
float minimumVoltage()
```

Returns the minimum voltage value measured since the last device reset. At power-up the minimum voltage value is set to FFh (the maximum).

#### Returns
The minimum voltage value in volts (V).
<hr />

### `maximumVoltage` <a id="class_battery_1a7baebfaf75aff02842a5eab7ce1629e7" class="anchor"></a>

```cpp
float maximumVoltage()
```

Returns the maximum voltage value measured since the last device reset. At power-up the maximum voltage value is set to 00h (the minimum).

#### Returns
The maximum voltage value in volts (V).
<hr />

### `resetMaximumMinimumVoltage` <a id="class_battery_1a2d4bde0fc0207f0a103f67be970cc412" class="anchor"></a>

```cpp
bool resetMaximumMinimumVoltage()
```

Resets the minimum and maximum voltage values.

#### Returns
True if the minimum and maximum voltage values were successfully reset, false otherwise.
<hr />

### `current` <a id="class_battery_1addc7658b5425f6bfabb8e55c7f73fd33" class="anchor"></a>

```cpp
int16_t current()
```

Reads the current flowing from the battery at the moment. Negative values indicate that the battery is charging, positive values indicate that the battery is discharging. When no battery is connected, the value is -1.

#### Returns
The current flowing from the battery in milli amperes (mA).
<hr />

### `averageCurrent` <a id="class_battery_1ab74143421658d9aafb05535558a315dc" class="anchor"></a>

```cpp
int16_t averageCurrent()
```

Reads an average of current readings of the battery.

#### Returns
The average current in milli amperes (mA).
<hr />

### `minimumCurrent` <a id="class_battery_1a04fb9f935964dc4cad7673d581a4e701" class="anchor"></a>

```cpp
int16_t minimumCurrent()
```

Reads the minimum current values measured since the last device reset. Note: The resolution of the minimum current value is 160mA so the value is rounded to the nearest 160mA.

#### Returns
The minimum current values in milli amperes (mA).
<hr />

### `maximumCurrent` <a id="class_battery_1a06bbac275505bd55f54904dde086ea72" class="anchor"></a>

```cpp
int16_t maximumCurrent()
```

Reads the maximum current values measured since the last device reset. Note: The resolution of the minimum current value is 160mA so the value is rounded to the nearest 160mA.

#### Returns
The maximum current values in milli amperes (mA).
<hr />

### `resetMaximumMinimumCurrent` <a id="class_battery_1a86b64cfdb23050cc77a66c1e03750b42" class="anchor"></a>

```cpp
bool resetMaximumMinimumCurrent()
```

Resets the minimum and maximum current values.

#### Returns
True if the minimum and maximum current values were successfully reset, false otherwise.
<hr />

### `power` <a id="class_battery_1acc75ec11734cdc2f877e11a122ebf164" class="anchor"></a>

```cpp
int16_t power()
```

Reads the current power of the battery in milliwatts (mW). This value is calculated based on the current and voltage of the battery.

#### Returns
The current power in milliwatts (mW).
<hr />

### `averagePower` <a id="class_battery_1a41ff59184770622e77ba133818996793" class="anchor"></a>

```cpp
int16_t averagePower()
```

Reads an average of power readings of the battery in milliwatts (mW). This value is calculated based on the current and voltage of the battery.

#### Returns
The average power in milliwatts (mW).
<hr />

### `internalTemperature` <a id="class_battery_1a3967e87e3ff5bdfbfb99681902d31464" class="anchor"></a>

```cpp
uint8_t internalTemperature()
```

Reads the current temperature of the internal die of the battery gauge chip.

#### Returns
The current temperature in degrees Celsius.
<hr />

### `averageInternalTemperature` <a id="class_battery_1a658633cd49a8b594f6a8e75a126e6b5d" class="anchor"></a>

```cpp
uint8_t averageInternalTemperature()
```

Reads an average of internal temperature readings of the battery. Note: If the battery temperature was read before, this function will change the configuration to read the internal temperature. You will have to await a couple of temperature readings before getting a meaningful average temperature.

#### Returns
The average temperature in degrees Celsius.
<hr />

### `percentage` <a id="class_battery_1a2f7cd7878c7e3b8227ff38e18c8f65e2" class="anchor"></a>

```cpp
uint8_t percentage()
```

Reads the battery's state of charge (SOC). This value is based on both the voltage and the current of the battery as well as compensation for the battery's age and temperature and discharge rate.

#### Returns
The state of charge as a percentage (Range: 0% - 100%).
<hr />

### `remainingCapacity` <a id="class_battery_1a769e8dddd81779757b8399660b084734" class="anchor"></a>

```cpp
uint16_t remainingCapacity()
```

Reads the remaining capacity of the battery. In combination with [current()](#class_battery_1addc7658b5425f6bfabb8e55c7f73fd33), this value can be used to estimate the remaining time until the battery is empty.

#### Returns
The remaining capacity in milliampere-hours (mAh).
<hr />

### `fullCapacity` <a id="class_battery_1afb54a909c0fa3e5d7aed34026a441c49" class="anchor"></a>

```cpp
uint16_t fullCapacity()
```

Returns the full capacity of the battery. For this to work, the capacity of the battery must be set when initializing the battery object. 
#### Returns
The full capacity of the battery.
<hr />

### `isEmpty` <a id="class_battery_1a91fab7f1d3534f6f657e5868ee9af95a" class="anchor"></a>

```cpp
bool isEmpty()
```

Checks if the battery is empty. Returns false once the cell voltage rises above the recovery threshold.

#### Returns
true if the battery is empty, false otherwise.
<hr />

### `timeToEmpty` <a id="class_battery_1af7775216c6a4278af417f8ebdfd94dbe" class="anchor"></a>

```cpp
int32_t timeToEmpty()
```

Calculates the estimated time until the battery is empty. 
#### Returns
The estimated time until the battery is empty, in seconds. If the battery is charging, the function returns -1.
<hr />

### `timeToFull` <a id="class_battery_1a6eaae4e71787908063ad64ee58ba09d2" class="anchor"></a>

```cpp
int32_t timeToFull()
```

Calculates the estimated time until the battery is fully charged. The value is determined by learning from the experience of prior charge cycles. 
#### Returns
The estimated time until the battery is fully charged in seconds. If the battery is discharging, the function returns -1.
<hr />

# class `Board` <a id="class_board" class="anchor"></a>

Represents a board with power management capabilities.

The [Board](#class_board) class provides methods to check the power source, enable/disable power rails, set voltage levels, enable/disable wakeup from pins or RTC, put the device into sleep mode for a specified duration, and control peripherals' power.

Supported boards: Arduino Portenta H7, Arduino Portenta C33, Arduino Nicla Vision.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Board`](#class_board_1a9ee491d4fea680cf69b033374a9fdfcb) | Construct a new [Board](#class_board) object. |
| [`~Board`](#class_board_1af73f45730119a1fd8f6670f53f959e68) | Destroy the [Board](#class_board) object. |
| [`begin`](#class_board_1a7cd62c2a663226bb02c87675e947ade0) | Initializes the board by initiating the PMIC. |
| [`isUSBPowered`](#class_board_1aa53bea8ac0404de8a7389484a61937ae) | Check if the board is powered through USB. |
| [`isBatteryPowered`](#class_board_1a80a62c172bea4a16b6983f204380f92b) | Check if the board is powered by the battery. |
| [`setExternalPowerEnabled`](#class_board_1a336acc6fbe5c9d3544a14bc47afc0fc8) | Enables/disables the voltage on the external power rail. This lane powers the pin labeled 3V3 on the board.  |
| [`setExternalVoltage`](#class_board_1ad92e1939e565023016b210ce6aae68b6) | Set the voltage for the external power rail. This lane powers the pin labeled 3V3 on the board.  |
| [`setCameraPowerEnabled`](#class_board_1ad02a62c1b376df7523751fa4b3207204) | Enables/disables the camera's power rail on boards with a built-in camera. |
| [`enableWakeupFromPin`](#class_board_1ae04b853e945b07852a65fb4f0e7e7d2b) | Enables wakeup from pin GPIO0 on Portenta H7. The pin is only accessible via high-density connectors. |
| [`enableSleepWhenIdle`](#class_board_1ae4c9772a307f85306102cf4333ecf249) | Enables sleep mode when the board is idle. |
| [`enableWakeupFromPin`](#class_board_1a94ac54f76a7e8fff5b7c6523af64169a) | Enables wake-up of the device from a specified pin (A0, A1, A2, A3, A4, A5, D4, D7 ) on Arduino Portenta C33.  |
| [`enableWakeupFromRTC`](#class_board_1a5fc9e67d4e42ce7943b9675c17fd77f6) | Enables wake-up of the device from the RTC. This function allows to use a custom RTC instance to put the device in sleep mode. |
| [`enableWakeupFromRTC`](#class_board_1a49925de689c2f73f49b09d7b190e5036) | Enables wake-up of the device from the RTC. |
| [`enableWakeupFromRTC`](#class_board_1a27a7db805596399daf0e89de755eca0c) | Enables wake-up of the device from the RTC.  |
| [`sleepUntilWakeupEvent`](#class_board_1a1d23524e0bfeb7282fa465f3834027e1) | Put the device into sleep mode until a wakeup event occurs This sleep mode is ideal for applications requiring periodic wake-ups or brief intervals of inactivity and reduces consumption to a range between 6mA and 18mA depending on the state of the peripherals. This sleep mode resumes the operation from the last operation without resetting the board. A wakeup event can be an interrupt on a pin or the RTC, depending on what you set with [enableWakeupFromPin()](#class_board_1ae04b853e945b07852a65fb4f0e7e7d2b) and [enableWakeupFromRTC()](#class_board_1a5fc9e67d4e42ce7943b9675c17fd77f6). |
| [`standByUntilWakeupEvent`](#class_board_1a7dda3836bbe5a11628d4d8a122529ded) | Put the device into standby mode until a wakeup event occurs. For scenarios demanding drastic power conservation, the standby Mode significantly reduces the board's power usage to micro amperes range depending on the state of the peripherals. This mode restarts the board on wake-up, effectively running the setup() function again. A wakeup event can be an interrupt on a pin or the RTC, depending on what you set with [enableWakeupFromPin()](#class_board_1ae04b853e945b07852a65fb4f0e7e7d2b) and [enableWakeupFromRTC()](#class_board_1a5fc9e67d4e42ce7943b9675c17fd77f6). |
| [`setAllPeripheralsPower`](#class_board_1a27dcc0b9d69a8cce256494192f2efb3a) | Toggle the peripherals' power on Portenta C33 (ADC, RGB LED, Secure Element, Wifi and Bluetooth). |
| [`setCommunicationPeripheralsPower`](#class_board_1ac91aa31be1ea833d7266dda45dd1c5f2) | Toggles the communication peripherials' power on Portenta C33 (Wifi, Bluetooth and Secure Element) |
| [`setAnalogDigitalConverterPower`](#class_board_1a3d9fbb30b03c3a7f733f0c89dd9dc43d) | Toggles the power of the analog digital converter on Portenta C33. This is not available on the Portenta H7. |
| [`setReferenceVoltage`](#class_board_1a8feb9efc5439c8fec5139f66484200b5) | Set the reference voltage. This value is used by the ADC to convert analog values to digital values. This can be particularly useful to increase the accuracy of the ADC when working with low voltages. |
| [`shutDownFuelGauge`](#class_board_1ae4af8f64cc1389bc0b640124dbb0d9c8) | Shuts down the fuel gauge to reduce power consumption. The IC returns to active mode on any edge of any communication line. If the IC is power-cycled or the software RESET command is sent the IC returns to active mode of operation. |

## Members

### `Board` <a id="class_board_1a9ee491d4fea680cf69b033374a9fdfcb" class="anchor"></a>

```cpp
Board()
```

Construct a new [Board](#class_board) object.

<hr />

### `~Board` <a id="class_board_1af73f45730119a1fd8f6670f53f959e68" class="anchor"></a>

```cpp
~Board()
```

Destroy the [Board](#class_board) object.

<hr />

### `begin` <a id="class_board_1a7cd62c2a663226bb02c87675e947ade0" class="anchor"></a>

```cpp
bool begin()
```

Initializes the board by initiating the PMIC.

#### Returns
true if the board initialization is successful, false otherwise.
<hr />

### `isUSBPowered` <a id="class_board_1aa53bea8ac0404de8a7389484a61937ae" class="anchor"></a>

```cpp
bool isUSBPowered()
```

Check if the board is powered through USB.

#### Returns
True if powered through USB, false otherwise.
<hr />

### `isBatteryPowered` <a id="class_board_1a80a62c172bea4a16b6983f204380f92b" class="anchor"></a>

```cpp
bool isBatteryPowered()
```

Check if the board is powered by the battery.

#### Returns
True if powered by the battery, false otherwise.
<hr />

### `setExternalPowerEnabled` <a id="class_board_1a336acc6fbe5c9d3544a14bc47afc0fc8" class="anchor"></a>

```cpp
void setExternalPowerEnabled(bool on)
```

Enables/disables the voltage on the external power rail. This lane powers the pin labeled 3V3 on the board. 
#### Parameters
* `on` True to enable this power rail, false to disable it.
<hr />

### `setExternalVoltage` <a id="class_board_1ad92e1939e565023016b210ce6aae68b6" class="anchor"></a>

```cpp
bool setExternalVoltage(float voltage)
```

Set the voltage for the external power rail. This lane powers the pin labeled 3V3 on the board. 
#### Parameters
* `voltage` float value of the voltage value to set. Value has to be one of the following (1.10, 1.20, 1.35, 1.50, 1.80, 2.50, 3.00, 3.30) 

#### Returns
True the voltage was set successfully, false otherwise.
<hr />

### `setCameraPowerEnabled` <a id="class_board_1ad02a62c1b376df7523751fa4b3207204" class="anchor"></a>

```cpp
void setCameraPowerEnabled(bool enabled)
```

Enables/disables the camera's power rail on boards with a built-in camera.

#### Parameters
* `enabled` True to turn on the camera, false to turn it off.
<hr />

### `enableWakeupFromPin` <a id="class_board_1ae04b853e945b07852a65fb4f0e7e7d2b" class="anchor"></a>

```cpp
void enableWakeupFromPin()
```

Enables wakeup from pin GPIO0 on Portenta H7. The pin is only accessible via high-density connectors.
<hr />

### `enableSleepWhenIdle` <a id="class_board_1ae4c9772a307f85306102cf4333ecf249" class="anchor"></a>

```cpp
void enableSleepWhenIdle()
```

Enables sleep mode when the board is idle.
<hr />

### `enableWakeupFromPin` <a id="class_board_1a94ac54f76a7e8fff5b7c6523af64169a" class="anchor"></a>

```cpp
void enableWakeupFromPin(uint8_t pin, PinStatus direction)
```

Enables wake-up of the device from a specified pin (A0, A1, A2, A3, A4, A5, D4, D7 ) on Arduino Portenta C33. 
#### Parameters
* `pin` The pin number used for waking up the device. 

* `direction` The direction of the interrupt that will wake up the device. (RISING, FALLING)
<hr />

### `enableWakeupFromRTC` <a id="class_board_1a5fc9e67d4e42ce7943b9675c17fd77f6" class="anchor"></a>

```cpp
bool enableWakeupFromRTC(uint32_t hours, uint32_t minutes, uint32_t seconds, void(*)() callbackFunction, RTClock * rtc)
```

Enables wake-up of the device from the RTC. This function allows to use a custom RTC instance to put the device in sleep mode.

#### Parameters
* `hours` The number of hours to sleep. 

* `minutes` The number of minutes to sleep. 

* `seconds` The number of seconds to sleep. 

* `callbackFunction` The function to call when the device wakes up. If no callback function is provided, the device will wake up without calling any function. 

* `rtc` The RTC instance to use for the sleep function. If no RTC instance is provided, the default RTC instance is used. 

#### Returns
True if successful, false otherwise.
<hr />

### `enableWakeupFromRTC` <a id="class_board_1a49925de689c2f73f49b09d7b190e5036" class="anchor"></a>

```cpp
bool enableWakeupFromRTC(uint32_t hours, uint32_t minutes, uint32_t seconds, RTClock * rtc)
```

Enables wake-up of the device from the RTC.

#### Parameters
* `hours` The number of hours to sleep. 

* `minutes` The number of minutes to sleep. 

* `seconds` The number of seconds to sleep. 

* `rtc` The RTC instance to use for the sleep function. Default is the shared RTC instance. 

#### Returns
True if successful, false otherwise.
<hr />

### `enableWakeupFromRTC` <a id="class_board_1a27a7db805596399daf0e89de755eca0c" class="anchor"></a>

```cpp
bool enableWakeupFromRTC(uint32_t hours, uint32_t minutes, uint32_t seconds)
```

Enables wake-up of the device from the RTC. 
#### Parameters
* `hours` The number of hours to sleep. 

* `minutes` The number of minutes to sleep. 

* `seconds` The number of seconds to sleep. 

#### Returns
True if successful, false otherwise.
<hr />

### `sleepUntilWakeupEvent` <a id="class_board_1a1d23524e0bfeb7282fa465f3834027e1" class="anchor"></a>

```cpp
void sleepUntilWakeupEvent()
```

Put the device into sleep mode until a wakeup event occurs This sleep mode is ideal for applications requiring periodic wake-ups or brief intervals of inactivity and reduces consumption to a range between 6mA and 18mA depending on the state of the peripherals. This sleep mode resumes the operation from the last operation without resetting the board. A wakeup event can be an interrupt on a pin or the RTC, depending on what you set with [enableWakeupFromPin()](#class_board_1ae04b853e945b07852a65fb4f0e7e7d2b) and [enableWakeupFromRTC()](#class_board_1a5fc9e67d4e42ce7943b9675c17fd77f6).
<hr />

### `standByUntilWakeupEvent` <a id="class_board_1a7dda3836bbe5a11628d4d8a122529ded" class="anchor"></a>

```cpp
void standByUntilWakeupEvent()
```

Put the device into standby mode until a wakeup event occurs. For scenarios demanding drastic power conservation, the standby Mode significantly reduces the board's power usage to micro amperes range depending on the state of the peripherals. This mode restarts the board on wake-up, effectively running the setup() function again. A wakeup event can be an interrupt on a pin or the RTC, depending on what you set with [enableWakeupFromPin()](#class_board_1ae04b853e945b07852a65fb4f0e7e7d2b) and [enableWakeupFromRTC()](#class_board_1a5fc9e67d4e42ce7943b9675c17fd77f6).
<hr />

### `setAllPeripheralsPower` <a id="class_board_1a27dcc0b9d69a8cce256494192f2efb3a" class="anchor"></a>

```cpp
void setAllPeripheralsPower(bool on)
```

Toggle the peripherals' power on Portenta C33 (ADC, RGB LED, Secure Element, Wifi and Bluetooth).

#### Parameters
* `on` True to turn on the power, false to turn it off.
<hr />

### `setCommunicationPeripheralsPower` <a id="class_board_1ac91aa31be1ea833d7266dda45dd1c5f2" class="anchor"></a>

```cpp
void setCommunicationPeripheralsPower(bool on)
```

Toggles the communication peripherials' power on Portenta C33 (Wifi, Bluetooth and Secure Element)

#### Parameters
* `on` True to turn on the power, false to turn it off.
<hr />

### `setAnalogDigitalConverterPower` <a id="class_board_1a3d9fbb30b03c3a7f733f0c89dd9dc43d" class="anchor"></a>

```cpp
void setAnalogDigitalConverterPower(bool on)
```

Toggles the power of the analog digital converter on Portenta C33. This is not available on the Portenta H7.

#### Parameters
* `on` True to turn on the power, false to turn it off.
<hr />

### `setReferenceVoltage` <a id="class_board_1a8feb9efc5439c8fec5139f66484200b5" class="anchor"></a>

```cpp
bool setReferenceVoltage(float voltage)
```

Set the reference voltage. This value is used by the ADC to convert analog values to digital values. This can be particularly useful to increase the accuracy of the ADC when working with low voltages.

#### Parameters
* `voltage` Reference voltage value in volts. It can be anything between 1.80V and 3.30V in steps of 0.10V. Any value outside this range or with different steps will not be accepted by the library. 

#### Returns
True if the voltage was set successfully, false otherwise.
<hr />

### `shutDownFuelGauge` <a id="class_board_1ae4af8f64cc1389bc0b640124dbb0d9c8" class="anchor"></a>

```cpp
void shutDownFuelGauge()
```

Shuts down the fuel gauge to reduce power consumption. The IC returns to active mode on any edge of any communication line. If the IC is power-cycled or the software RESET command is sent the IC returns to active mode of operation.

<hr />

# class `Charger` <a id="class_charger" class="anchor"></a>

Class for controlling charging parameters and monitoring charging status.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Charger`](#class_charger_1a386eef9a5c151f3e5eb3ee67a0aeb0cb) | Constructs a new [Charger](#class_charger) object. |
| [`begin`](#class_charger_1af3ebf5b1bbd6c4909f47217b83fe57ab) | Initializes the charger by initiating the PMIC. |
| [`setChargeCurrent`](#class_charger_1a7092cf5385bf469d3b27204478fb1671) | Set the charging current. The default charging current is set to 100mA. |
| [`getChargeCurrent`](#class_charger_1a3ff22dda98f766f42a3a7fdfc46d7a41) | Get the charge current in milli amperes (mA). |
| [`setChargeVoltage`](#class_charger_1a46cee977438a93ef66ed3882d741efbc) | Set the charging voltage in volts (V). The current charging voltage is set to 4.2V by default. |
| [`getChargeVoltage`](#class_charger_1af478d3be4756b758238823696c1a00c8) | Get the charge voltage in volts (V). |
| [`setEndOfChargeCurrent`](#class_charger_1a9b54c1077cc45ed826b8269ff57a3ee2) | Set the end-of-charge current. The charger IC determines when to terminate the charge cycle based on the current going into the battery dropping below the given threshold during the constant voltage phase. At this point, the battery is considered fully charged and charging is completed. If charge termination is disabled, the charge current will naturally decay to 0mA, but this is rarely done in practice. This is because the amount of charge going into the battery exponentially decreases during CV charging, and it would take a significantly longer time to recharge the battery with a very little increase in capacity. |
| [`getEndOfChargeCurrent`](#class_charger_1ae74b5ab591bd666c47cd133d2855152c) | Get the end of charge current. |
| [`setInputCurrentLimit`](#class_charger_1a1c4b5f61bd84e067c2643a0da1ccd1a7) | The input current limit (ILIM) safeguards the device by preventing overcurrent, ensuring the charging current is within safe levels for the battery, and adapting to the maximum current the power source can provide, allowing you to charge and use the system at the same time. The default input current limit is set to 1.5A. |
| [`getInputCurrentLimit`](#class_charger_1a768963364778f838e4b44463c020b173) | Get the input current limit. It is a safeguard to prevent overcurrent when charging respectively to the maximum current the power source can provide. |
| [`getState`](#class_charger_1a4670cf2d22eb36216e7ef2b65077021a) | Get the current charging status. |
| [`isEnabled`](#class_charger_1a908179315a74d96f27fbb86858ae4892) | Checks if the charger and thus charging is enabled. By default, the charger is enabled. |
| [`setEnabled`](#class_charger_1a4db5462b2061801340f022f2cd35e6c0) | Sets the enabled state of the charger. When enabling it uses the default settings or the last saved parameters, depending on what was set previously. |

## Members

### `Charger` <a id="class_charger_1a386eef9a5c151f3e5eb3ee67a0aeb0cb" class="anchor"></a>

```cpp
Charger()
```

Constructs a new [Charger](#class_charger) object.

<hr />

### `begin` <a id="class_charger_1af3ebf5b1bbd6c4909f47217b83fe57ab" class="anchor"></a>

```cpp
bool begin()
```

Initializes the charger by initiating the PMIC.

#### Returns
true if the charger initialization is successful, false otherwise.
<hr />

### `setChargeCurrent` <a id="class_charger_1a7092cf5385bf469d3b27204478fb1671" class="anchor"></a>

```cpp
bool setChargeCurrent(uint16_t current)
```

Set the charging current. The default charging current is set to 100mA.

#### Parameters
* `current` Charging current in milli amperes (mA). Supported values: 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000 

#### Returns
True if successful, false if an invalid value was provided or if the PMIC communication failed.
<hr />

### `getChargeCurrent` <a id="class_charger_1a3ff22dda98f766f42a3a7fdfc46d7a41" class="anchor"></a>

```cpp
uint16_t getChargeCurrent()
```

Get the charge current in milli amperes (mA).

#### Returns
The charge current in float.
<hr />

### `setChargeVoltage` <a id="class_charger_1a46cee977438a93ef66ed3882d741efbc" class="anchor"></a>

```cpp
bool setChargeVoltage(float voltage)
```

Set the charging voltage in volts (V). The current charging voltage is set to 4.2V by default.

#### Parameters
* `voltage` Charging voltage in volts (V). Supported values: 3.50, 3.52, 3.54, 3.56, 3.58, 3.60, 3.62, 3.64, 3.66, 3.68, 3.70, 3.72, 3.74, 3.76, 3.78, 3.80, 3.82, 3.84, 3.86, 3.88, 3.90, 3.92, 3.94, 3.96, 3.98, 4.00, 4.02, 4.04, 4.06, 4.08, 4.10, 4.12, 4.14, 4.16, 4.18, 4.20, 4.22, 4.24, 4.26, 4.28, 4.30, 4.32, 4.34, 4.36, 4.38, 4.40, 4.42, 4.44 

#### Returns
True if successful, false if an invalid value was provided or if the PMIC communication failed.
<hr />

### `getChargeVoltage` <a id="class_charger_1af478d3be4756b758238823696c1a00c8" class="anchor"></a>

```cpp
float getChargeVoltage()
```

Get the charge voltage in volts (V).

#### Returns
The charge voltage as a float value.
<hr />

### `setEndOfChargeCurrent` <a id="class_charger_1a9b54c1077cc45ed826b8269ff57a3ee2" class="anchor"></a>

```cpp
bool setEndOfChargeCurrent(uint16_t current)
```

Set the end-of-charge current. The charger IC determines when to terminate the charge cycle based on the current going into the battery dropping below the given threshold during the constant voltage phase. At this point, the battery is considered fully charged and charging is completed. If charge termination is disabled, the charge current will naturally decay to 0mA, but this is rarely done in practice. This is because the amount of charge going into the battery exponentially decreases during CV charging, and it would take a significantly longer time to recharge the battery with a very little increase in capacity.

#### Parameters
* `current` End-of-charge current in milli amperes (mA). The default end-of-charge current is set to 5 mA. Supported values: 5, 10, 20, 30, 50 

#### Returns
True if successful, false if an invalid value was provided or if the PMIC communication failed.
<hr />

### `getEndOfChargeCurrent` <a id="class_charger_1ae74b5ab591bd666c47cd133d2855152c" class="anchor"></a>

```cpp
uint16_t getEndOfChargeCurrent()
```

Get the end of charge current.

This function returns the current value at which the charging process is considered complete. Charging is terminated when the supplied current drops below the pre-programmed end of charge level.

#### Returns
The end of charge current.
<hr />

### `setInputCurrentLimit` <a id="class_charger_1a1c4b5f61bd84e067c2643a0da1ccd1a7" class="anchor"></a>

```cpp
bool setInputCurrentLimit(uint16_t current)
```

The input current limit (ILIM) safeguards the device by preventing overcurrent, ensuring the charging current is within safe levels for the battery, and adapting to the maximum current the power source can provide, allowing you to charge and use the system at the same time. The default input current limit is set to 1.5A.

#### Parameters
* `current` Maximum input current in milli amperes (mA). Supported values: 10, 15, 20, 25, 30, 35, 40, 45, 50, 100, 150, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1500 

#### Returns
True if successful, false if an invalid value was provided or if the PMIC communication failed.
<hr />

### `getInputCurrentLimit` <a id="class_charger_1a768963364778f838e4b44463c020b173" class="anchor"></a>

```cpp
uint16_t getInputCurrentLimit()
```

Get the input current limit. It is a safeguard to prevent overcurrent when charging respectively to the maximum current the power source can provide.

#### Returns
The input current limit in milli amperes (mA).
<hr />

### `getState` <a id="class_charger_1a4670cf2d22eb36216e7ef2b65077021a" class="anchor"></a>

```cpp
ChargingState getState()
```

Get the current charging status.

#### Returns
Charging status enum value (ChargingState). The possible states are:

* none: Provided by the registers, not used in this API.

* preCharge: First stage of the charging process, prepares battery for the charging process.

* fastChargeConstantCurrent: Second phase of the charging process where the battery is charging in constant current mode until it reaches the voltage where the it's considered fully charged. (4.2V)

* fastChargeConstantVoltage: Third phase of the charging process where the battery is kept at the fully charged voltage and current is slowly decreased to the end of charge current.

* endOfCharge: If the battery is still connected, the charger will ensure it's kept at 4.2V by topping up the voltage to avoid self discharge.

* done: [Battery](#class_battery) is fully charged

* timerFaultError: The timer that is monitoring the charge status has encountered an error.

* thermistorSuspendError: Charging was suspended due to overheating

* chargerDisabled: [Charger](#class_charger) is disabled

* batteryOvervoltageError: Charging was suspended due to an overvoltage fault

* chargerBypassed: The charger is bypassed completely and the USB voltage is powering the board
<hr />

### `isEnabled` <a id="class_charger_1a908179315a74d96f27fbb86858ae4892" class="anchor"></a>

```cpp
bool isEnabled()
```

Checks if the charger and thus charging is enabled. By default, the charger is enabled.

#### Returns
true if the charger is enabled, false otherwise.
<hr />

### `setEnabled` <a id="class_charger_1a4db5462b2061801340f022f2cd35e6c0" class="anchor"></a>

```cpp
bool setEnabled(bool enabled)
```

Sets the enabled state of the charger. When enabling it uses the default settings or the last saved parameters, depending on what was set previously.

#### Parameters
* `enabled` The desired enabled state of the charger. 

#### Returns
true if the enabled state was successfully set, false otherwise.
<hr />

# class `MAX1726Driver` <a id="class_m_a_x1726_driver" class="anchor"></a>

Driver class for the MAX1726 Fuel Gauge IC.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`chargingComplete`](#class_m_a_x1726_driver_1a9c7c3d11d9dddc7667eafba19c52e65f) | Checks if the battery charging is complete. |
| [`setOperationMode`](#class_m_a_x1726_driver_1a13aeedba15e50b2fd2dada0a8ab0e5cd) | Sets the operation mode of the Fuel Gauge. |
| [`MAX1726Driver`](#class_m_a_x1726_driver_1af68eee6cc8a3d2a9fbbb0097b55e7ec6) | Constructs a new [MAX1726Driver](#class_m_a_x1726_driver) object. |
| [`~MAX1726Driver`](#class_m_a_x1726_driver_1a29bb1df9c115d16da9e4ce3afc99a992) |  |

## Members

### `chargingComplete` <a id="class_m_a_x1726_driver_1a9c7c3d11d9dddc7667eafba19c52e65f" class="anchor"></a>

```cpp
bool chargingComplete()
```

Checks if the battery charging is complete.

Checks if the charging process is complete.

#### Returns
true if the charging process is complete, false otherwise.

#### Returns
true if the charging is complete, false otherwise.
<hr />

### `setOperationMode` <a id="class_m_a_x1726_driver_1a13aeedba15e50b2fd2dada0a8ab0e5cd" class="anchor"></a>

```cpp
bool setOperationMode(FuelGaugeOperationMode mode)
```

Sets the operation mode of the Fuel Gauge.

#### Parameters
* `mode` The operation mode to set. Possible values are: hibernate, shutdown, active. 

#### Returns
True if the operation mode was set successfully, false otherwise.
<hr />

### `MAX1726Driver` <a id="class_m_a_x1726_driver_1af68eee6cc8a3d2a9fbbb0097b55e7ec6" class="anchor"></a>

```cpp
MAX1726Driver(TwoWire * wire, uint8_t i2cAddress)
```

Constructs a new [MAX1726Driver](#class_m_a_x1726_driver) object.

#### Parameters
* `wire` Pointer to the TwoWire object for I2C communication. 

* `i2cAddress` The I2C address of the MAX1726 device. The default value is 0x36.
<hr />

### `~MAX1726Driver` <a id="class_m_a_x1726_driver_1a29bb1df9c115d16da9e4ce3afc99a992" class="anchor"></a>

```cpp
~MAX1726Driver()
```

<hr />

# struct `BatteryCharacteristics` <a id="struct_battery_characteristics" class="anchor"></a>

This struct contains the characteristics of the battery.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`capacity`](#struct_battery_characteristics_1a6bd20a3ca22801553596234c7d80014c) | The battery's capacity in milliampere-hours (mAh). |
| [`emptyVoltage`](#struct_battery_characteristics_1af8847c64e47bd1ee07a2234572658baf) | The voltage in volts (V) at which the battery is considered empty. If you don't know this value you can use the minimumVoltage() function to find out while you let the battery completely discharge. |
| [`chargeVoltage`](#struct_battery_characteristics_1a1278657cc6c246d6545a3770d213cf91) | The voltage in volts (V) at which the battery is being charged. |
| [`endOfChargeCurrent`](#struct_battery_characteristics_1a13c651b4da45ab04ec9935023257aec2) | The current in milli amperes (mA) that is used to keep the battery charged at the end of the charging process. |
| [`ntcResistor`](#struct_battery_characteristics_1ab5b19a09ad5e5d61c1ad72bdf4de4fb3) | The NTC resistor value used in the battery pack (10K or 100K Ohm). |
| [`recoveryVoltage`](#struct_battery_characteristics_1aff1e9cdf23f2a9ff9e23da138f1791b4) | Sets the voltage level for clearing empty detection. Once the cell voltage rises above this point, empty voltage detection is re-enabled. |

## Members

### `capacity` <a id="struct_battery_characteristics_1a6bd20a3ca22801553596234c7d80014c" class="anchor"></a>

```cpp
int capacity
```

The battery's capacity in milliampere-hours (mAh).

<hr />

### `emptyVoltage` <a id="struct_battery_characteristics_1af8847c64e47bd1ee07a2234572658baf" class="anchor"></a>

```cpp
float emptyVoltage
```

The voltage in volts (V) at which the battery is considered empty. If you don't know this value you can use the minimumVoltage() function to find out while you let the battery completely discharge.

<hr />

### `chargeVoltage` <a id="struct_battery_characteristics_1a1278657cc6c246d6545a3770d213cf91" class="anchor"></a>

```cpp
float chargeVoltage
```

The voltage in volts (V) at which the battery is being charged.

<hr />

### `endOfChargeCurrent` <a id="struct_battery_characteristics_1a13c651b4da45ab04ec9935023257aec2" class="anchor"></a>

```cpp
int endOfChargeCurrent
```

The current in milli amperes (mA) that is used to keep the battery charged at the end of the charging process.

<hr />

### `ntcResistor` <a id="struct_battery_characteristics_1ab5b19a09ad5e5d61c1ad72bdf4de4fb3" class="anchor"></a>

```cpp
NTCResistor ntcResistor
```

The NTC resistor value used in the battery pack (10K or 100K Ohm).

<hr />

### `recoveryVoltage` <a id="struct_battery_characteristics_1aff1e9cdf23f2a9ff9e23da138f1791b4" class="anchor"></a>

```cpp
float recoveryVoltage
```

Sets the voltage level for clearing empty detection. Once the cell voltage rises above this point, empty voltage detection is re-enabled.

<hr />

