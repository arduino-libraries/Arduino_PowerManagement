
#ifndef POWER_MANAGEMENT_H
#define POWER_MANAGEMENT_H 

#include <Arduino.h>
#include "Board.h"
#include "Battery.h"
#include "Charger.h"
#include <Arduino_PMIC.h>



class PowerManagement{
    public: 
        /**
         * @brief constructor for the PowerManagement 
         */
        PowerManagement();

        /**
         * @brief start communication with the PMIC chip and the power gauge. 
        */
        void begin();
        
        /**
         * @brief returns the initialised instance of the Board class
         * @returns returns the dereferenced board pointer (actual Board instance)
        */
        Board getBoard();
        
        /**
         * @brief returns the initialised instance of the Battery class
         * @returns returns the dereferenced bbattery pointer (actual Battery instance)
        */
        Battery getBattery();
        
        /** 
         * @brief returns the initialised instance of the Charger class
         * @returns returns the dereferenced charger pointer (actual Charger instance)
         */
        Charger getCharger();

    private:
        Battery * battery;
        Board * board;
        Charger * charger;
        PF1550 * pPMIC;
};




#endif