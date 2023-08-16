# Arduino_PowerManagement

This library abstracts the functionality of the PF1550 Power Management IC and MAX17162 LiPo Fuel Gauge found in the Portenta C33, Portenta H7 and Nicla Vision boards. 
It allows you to monitor the battery usage of your board, control and monitor charging parameters, enable or disable specific power rails on each board to save power, as well as change voltages on some of these rails. 

## Examples 
* **/examples/battery** - 
* **/examples/charger** -
* **/examples/external_voltage** -
* **/examples/power_shell** -
* **/examples/toggle_nicla_cameras** - 

## Features

* Monitor current and average battery metrics (viltage, current, percentage, time-to-full, time-to-empty)
* Monitor battery health metrics (power cycles, temperature, reported capacity)
* Monitor and control charging
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
    * On Portenta H7
        * Enable and disable the external power rail
        * Change voltage on external power rail




### Usage 

```cpp
#include "PowerManagement.h"
#include <vector>
#include <string>

PowerManagement manager = PowerManagement();
Battery battery; 
Board board; 
Charger charger;

void setup(){
    manager.begin();
    battery = manager.getBattery();
    board = manager.getBoard();
    charger = manager.getCharger();

    /* Rest of your setup() code */
}
```

#### Battery

#### Charger 

#### Board

##### Nicla vision
##### Portenta C33
##### Portenta H7