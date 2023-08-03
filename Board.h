#ifndef BOARD_H
#define BOARD_H

#include <Arduino_PMIC.h>

class Board {
    public:
        Board();
        Board(PF1550 * _pPMIC);
        void begin();
        bool isUSBPowered();
        bool isCharging();
        bool isBatteryPowered();
    
        #if defined(ARDUINO_NICLA_VISION)
        void toggleCameraPower(bool on);
        void toggleExternalPower(bool on);
        #endif 
    private:
       PF1550 * pPMIC;
        
};

#endif