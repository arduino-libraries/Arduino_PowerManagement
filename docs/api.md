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
| [`readVoltage`](#class_battery_1acd8af093394d3e3924177a04691c8bce) | Reads the current voltage of the battery. |
| [`readVoltageAvg`](#class_battery_1a1922eebd2c523fbc8840b43f35ed0f86) | Reads the average voltage of the battery. |
| [`readCurrent`](#class_battery_1a0e0fa178fc254bc51e2cfdc5993e7e6f) | Reads the instantaneous current of the battery. |
| [`readCurrentAvg`](#class_battery_1a8db47947e4b0861604a9031e139ccf0b) | Reads the average current of the battery. |
| [`readTemp`](#class_battery_1a089a732a1d40554234e6b655ec3a65f8) | Reads the current temperature of the battery. |
| [`readTempAvg`](#class_battery_1ad9772edbb9968cd893ae0b8839ff876c) | Reads the average temperature of the battery. |
| [`readPercentage`](#class_battery_1a86b221882856ca03f28999ceaff3d16d) | Reads the battery's state of charge (SOC). |
| [`readTimeToEmpty`](#class_battery_1a5608f7ff0c966235988d2a38b966c033) | Reads the estimated time to empty (discharge) of the battery. |
| [`readTimeToFull`](#class_battery_1a210a64027d2cc7db2a360901e6c8957f) | Reads the estimated time to full (charge) of the battery. |
| [`readRemainingCapacity`](#class_battery_1a9fb236afa18c5d688e44f196a63adf4e) | Reads the remaining capacity of the battery. |
| [`readReportedCapacity`](#class_battery_1ab519831bdfb5f6230e94393dc155adee) | Reads the reported capacity of the battery. |

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

### `readVoltage` <a id="class_battery_1acd8af093394d3e3924177a04691c8bce" class="anchor"></a>

```cpp
public unsigned int readVoltage()
```

Reads the current voltage of the battery.

#### Returns
The current voltage in millivolts (mV).
<hr />

### `readVoltageAvg` <a id="class_battery_1a1922eebd2c523fbc8840b43f35ed0f86" class="anchor"></a>

```cpp
public unsigned int readVoltageAvg()
```

Reads the average voltage of the battery.

#### Returns
The average voltage in millivolts (mV).
<hr />

### `readCurrent` <a id="class_battery_1a0e0fa178fc254bc51e2cfdc5993e7e6f" class="anchor"></a>

```cpp
public int readCurrent()
```

Reads the instantaneous current of the battery.

#### Returns
The instantaneous current in miliamperes (mA)
<hr />

### `readCurrentAvg` <a id="class_battery_1a8db47947e4b0861604a9031e139ccf0b" class="anchor"></a>

```cpp
public int readCurrentAvg()
```

Reads the average current of the battery.

#### Returns
The average current in millivolts (mV).
<hr />

### `readTemp` <a id="class_battery_1a089a732a1d40554234e6b655ec3a65f8" class="anchor"></a>

```cpp
public int readTemp()
```

Reads the current temperature of the battery.

#### Returns
The current temperature in degrees Celsius.
<hr />

### `readTempAvg` <a id="class_battery_1ad9772edbb9968cd893ae0b8839ff876c" class="anchor"></a>

```cpp
public int readTempAvg()
```

Reads the average temperature of the battery.

#### Returns
The current temperature in degrees Celsius.
<hr />

### `readPercentage` <a id="class_battery_1a86b221882856ca03f28999ceaff3d16d" class="anchor"></a>

```cpp
public unsigned int readPercentage()
```

Reads the battery's state of charge (SOC).

#### Returns
The state of charge as a percentage.
<hr />

### `readTimeToEmpty` <a id="class_battery_1a5608f7ff0c966235988d2a38b966c033" class="anchor"></a>

```cpp
public unsigned int readTimeToEmpty()
```

Reads the estimated time to empty (discharge) of the battery.

#### Returns
The estimated time to empty in minutes.
<hr />

### `readTimeToFull` <a id="class_battery_1a210a64027d2cc7db2a360901e6c8957f" class="anchor"></a>

```cpp
public unsigned int readTimeToFull()
```

Reads the estimated time to full (charge) of the battery.

#### Returns
The estimated time to full in minutes.
<hr />

### `readRemainingCapacity` <a id="class_battery_1a9fb236afa18c5d688e44f196a63adf4e" class="anchor"></a>

```cpp
public unsigned int readRemainingCapacity()
```

Reads the remaining capacity of the battery.

#### Returns
The remaining capacity in milliampere-hours (mAh).
<hr />

### `readReportedCapacity` <a id="class_battery_1ab519831bdfb5f6230e94393dc155adee" class="anchor"></a>

```cpp
public unsigned int readReportedCapacity()
```

Reads the reported capacity of the battery.

#### Returns
The reported capacity in milliampere-hours (mAh).
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
| [`enableCharger`](#class_charger_1aaf1b927bdc15214b64913fddf88f0208) | Enable the charger. |
| [`disableCharger`](#class_charger_1a1584e0507a90236a72f56cf298cf77b5) | Disable the charger. |

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

### `enableCharger` <a id="class_charger_1aaf1b927bdc15214b64913fddf88f0208" class="anchor"></a>

```cpp
public bool enableCharger()
```

Enable the charger.

#### Returns
True if successful, false otherwise.
<hr />

### `disableCharger` <a id="class_charger_1a1584e0507a90236a72f56cf298cf77b5" class="anchor"></a>

```cpp
public bool disableCharger()
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

