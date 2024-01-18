# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class ` [`Battery`](#class_battery) | 
`class ` [`Board`](#class_board) | 
`class ` [`Charger`](#class_charger) | [Charger](#class_charger) class for controlling charging parameters and monitoring charging status.
`class ` [`PowerManagement`](#class_power_management) | 

# class `Battery` <a id="class_battery" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Battery`](#class_battery_1a36a6234c583e3b3506f4a77e3eb49989) | Constructor for the [Battery](#class_battery) class. |
| [`begin`](#class_battery_1ae22175033a63ac6cf222973f2498d193) | Initializes the battery communication and configuration. |
| [`isConnected`](#class_battery_1a9473c4a4583abea991268d0818f19dbe) | Checks if a battery is connected to the system. |
| [`voltage`](#class_battery_1a00b9ab137ea97c46da061537473b409f) | Reads the current voltage of the battery. |
| [`voltageAverage`](#class_battery_1ad25a5eae3bc9c879fa673c29c4f2c524) | Reads the average voltage of the battery. |
| [`current`](#class_battery_1acc60fb79f995897dbcad56535b4ddc7f) | Reads the instantaneous current of the battery. |
| [`currentAverage`](#class_battery_1a4f7e36bc2d78754a9f3bf13f18ed16f2) | Reads the average current of the battery. |
| [`temperature`](#class_battery_1a9769b18902c4576c3ed7405c7e58bbea) | Reads the current temperature of the battery. |
| [`temperatureAverage`](#class_battery_1a898ee9d9492aee01489db146e8df163d) | Reads the average temperature of the battery. |
| [`percentage`](#class_battery_1ae95736b1cd05268257937a00b20a707b) | Reads the battery's state of charge (SOC). |
| [`remainingCapacity`](#class_battery_1afd66687ef99d7d2c88a501fa9dfaf579) | Reads the remaining capacity of the battery. |

## Members

### `Battery` <a id="class_battery_1a36a6234c583e3b3506f4a77e3eb49989" class="anchor"></a>

```cpp
public Battery()
```

Constructor for the [Battery](#class_battery) class.

<hr />

### `begin` <a id="class_battery_1ae22175033a63ac6cf222973f2498d193" class="anchor"></a>

```cpp
public void begin()
```

Initializes the battery communication and configuration.

<hr />

### `isConnected` <a id="class_battery_1a9473c4a4583abea991268d0818f19dbe" class="anchor"></a>

```cpp
public boolean isConnected()
```

Checks if a battery is connected to the system.

#### Returns
True if a battery has been connected, false otherwise
<hr />

### `voltage` <a id="class_battery_1a00b9ab137ea97c46da061537473b409f" class="anchor"></a>

```cpp
public unsigned int voltage()
```

Reads the current voltage of the battery.

#### Returns
The current voltage in millivolts (mV).
<hr />

### `voltageAverage` <a id="class_battery_1ad25a5eae3bc9c879fa673c29c4f2c524" class="anchor"></a>

```cpp
public unsigned int voltageAverage()
```

Reads the average voltage of the battery.

#### Returns
The average voltage in millivolts (mV).
<hr />

### `current` <a id="class_battery_1acc60fb79f995897dbcad56535b4ddc7f" class="anchor"></a>

```cpp
public int current()
```

Reads the instantaneous current of the battery.

#### Returns
The instantaneous current in miliamperes (mA)
<hr />

### `currentAverage` <a id="class_battery_1a4f7e36bc2d78754a9f3bf13f18ed16f2" class="anchor"></a>

```cpp
public int currentAverage()
```

Reads the average current of the battery.

#### Returns
The average current in millivolts (mV).
<hr />

### `temperature` <a id="class_battery_1a9769b18902c4576c3ed7405c7e58bbea" class="anchor"></a>

```cpp
public int temperature()
```

Reads the current temperature of the battery.

#### Returns
The current temperature in degrees Celsius.
<hr />

### `temperatureAverage` <a id="class_battery_1a898ee9d9492aee01489db146e8df163d" class="anchor"></a>

```cpp
public int temperatureAverage()
```

Reads the average temperature of the battery.

#### Returns
The current temperature in degrees Celsius.
<hr />

### `percentage` <a id="class_battery_1ae95736b1cd05268257937a00b20a707b" class="anchor"></a>

```cpp
public unsigned int percentage()
```

Reads the battery's state of charge (SOC).

#### Returns
The state of charge as a percentage.
<hr />

### `remainingCapacity` <a id="class_battery_1afd66687ef99d7d2c88a501fa9dfaf579" class="anchor"></a>

```cpp
public unsigned int remainingCapacity()
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
| [`Board`](#class_board_1af301b08c1cc0ee86c31985d204d1e53c) | Constructor for the [Board](#class_board) class with a PF1550 PMIC instance. |
| [`isUSBPowered`](#class_board_1aa53bea8ac0404de8a7389484a61937ae) | Check if the board is powered through USB. |
| [`isBatteryPowered`](#class_board_1a80a62c172bea4a16b6983f204380f92b) | Check if the board is powered by the battery. |
| [`setExternalSwitch`](#class_board_1ae6128ca6cfee4780699646ded2971c10) | Set the external power lane switch state. |
| [`setExternalVoltage`](#class_board_1ac85a176efa19e65c688fcb27b5170000) | Set the voltage for the external power rail. |
| [`setCameraSwitch`](#class_board_1abfb2f9501dbcd20ebc0a2da9db0c8b86) | Set the camera power rail switch state on Nicla Vision. |
| [`enableWakeupFromPin`](#class_board_1a001bd0741f8dc4d1827f4726089cbb4c) | Enables wake-up of the device from a specified pin (A0, A1, A2, A3, A4, A5, D4, D7 )  |
| [`enableWakeupFromRTC`](#class_board_1ae158d0367a2851d1f1f560bcca784412) | Enables wake-up of the device from the RTC. |
| [`sleepFor`](#class_board_1a966bcfa00c60eaf3b0a1aa89d1deea9d) | Put the device in sleep mode for a specified amount of time. |
| [`sleepUntilWakeupEvent`](#class_board_1a1d23524e0bfeb7282fa465f3834027e1) | Put the device into sleep mode until a wakeup event occurs. |
| [`deepSleepUntilWakeupEvent`](#class_board_1aa0f7c55bf12f52374a2694aff110836b) | Put the device into deep sleep mode until a wakeup event occurs. |
| [`turnPeripheralsOff`](#class_board_1a8e78bbbcc6638a365e30d2d846ddb2a7) | Turn the peripherals on Portenta C33 (ADC, RGB LED, Secure Element, Wifi and Bluetooth) off. |
| [`turnPeripheralsOn`](#class_board_1adba07ed1d75e90fe5d2ebdca75c9a2a8) | Turn the peripherals on Portenta C33 back on. (ADC, RGB LED, Secure Element, Wifi and Bluetooth) |
| [`setCommunicationSwitch`](#class_board_1a446d0b15dc91554c1e6102e655adc837) | Set the communication power rail switch state on Portenta C33 (Wifi, Bluetooth and Secure Element) |
| [`setAnalogVoltage`](#class_board_1a02fc8e3eb090a4ee5fb0b3f482e52b1f) | Set the analog voltage on Portenta C33. |
| [`setReferenceVoltage`](#class_board_1ae76e10f866abc11788e7bffa770c4567) | Set the reference voltage on Portenta C33. |

## Members

### `Board` <a id="class_board_1a9ee491d4fea680cf69b033374a9fdfcb" class="anchor"></a>

```cpp
public Board()
```

Default constructor for the [Board](#class_board) class.

<hr />

### `Board` <a id="class_board_1af301b08c1cc0ee86c31985d204d1e53c" class="anchor"></a>

```cpp
public Board(PF1550 * _pPMIC)
```

Constructor for the [Board](#class_board) class with a PF1550 PMIC instance.

#### Parameters
* `_pPMIC` Pointer to the PF1550 PMIC instance.
<hr />

### `isUSBPowered` <a id="class_board_1aa53bea8ac0404de8a7389484a61937ae" class="anchor"></a>

```cpp
public bool isUSBPowered()
```

Check if the board is powered through USB.

#### Returns
True if powered through USB, false otherwise.
<hr />

### `isBatteryPowered` <a id="class_board_1a80a62c172bea4a16b6983f204380f92b" class="anchor"></a>

```cpp
public bool isBatteryPowered()
```

Check if the board is powered by the battery.

#### Returns
True if powered by the battery, false otherwise.
<hr />

### `setExternalSwitch` <a id="class_board_1ae6128ca6cfee4780699646ded2971c10" class="anchor"></a>

```cpp
public void setExternalSwitch(bool on)
```

Set the external power lane switch state.

#### Parameters
* `on` True to turn on the switch, false to turn it off.
<hr />

### `setExternalVoltage` <a id="class_board_1ac85a176efa19e65c688fcb27b5170000" class="anchor"></a>

```cpp
public bool setExternalVoltage(float v)
```

Set the voltage for the external power rail.

#### Parameters
* `v` Voltage value to set. (as float) 

#### Returns
True if successful, false otherwise.
<hr />

### `setCameraSwitch` <a id="class_board_1abfb2f9501dbcd20ebc0a2da9db0c8b86" class="anchor"></a>

```cpp
public void setCameraSwitch(bool on)
```

Set the camera power rail switch state on Nicla Vision.

#### Parameters
* `on` True to turn on the switches, false to turn them off.
<hr />

### `enableWakeupFromPin` <a id="class_board_1a001bd0741f8dc4d1827f4726089cbb4c" class="anchor"></a>

```cpp
public void enableWakeupFromPin(uint8_t pin, PinStatus state)
```

Enables wake-up of the device from a specified pin (A0, A1, A2, A3, A4, A5, D4, D7 ) 
#### Parameters
* `pin` The pin number used for waking up the device. 

* `direction` The direction of the interrupt that will wake up the device. (RISING, FALLING)
<hr />

### `enableWakeupFromRTC` <a id="class_board_1ae158d0367a2851d1f1f560bcca784412" class="anchor"></a>

```cpp
public void enableWakeupFromRTC()
```

Enables wake-up of the device from the RTC.
<hr />

### `sleepFor` <a id="class_board_1a966bcfa00c60eaf3b0a1aa89d1deea9d" class="anchor"></a>

```cpp
public bool sleepFor(int hours, int minutes, int seconds, void(*)() callbackFunction, RTClock * rtc)
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

### `sleepUntilWakeupEvent` <a id="class_board_1a1d23524e0bfeb7282fa465f3834027e1" class="anchor"></a>

```cpp
public void sleepUntilWakeupEvent()
```

Put the device into sleep mode until a wakeup event occurs.

<hr />

### `deepSleepUntilWakeupEvent` <a id="class_board_1aa0f7c55bf12f52374a2694aff110836b" class="anchor"></a>

```cpp
public void deepSleepUntilWakeupEvent()
```

Put the device into deep sleep mode until a wakeup event occurs.

<hr />

### `turnPeripheralsOff` <a id="class_board_1a8e78bbbcc6638a365e30d2d846ddb2a7" class="anchor"></a>

```cpp
public void turnPeripheralsOff()
```

Turn the peripherals on Portenta C33 (ADC, RGB LED, Secure Element, Wifi and Bluetooth) off.

<hr />

### `turnPeripheralsOn` <a id="class_board_1adba07ed1d75e90fe5d2ebdca75c9a2a8" class="anchor"></a>

```cpp
public void turnPeripheralsOn()
```

Turn the peripherals on Portenta C33 back on. (ADC, RGB LED, Secure Element, Wifi and Bluetooth)

<hr />

### `setCommunicationSwitch` <a id="class_board_1a446d0b15dc91554c1e6102e655adc837" class="anchor"></a>

```cpp
public void setCommunicationSwitch(bool on)
```

Set the communication power rail switch state on Portenta C33 (Wifi, Bluetooth and Secure Element)

#### Parameters
* `on` True to turn on the switches, false to turn them off.
<hr />

### `setAnalogVoltage` <a id="class_board_1a02fc8e3eb090a4ee5fb0b3f482e52b1f" class="anchor"></a>

```cpp
public bool setAnalogVoltage(float v)
```

Set the analog voltage on Portenta C33.

#### Parameters
* `v` Voltage value to set (as float). 

#### Returns
True if successful, false otherwise.
<hr />

### `setReferenceVoltage` <a id="class_board_1ae76e10f866abc11788e7bffa770c4567" class="anchor"></a>

```cpp
public bool setReferenceVoltage(float v)
```

Set the reference voltage on Portenta C33.

#### Parameters
* `v` Voltage value to set (as float). 

#### Returns
True if successful, false otherwise.
<hr />

# class `Charger` <a id="class_charger" class="anchor"></a>

[Charger](#class_charger) class for controlling charging parameters and monitoring charging status.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`Charger`](#class_charger_1a386eef9a5c151f3e5eb3ee67a0aeb0cb) | Default constructor. |
| [`Charger`](#class_charger_1ab7a66c8e07b9893bf588e1d970cfa572) | Constructor with PMIC instance. |
| [`setChargeCurrent`](#class_charger_1ac201e063885cc09e5bee43e215aead23) | Set the charging current. |
| [`setChargeVoltage`](#class_charger_1a67fb56239f6314d960a4939b36236e07) | Set the charging voltage. |
| [`setEndOfChargeCurrent`](#class_charger_1af700e2c163f75f25173b3db85054edb5) | Set the end-of-charge current. |
| [`setMaxInputCurrent`](#class_charger_1a7e6894f37c7d4a4554fd634a0d7405cc) | Set the maximum input current. |
| [`getChargeStatus`](#class_charger_1a0c1c368e7b7cef05f9491efc4a576cb8) | Get the current charging status. |
| [`enable`](#class_charger_1a6e7a92f5fb4ae1f016ff13d5c716a81f) | Enable the charger. |
| [`disable`](#class_charger_1aa87840314777bb23a58cbead63407707) | Disable the charger. |

## Members

### `Charger` <a id="class_charger_1a386eef9a5c151f3e5eb3ee67a0aeb0cb" class="anchor"></a>

```cpp
public Charger()
```

Default constructor.

<hr />

### `Charger` <a id="class_charger_1ab7a66c8e07b9893bf588e1d970cfa572" class="anchor"></a>

```cpp
public Charger(PF1550 * _pPMIC)
```

Constructor with PMIC instance.

#### Parameters
* `_pPMIC` Pointer to the PF1550 PMIC instance.
<hr />

### `setChargeCurrent` <a id="class_charger_1ac201e063885cc09e5bee43e215aead23" class="anchor"></a>

```cpp
public void setChargeCurrent(ChargeCurrent i)
```

Set the charging current.

#### Parameters
* `i` Charging current enum value (ChargeCurrent).
<hr />

### `setChargeVoltage` <a id="class_charger_1a67fb56239f6314d960a4939b36236e07" class="anchor"></a>

```cpp
public void setChargeVoltage(ChargeVoltage v)
```

Set the charging voltage.

#### Parameters
* `v` Charging voltage enum value (ChargeVoltage).
<hr />

### `setEndOfChargeCurrent` <a id="class_charger_1af700e2c163f75f25173b3db85054edb5" class="anchor"></a>

```cpp
public void setEndOfChargeCurrent(EndOfChargeCurrent i)
```

Set the end-of-charge current.

#### Parameters
* `i` End-of-charge current enum value (EndOfChargeCurrent).
<hr />

### `setMaxInputCurrent` <a id="class_charger_1a7e6894f37c7d4a4554fd634a0d7405cc" class="anchor"></a>

```cpp
public void setMaxInputCurrent(MaxInputCurrent i)
```

Set the maximum input current.

#### Parameters
* `i` Maximum input current enum value (MaxInputCurrent).
<hr />

### `getChargeStatus` <a id="class_charger_1a0c1c368e7b7cef05f9491efc4a576cb8" class="anchor"></a>

```cpp
public ChargeStatus getChargeStatus()
```

Get the current charging status.

#### Returns
Charging status enum value (ChargeStatus).
<hr />

### `enable` <a id="class_charger_1a6e7a92f5fb4ae1f016ff13d5c716a81f" class="anchor"></a>

```cpp
public bool enable()
```

Enable the charger.

#### Returns
True if successful, false otherwise.
<hr />

### `disable` <a id="class_charger_1aa87840314777bb23a58cbead63407707" class="anchor"></a>

```cpp
public bool disable()
```

Disable the charger.

#### Returns
True if successful, false otherwise.
<hr />

# class `PowerManagement` <a id="class_power_management" class="anchor"></a>

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`PowerManagement`](#class_power_management_1acc41d5c24cf751f6924e62c4e602f5b3) | constructor for the [PowerManagement](#class_power_management) |
| [`begin`](#class_power_management_1ace2dda7f9dd9536b5cfcd6d91ece7f2f) | start communication with the PMIC chip and the power gauge. |
| [`getBoard`](#class_power_management_1ad732d749ad09d03eff4523b617ec7e7f) | returns the initialised instance of the [Board](#class_board) class |
| [`getBattery`](#class_power_management_1aec3b949e2c9904113a7c406ac7019e00) | returns the initialised instance of the [Battery](#class_battery) class |
| [`getCharger`](#class_power_management_1ae77d117118b803ba4d35132ab4d5270e) | returns the initialised instance of the [Charger](#class_charger) class |

## Members

### `PowerManagement` <a id="class_power_management_1acc41d5c24cf751f6924e62c4e602f5b3" class="anchor"></a>

```cpp
public PowerManagement()
```

constructor for the [PowerManagement](#class_power_management)

<hr />

### `begin` <a id="class_power_management_1ace2dda7f9dd9536b5cfcd6d91ece7f2f" class="anchor"></a>

```cpp
public void begin()
```

start communication with the PMIC chip and the power gauge.

<hr />

### `getBoard` <a id="class_power_management_1ad732d749ad09d03eff4523b617ec7e7f" class="anchor"></a>

```cpp
public Board getBoard()
```

returns the initialised instance of the [Board](#class_board) class

#### Returns
returns the dereferenced board pointer (actual [Board](#class_board) instance)
<hr />

### `getBattery` <a id="class_power_management_1aec3b949e2c9904113a7c406ac7019e00" class="anchor"></a>

```cpp
public Battery getBattery()
```

returns the initialised instance of the [Battery](#class_battery) class

#### Returns
returns the dereferenced bbattery pointer (actual [Battery](#class_battery) instance)
<hr />

### `getCharger` <a id="class_power_management_1ae77d117118b803ba4d35132ab4d5270e" class="anchor"></a>

```cpp
public Charger getCharger()
```

returns the initialised instance of the [Charger](#class_charger) class

#### Returns
returns the dereferenced charger pointer (actual [Charger](#class_charger) instance)
<hr />

