
#ifndef POWERMANAGER_H
#define POWERMANAGER_H 

#include <Arduino.h>
#include "Board.h"
#include "Battery.h"
#include <Arduino_PMIC.h>

//#include "Charger.h"

class PowerManagement{
    public: 
        PowerManagement();
        void begin();
        Board getBoard();
        Battery getBattery();
        //Charger getCharger();


    private:
        Battery * battery;
        Board * board;
        //Charger * charger;
        PF1550 * pPMIC;
};




#endif