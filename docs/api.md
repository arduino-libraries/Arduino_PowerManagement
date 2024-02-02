# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class ` [`Battery`](#class_battery) | [Battery](#class_battery) class definition and member function declarations.
`class ` [`Board`](#class_board) | 
`class ` [`Charger`](#class_charger) | [Charger](#class_charger) class for controlling charging parameters and monitoring charging status.
`class ` [`PowerManagement`](#class_power_management) | 

# class `Battery` <a id="class_battery" class="anchor"></a>

[Battery](#class_battery) class definition and member function declarations.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Battery`](#class_battery_1a36a6234c583e3b3506f4a77e3eb49989) | Constructor for the [Battery](#class_battery) class. Initializes the battery with default values for capacity and empty voltage. The default values are 200mAh and 3000mV respectively. |
| [`Battery`](#class_battery_1a8c861b38bb868a17f980615c47180655) | Constructor for the [Battery](#class_battery) class. |
| [`begin`](#class_battery_1abe2e94712b9e846f38f63884f6f995ef) | Initializes the battery communication and configuration. |
| [`isConnected`](#class_battery_1a9473c4a4583abea991268d0818f19dbe) | Checks if a battery is connected to the system. |
| [`voltage`](#class_battery_1af6c186181316398ab86a73591adc7229) | Reads the current voltage of the battery. Voltage is usually between 3000mV and 4200mV. |
| [`averageVoltage`](#class_battery_1a8b343c8244e16caba082643c3d3e9e46) | Reads the average voltage of the battery. |
| [`current`](#class_battery_1acc60fb79f995897dbcad56535b4ddc7f) | Reads the current flowing from the battery at the moment. |
| [`averageCurrent`](#class_battery_1a60543d61d65d23745ffb0b11a7b52bb4) | Reads the average current of the battery. |
| [`temperature`](#class_battery_1a9769b18902c4576c3ed7405c7e58bbea) | Reads the current temperature of the battery. |
| [`averageTemperature`](#class_battery_1a89b2bbbda3ce367b2e855ce9b258abf0) | Reads the average temperature of the battery. |
| [`percentage`](#class_battery_1a4d34768c6d8740fad39ce25028a01ee6) | Reads the battery's state of charge (SOC). This value is based on both the voltage and the current of the battery as well as compensation for the battery's age and temperature and discharge rate. |
| [`remainingCapacity`](#class_battery_1a622eb39d57504e13beaac16003c04fd3) | Reads the remaining capacity of the battery. |

## Members

### `Battery` <a id="class_battery_1a36a6234c583e3b3506f4a77e3eb49989" class="anchor"></a>

```cpp
Battery()
```

Constructor for the [Battery](#class_battery) class. Initializes the battery with default values for capacity and empty voltage. The default values are 200mAh and 3000mV respectively.

**See also**: [Battery(int, int)](#class_battery_1a8c861b38bb868a17f980615c47180655)

**See also**: #defaultBatteryCapacityInMiliampereHours 

**See also**: #defaultEmptyVoltage
<hr />

### `Battery` <a id="class_battery_1a8c861b38bb868a17f980615c47180655" class="anchor"></a>

```cpp
Battery(int capacityInMilliAmpereHours, int emptyVoltageInMilliVolts)
```

Constructor for the [Battery](#class_battery) class.

#### Parameters
* `capacityInMilliAmpereHours` The capacity of the battery in milliampere-hours (mAh). 

* `emptyVoltageInMilliVolts` The voltage at which the battery is considered empty in millivolts (mV).
<hr />

### `begin` <a id="class_battery_1abe2e94712b9e846f38f63884f6f995ef" class="anchor"></a>

```cpp
bool begin()
```

Initializes the battery communication and configuration.

<hr />

### `isConnected` <a id="class_battery_1a9473c4a4583abea991268d0818f19dbe" class="anchor"></a>

```cpp
boolean isConnected()
```

Checks if a battery is connected to the system.

#### Returns
True if a battery has been connected, false otherwise
<hr />

### `voltage` <a id="class_battery_1af6c186181316398ab86a73591adc7229" class="anchor"></a>

```cpp
int voltage()
```

Reads the current voltage of the battery. Voltage is usually between 3000mV and 4200mV.

#### Returns
The current voltage in millivolts (mV).
<hr />

### `averageVoltage` <a id="class_battery_1a8b343c8244e16caba082643c3d3e9e46" class="anchor"></a>

```cpp
unsigned int averageVoltage()
```

Reads the average voltage of the battery.

#### Returns
The average voltage in millivolts (mV).
<hr />

### `current` <a id="class_battery_1acc60fb79f995897dbcad56535b4ddc7f" class="anchor"></a>

```cpp
int current()
```

Reads the current flowing from the battery at the moment.

#### Returns
The current flowing from the battery at the moment miliamperes (mA).
<hr />

### `averageCurrent` <a id="class_battery_1a60543d61d65d23745ffb0b11a7b52bb4" class="anchor"></a>

```cpp
int averageCurrent()
```

Reads the average current of the battery.

#### Returns
The average current in millivolts (mV).
<hr />

### `temperature` <a id="class_battery_1a9769b18902c4576c3ed7405c7e58bbea" class="anchor"></a>

```cpp
int temperature()
```

Reads the current temperature of the battery.

#### Returns
The current temperature in degrees Celsius.
<hr />

### `averageTemperature` <a id="class_battery_1a89b2bbbda3ce367b2e855ce9b258abf0" class="anchor"></a>

```cpp
int averageTemperature()
```

Reads the average temperature of the battery.

#### Returns
The current temperature in degrees Celsius.
<hr />

### `percentage` <a id="class_battery_1a4d34768c6d8740fad39ce25028a01ee6" class="anchor"></a>

```cpp
int percentage()
```

Reads the battery's state of charge (SOC). This value is based on both the voltage and the current of the battery as well as compensation for the battery's age and temperature and discharge rate.

#### Returns
The state of charge as a percentage.
<hr />

### `remainingCapacity` <a id="class_battery_1a622eb39d57504e13beaac16003c04fd3" class="anchor"></a>

```cpp
int remainingCapacity()
```

Reads the remaining capacity of the battery.

#### Returns
The remaining capacity in milliampere-hours (mAh).
<hr />

# class `Board` <a id="class_board" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Board`](#class_board_1a9ee491d4fea680cf69b033374a9fdfcb) | Default constructor for the [Board](#class_board) class. |
| [`Board`](#class_board_1a46e7c2305b38070b01a5714449021b5c) | Constructor for the [Board](#class_board) class with a PF1550 PMIC instance. |
| [`isUSBPowered`](#class_board_1aa53bea8ac0404de8a7389484a61937ae) | Check if the board is powered through USB. |
| [`isBatteryPowered`](#class_board_1a80a62c172bea4a16b6983f204380f92b) | Check if the board is powered by the battery. |
| [`setExternalPowerEnabled`](#class_board_1a336acc6fbe5c9d3544a14bc47afc0fc8) | Set the voltage for the external power rail. This lane powers the pin labeled 3V3 on the board.  |
| [`setExternalVoltage`](#class_board_1ad92e1939e565023016b210ce6aae68b6) | Set the voltage for the external power rail. This lane powers the pin labeled 3V3 on the board.  |
| [`setCameraPowerEnabled`](#class_board_1ad02a62c1b376df7523751fa4b3207204) | Set the camera power rail switch direction on boards with a built-in camera. |
| [`enableWakeupFromPin`](#class_board_1a94ac54f76a7e8fff5b7c6523af64169a) | Enables wake-up of the device from a specified pin (A0, A1, A2, A3, A4, A5, D4, D7 )  |
| [`enableWakeupFromRTC`](#class_board_1ae158d0367a2851d1f1f560bcca784412) | Enables wake-up of the device from the RTC. |
| [`sleepFor`](#class_board_1a966bcfa00c60eaf3b0a1aa89d1deea9d) | Put the device in sleep mode for a specified amount of time. |
| [`sleepFor`](#class_board_1a31c46d510bbf14e372e019b8789afd3b) | Put the device in sleep mode for a specified amount of time. |
| [`sleepUntilWakeupEvent`](#class_board_1a1d23524e0bfeb7282fa465f3834027e1) | Put the device into sleep mode until a wakeup event occurs. This sleep mode is ideal for applications requiring periodic wake-ups or brief intervals of inactivity and reduces consumption to a range between 6mA and 18mA depending on the state of the peripherals. This sleep mode resumes the operation from the last operation. A wakeup event can be an interrupt on a pin or the RTC, depending on what you set with [enableWakeupFromPin()](#class_board_1a94ac54f76a7e8fff5b7c6523af64169a) and [enableWakeupFromRTC()](#class_board_1ae158d0367a2851d1f1f560bcca784412). |
| [`deepSleepUntilWakeupEvent`](#class_board_1aa0f7c55bf12f52374a2694aff110836b) | Put the device into deep sleep mode until a wakeup event occurs. For scenarios demanding drastic power conservation, the Deep Sleep Mode significantly reduces the board's power usage to range between 90uA and 11mA depending on the state of the peripherals. This mode restarts the board on wakeup, effectively running the setup() function again. A wakeup event can be an interrupt on a pin or the RTC, depending on what you set with [enableWakeupFromPin()](#class_board_1a94ac54f76a7e8fff5b7c6523af64169a) and [enableWakeupFromRTC()](#class_board_1ae158d0367a2851d1f1f560bcca784412). |
| [`setAllPeripheralsPower`](#class_board_1a27dcc0b9d69a8cce256494192f2efb3a) | Turn the peripherals on Portenta C33 (ADC, RGB LED, Secure Element, Wifi and Bluetooth) off. |
| [`setCommunicationPeripheralsPower`](#class_board_1ac91aa31be1ea833d7266dda45dd1c5f2) | Set the communication power rail switch direction on Portenta C33 (Wifi, Bluetooth and Secure Element) |
| [`setAnalogDigitalConverterPower`](#class_board_1a3d9fbb30b03c3a7f733f0c89dd9dc43d) | Set the analog digital converter power rail switch direction on Portenta C33. |
| [`setReferenceVoltage`](#class_board_1a8feb9efc5439c8fec5139f66484200b5) | Set the reference voltage on Portenta C33. This value is used by the ADC to convert analog values to digital values. This can be particularly useful to increase the accuracy of the ADC when working with low voltages. |

## Members

### `Board` <a id="class_board_1a9ee491d4fea680cf69b033374a9fdfcb" class="anchor"></a>

```cpp
Board()
```

Default constructor for the [Board](#class_board) class.

<hr />

### `Board` <a id="class_board_1a46e7c2305b38070b01a5714449021b5c" class="anchor"></a>

```cpp
Board(PF1550 * pmic)
```

Constructor for the [Board](#class_board) class with a PF1550 PMIC instance.

#### Parameters
* `pmic` Pointer to the PF1550 PMIC instance.
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

Set the voltage for the external power rail. This lane powers the pin labeled 3V3 on the board. 
#### Parameters
* `on` True to enable this power rail, false to disable it.
<hr />

### `setExternalVoltage` <a id="class_board_1ad92e1939e565023016b210ce6aae68b6" class="anchor"></a>

```cpp
bool setExternalVoltage(float voltage)
```

Set the voltage for the external power rail. This lane powers the pin labeled 3V3 on the board. 
#### Parameters
* `voltage` float value of the voltage value to set. `voltage` has to be one of the following (1.10, 1.20, 1.35, 1.50, 1.80, 2.50, 3.00 and 3.30) 

#### Returns
True if successful, false otherwise.
<hr />

### `setCameraPowerEnabled` <a id="class_board_1ad02a62c1b376df7523751fa4b3207204" class="anchor"></a>

```cpp
void setCameraPowerEnabled(bool enabled)
```

Set the camera power rail switch direction on boards with a built-in camera.

#### Parameters
* `enabled` True to turn on the switches, false to turn them off.
<hr />

### `enableWakeupFromPin` <a id="class_board_1a94ac54f76a7e8fff5b7c6523af64169a" class="anchor"></a>

```cpp
void enableWakeupFromPin(uint8_t pin, PinStatus direction)
```

Enables wake-up of the device from a specified pin (A0, A1, A2, A3, A4, A5, D4, D7 ) 
#### Parameters
* `pin` The pin number used for waking up the device. 

* `direction` The direction of the interrupt that will wake up the device. (RISING, FALLING)
<hr />

### `enableWakeupFromRTC` <a id="class_board_1ae158d0367a2851d1f1f560bcca784412" class="anchor"></a>

```cpp
void enableWakeupFromRTC()
```

Enables wake-up of the device from the RTC.
<hr />

### `sleepFor` <a id="class_board_1a966bcfa00c60eaf3b0a1aa89d1deea9d" class="anchor"></a>

```cpp
bool sleepFor(int hours, int minutes, int seconds, void(*)() callbackFunction, RTClock * rtc)
```

Put the device in sleep mode for a specified amount of time.

#### Parameters
* `hours` The number of hours to sleep. 

* `minutes` The number of minutes to sleep. 

* `seconds` The number of seconds to sleep. 

* `callbackFunction` The function to call when the device wakes up. 

* `RTC` The RTC instance to use for the sleep function. 

#### Returns
True if successful, false otherwise.
<hr />

### `sleepFor` <a id="class_board_1a31c46d510bbf14e372e019b8789afd3b" class="anchor"></a>

```cpp
bool sleepFor(int hours, int minutes, int seconds, void(*)() callbackFunction)
```

Put the device in sleep mode for a specified amount of time.

#### Parameters
* `hours` The number of hours to sleep. 

* `minutes` The number of minutes to sleep. 

* `seconds` The number of seconds to sleep. 

* `callbackFunction` The function to call when the device wakes up. 

#### Returns
True if successful, false otherwise.
<hr />

### `sleepUntilWakeupEvent` <a id="class_board_1a1d23524e0bfeb7282fa465f3834027e1" class="anchor"></a>

```cpp
void sleepUntilWakeupEvent()
```

Put the device into sleep mode until a wakeup event occurs. This sleep mode is ideal for applications requiring periodic wake-ups or brief intervals of inactivity and reduces consumption to a range between 6mA and 18mA depending on the state of the peripherals. This sleep mode resumes the operation from the last operation. A wakeup event can be an interrupt on a pin or the RTC, depending on what you set with [enableWakeupFromPin()](#class_board_1a94ac54f76a7e8fff5b7c6523af64169a) and [enableWakeupFromRTC()](#class_board_1ae158d0367a2851d1f1f560bcca784412).
<hr />

### `deepSleepUntilWakeupEvent` <a id="class_board_1aa0f7c55bf12f52374a2694aff110836b" class="anchor"></a>

```cpp
void deepSleepUntilWakeupEvent()
```

Put the device into deep sleep mode until a wakeup event occurs. For scenarios demanding drastic power conservation, the Deep Sleep Mode significantly reduces the board's power usage to range between 90uA and 11mA depending on the state of the peripherals. This mode restarts the board on wakeup, effectively running the setup() function again. A wakeup event can be an interrupt on a pin or the RTC, depending on what you set with [enableWakeupFromPin()](#class_board_1a94ac54f76a7e8fff5b7c6523af64169a) and [enableWakeupFromRTC()](#class_board_1ae158d0367a2851d1f1f560bcca784412).
<hr />

### `setAllPeripheralsPower` <a id="class_board_1a27dcc0b9d69a8cce256494192f2efb3a" class="anchor"></a>

```cpp
void setAllPeripheralsPower(bool on)
```

Turn the peripherals on Portenta C33 (ADC, RGB LED, Secure Element, Wifi and Bluetooth) off.

<hr />

### `setCommunicationPeripheralsPower` <a id="class_board_1ac91aa31be1ea833d7266dda45dd1c5f2" class="anchor"></a>

```cpp
void setCommunicationPeripheralsPower(bool on)
```

Set the communication power rail switch direction on Portenta C33 (Wifi, Bluetooth and Secure Element)

#### Parameters
* `on` True to turn on the switches, false to turn them off.
<hr />

### `setAnalogDigitalConverterPower` <a id="class_board_1a3d9fbb30b03c3a7f733f0c89dd9dc43d" class="anchor"></a>

```cpp
void setAnalogDigitalConverterPower(bool on)
```

Set the analog digital converter power rail switch direction on Portenta C33.

#### Parameters
* `on` True to turn on the switches, false to turn them off.
<hr />

### `setReferenceVoltage` <a id="class_board_1a8feb9efc5439c8fec5139f66484200b5" class="anchor"></a>

```cpp
bool setReferenceVoltage(float voltage)
```

Set the reference voltage on Portenta C33. This value is used by the ADC to convert analog values to digital values. This can be particularly useful to increase the accuracy of the ADC when working with low voltages.

#### Parameters
* `voltage` float value of the voltage value to set. It can be any value between 1.80V and 3.30V in steps of 0.10V. Any value outside this range or with different steps will not be accepted by the library. 

#### Returns
True if successful, false otherwise.
<hr />

# class `Charger` <a id="class_charger" class="anchor"></a>

[Charger](#class_charger) class for controlling charging parameters and monitoring charging status.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Charger`](#class_charger_1a386eef9a5c151f3e5eb3ee67a0aeb0cb) | Default constructor. |
| [`Charger`](#class_charger_1a941c1c93e7cca4055cb1b85c19c43824) | Constructor with PMIC instance. |
| [`setChargeCurrent`](#class_charger_1a5e2414a885c3d48a4767c725c1f734bb) | Set the charging current. |
| [`setChargeVoltage`](#class_charger_1aa3c52bef06f8d1069cc10b1829e4e878) | Set the charging voltage. |
| [`setEndOfChargeCurrent`](#class_charger_1a9a68b14cc28c160ba366cfc4eda4d0a0) | Set the end-of-charge current. |
| [`setInputCurrentLimit`](#class_charger_1ab4475b311be03071cf05b3c4ecfa9203) | The input current limit (ILIM) safeguards the device by preventing overcurrent, ensuring the charging current is within safe levels for the battery, and adapting to the maximum current the power source can provide, allowing you to charge and use the system at the same time. |
| [`getChargeStatus`](#class_charger_1a0c1c368e7b7cef05f9491efc4a576cb8) | Get the current charging status. |
| [`enable`](#class_charger_1a6e7a92f5fb4ae1f016ff13d5c716a81f) | Enables the charging functionality with either the default settings or the last saved parameters, depending on what was set previously. |
| [`disable`](#class_charger_1aa87840314777bb23a58cbead63407707) | Disable the charging functionality. |

## Members

### `Charger` <a id="class_charger_1a386eef9a5c151f3e5eb3ee67a0aeb0cb" class="anchor"></a>

```cpp
Charger()
```

Default constructor.

<hr />

### `Charger` <a id="class_charger_1a941c1c93e7cca4055cb1b85c19c43824" class="anchor"></a>

```cpp
Charger(PF1550 * pmic)
```

Constructor with PMIC instance.

#### Parameters
* `pmic` Pointer to the PF1550 PMIC instance.
<hr />

### `setChargeCurrent` <a id="class_charger_1a5e2414a885c3d48a4767c725c1f734bb" class="anchor"></a>

```cpp
void setChargeCurrent(ChargeCurrent current)
```

Set the charging current.

#### Parameters
* `current` Charging current enum value (ChargeCurrent).
<hr />

### `setChargeVoltage` <a id="class_charger_1aa3c52bef06f8d1069cc10b1829e4e878" class="anchor"></a>

```cpp
void setChargeVoltage(ChargeVoltage voltage)
```

Set the charging voltage.

#### Parameters
* `voltage` Charging voltage enum value (ChargeVoltage).
<hr />

### `setEndOfChargeCurrent` <a id="class_charger_1a9a68b14cc28c160ba366cfc4eda4d0a0" class="anchor"></a>

```cpp
void setEndOfChargeCurrent(EndOfChargeCurrent current)
```

Set the end-of-charge current.

#### Parameters
* `current` End-of-charge current enum value (EndOfChargeCurrent).
<hr />

### `setInputCurrentLimit` <a id="class_charger_1ab4475b311be03071cf05b3c4ecfa9203" class="anchor"></a>

```cpp
void setInputCurrentLimit(InputCurrentLimit current)
```

The input current limit (ILIM) safeguards the device by preventing overcurrent, ensuring the charging current is within safe levels for the battery, and adapting to the maximum current the power source can provide, allowing you to charge and use the system at the same time.

#### Parameters
* `current` Maximum input current enum value (InputCurrentLimit).
<hr />

### `getChargeStatus` <a id="class_charger_1a0c1c368e7b7cef05f9491efc4a576cb8" class="anchor"></a>

```cpp
ChargeStatus getChargeStatus()
```

Get the current charging status.

#### Returns
Charging status enum value (ChargeStatus).
<hr />

### `enable` <a id="class_charger_1a6e7a92f5fb4ae1f016ff13d5c716a81f" class="anchor"></a>

```cpp
bool enable()
```

Enables the charging functionality with either the default settings or the last saved parameters, depending on what was set previously.

#### Returns
True if successful, false otherwise.
<hr />

### `disable` <a id="class_charger_1aa87840314777bb23a58cbead63407707" class="anchor"></a>

```cpp
bool disable()
```

Disable the charging functionality.

#### Returns
True if successful, false otherwise.
<hr />

# class `PowerManagement` <a id="class_power_management" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`PowerManagement`](#class_power_management_1acc41d5c24cf751f6924e62c4e602f5b3) | constructor for the [PowerManagement](#class_power_management) |
| [`~PowerManagement`](#class_power_management_1a3d8e868a9d3eb39a971f1cfe901119df) | destructor for the [PowerManagement](#class_power_management) |
| [`begin`](#class_power_management_1a65bcff4dceb0effedd04b20be2e6695e) | start communication with the PMIC chip and the power gauge. |
| [`getBoard`](#class_power_management_1ad732d749ad09d03eff4523b617ec7e7f) | This class centralizes control over the power distribution within the board. It allows users to enable or disable specific power rails, and send the board into low-power modes. |
| [`getBattery`](#class_power_management_1aec3b949e2c9904113a7c406ac7019e00) | Dedicated to battery management, this class enables real-time monitoring of battery usage and health. |
| [`getCharger`](#class_power_management_1ae77d117118b803ba4d35132ab4d5270e) | Focused on battery charging dynamics, this class provides a detailed insight into charging parameters. |

## Members

### `PowerManagement` <a id="class_power_management_1acc41d5c24cf751f6924e62c4e602f5b3" class="anchor"></a>

```cpp
PowerManagement()
```

constructor for the [PowerManagement](#class_power_management)

<hr />

### `~PowerManagement` <a id="class_power_management_1a3d8e868a9d3eb39a971f1cfe901119df" class="anchor"></a>

```cpp
~PowerManagement()
```

destructor for the [PowerManagement](#class_power_management)

<hr />

### `begin` <a id="class_power_management_1a65bcff4dceb0effedd04b20be2e6695e" class="anchor"></a>

```cpp
bool begin()
```

start communication with the PMIC chip and the power gauge.

#### Returns
true if the initialization was successful, false otherwise
<hr />

### `getBoard` <a id="class_power_management_1ad732d749ad09d03eff4523b617ec7e7f" class="anchor"></a>

```cpp
Board getBoard()
```

This class centralizes control over the power distribution within the board. It allows users to enable or disable specific power rails, and send the board into low-power modes.

#### Returns
the [Board](#class_board) object.
<hr />

### `getBattery` <a id="class_power_management_1aec3b949e2c9904113a7c406ac7019e00" class="anchor"></a>

```cpp
Battery getBattery()
```

Dedicated to battery management, this class enables real-time monitoring of battery usage and health.

#### Returns
the [Battery](#class_battery) object.
<hr />

### `getCharger` <a id="class_power_management_1ae77d117118b803ba4d35132ab4d5270e" class="anchor"></a>

```cpp
Charger getCharger()
```

Focused on battery charging dynamics, this class provides a detailed insight into charging parameters.

#### Returns
the [Charger](#class_charger) object.
<hr />

