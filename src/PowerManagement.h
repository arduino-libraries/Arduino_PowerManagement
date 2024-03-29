#ifndef POWER_MANAGEMENT_H
#define POWER_MANAGEMENT_H 

#include <Arduino.h>
#include "Board.h"
#include "Battery.h"
#include "Charger.h"
#include <Arduino_PF1550.h>

/**
 * @brief The PowerManagement class is responsible for centralizing control over power distribution within the board.
 * It provides functions to start communication with the PMIC chip and power gauge, and access objects for board, battery, and charger management.
 */
class PowerManagement{
    public: 
        /**
         * @brief constructor for the PowerManagement 
         */
        PowerManagement();

        /**
         * @brief destructor for the PowerManagement
         */
        ~PowerManagement();

        /**
         * @brief start communication with the PMIC chip and the power gauge. 
         * @returns true if the initialization was successful, false otherwise
         */
        bool begin();
        
        /**
         * @brief This class centralizes control over the power distribution within the board. It allows users to enable or disable specific power rails, and send the board into low-power modes. 
         * @returns the Board object.
         */
        Board getBoard();

        /**
         * @brief Focused on battery health and usage, this class provides a detailed insight into the battery's health and usage.
         * @returns the Battery object. 
         */
        Battery getBattery();
        
        /** 
         * @brief Focused on battery charging dynamics, this class provides a detailed insight into charging parameters.
         * @returns the Charger object. 
         */
        Charger getCharger();

    private:
        Battery * battery = nullptr;
        Board * board = nullptr;
        Charger * charger = nullptr;
};

#endif
