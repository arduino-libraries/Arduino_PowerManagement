# Power ManagemtnInteractive Shell

This sketch demonstrates the usage of the Power Management library to control and monitor power-related features of different Arduino boards. The sketch allows you to interact with various power management functionalities such as battery monitoring, charging control, and voltage rail adjustments.

## Instructions

1. Upload the sketch to your Arduino board.
2. Open the serial monitor at a baud rate of 115200.
3. Use the provided commands to interact with power management features.

## Commands and Parameters

### Toggle Rail
Toggle the state of a specific power rail.

Command: `toggle_rail <rail_name> <on/off>`

- `<rail_name>`: Specify the name of the power rail to toggle.
  - Options: `C33_external`, `C33_communication`, `H7_external`, `nicla_external`, `nicla_camera`
- `<on/off>`: Specify whether to turn the rail on or off.
  - Options: `1` (on) or `0` (off)

### Set Rail Voltage
Set the voltage of a specific power rail.

Command: `set_rail_voltage <rail_name> <voltage>`

- `<rail_name>`: Specify the name of the power rail to set the voltage for.
  - Options: `C33_reference`, `C33_analog`, `C33_external`, `H7_external`, `nicla_external`
- `<voltage>`: Specify the voltage value to set for the rail.
  - Note: Voltage values must be within the acceptable range for the specific rail.

### Toggle Charger
Toggle the state of the battery charger.

Command: `toggle_charger <on/off>`

- `<on/off>`: Specify whether to enable or disable the charger.
  - Options: `1` (on) or `0` (off)

### Status
Display the status of the board, charger, and battery metrics.

Command: `status`

## Notes

- Make sure to follow the guidelines for voltage and rail names to avoid unexpected behavior.
- Be cautious when adjusting voltage values, as incorrect values may damage your board or battery.

## Example Usage

1. To turn on the external power rail on a Portenta C33:
   ```
   toggle_rail C33_external 1
   ```

2. To set the reference voltage to 1.20V on a Portenta C33:
   ```
   set_rail_voltage C33_reference 1.20
   ```

3. To enable the charger:
   ```
   toggle_charger 1
   ```

4. To view the status of the board, charger, and battery metrics:
   ```
   status
   ```

## License

This sketch and library are provided under the [MIT License](LICENSE).
```

Feel free to modify and expand upon this template to suit your specific project and requirements.