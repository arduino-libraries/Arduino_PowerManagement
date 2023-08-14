#! /bin/bash
#echo "---- COMPILING FOR NICLA VISION ----"
#arduino-cli compile -b arduino:mbed_nicla:nicla_vision 
#echo "---- COMPILING FOR C33 ----"
#arduino-cli compile -b arduino:renesas_portenta:portenta_c33
#echo "---- COMPILING FOR H7 ----"


#arduino-cli compile -b arduino:mbed_portenta:envie_m7 --library "/home/c.dragomir/ArduinoWorkspace/Repos/Arduino_PF1550"
#arduino-cli upload -b arduino:mbed_portenta:envie_m7

arduino-cli compile -b arduino:mbed_nicla:nicla_vision  --library "/home/c.dragomir/ArduinoWorkspace/Repos/Arduino_PF1550"
arduino-cli upload -b arduino:mbed_nicla:nicla_vision --port "/dev/ttyACM0"