#ifndef CHARGER_H

#include <Arduino_PF1550.h>
#include "WireUtils.h"

typedef VFastCharge ChargeVoltage;
typedef IFastCharge ChargeCurrent;
typedef IEndOfCharge EndOfChargeCurrent;
typedef IInputCurrentLimit InputCurrentLimit;

/**
 * Enum representing different states of charging.
 */

enum class ChargingState {
    /**
     * Provided by the registers, not used in this API.
     */
    none = -1,

    /**
     * First stage of the charging process, prepares battery for the charging process.
     */
    preCharge = 0,

    /**
     * Second phase of the charging process where the battery is charging in constant current mode until it reaches the voltage where the it's considered fully charged. (4.2V)
     */
    fastChargeConstantCurrent = 1,

    /**
     * Third phase of the charging process where the battery is kept at the fully charged voltage and current is slowly decreased to the end of charge current.
     */
    fastChargeConstantVoltage = 2,

    /**
     * If the battery is still connected, the charger will ensure it's kept at 4.2V by topping up the voltage to avoid self discharge.
     */
    endOfCharge = 3,

    /** 
     * Battery is fully charged
     */
    done = 4,
    
    /** 
     * The timer that is monitoring the charge status has encountered an error.
     */
    timerFaultError = 6,
    
    /** 
     * Charging was suspended due to overheating
     */
    thermistorSuspendError = 7,
    
    /** 
     * Charger is disabled
     */
    chargerDisabled = 8,
    
    /** 
     *  Charging was suspended due to an overvoltage fault
     */
    batteryOvervoltageError = 9,
    
    /** 
     * The charger is bypassed completely and the USB voltage is powering the board
     */
    chargerBypassed = 12
};

/**
 * @brief Class for controlling charging parameters and monitoring charging status.
 */
class Charger {
public:
    /**
     * @brief Constructs a new Charger object.
     */
    Charger();

    /**
     * @brief Initializes the charger by initiating the PMIC.
     * 
     * @return true if the charger initialization is successful, false otherwise.
     */
    bool begin();

    /**
     * @brief Set the charging current. 
     * The default charging current is set to 100mA.
     * @param current Charging current in milli amperes (mA).
     * Supported values: 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000
     * @return True if successful, false if an invalid value was provided or if the PMIC communication failed.
     */
    bool setChargeCurrent(uint16_t current);

    /**
     * @brief Get the charge current in milli amperes (mA).
     * @return The charge current in float.
     */
    uint16_t getChargeCurrent();

    /**
     * @brief Set the charging voltage in volts (V).
     * The current charging voltage is set to 4.2V by default.
     * @param voltage Charging voltage in volts (V).
     * Supported values: 3.50, 3.52, 3.54, 3.56, 3.58, 3.60, 3.62, 3.64, 3.66, 3.68, 3.70, 3.72, 3.74, 3.76, 
     * 3.78, 3.80, 3.82, 3.84, 3.86, 3.88, 3.90, 3.92, 3.94, 3.96, 3.98, 4.00, 4.02, 4.04, 4.06, 4.08, 4.10, 
     * 4.12, 4.14, 4.16, 4.18, 4.20, 4.22, 4.24, 4.26, 4.28, 4.30, 4.32, 4.34, 4.36, 4.38, 4.40, 4.42, 4.44
     * @return True if successful, false if an invalid value was provided or if the PMIC communication failed.
     */
    bool setChargeVoltage(float voltage);

    /**
     * @brief Get the charge voltage in volts (V).
     * @return The charge voltage as a float value.
     */
    float getChargeVoltage();

    /**
     * @brief Set the end-of-charge current.
     * The charger IC determines when to terminate the charge cycle based on the current going into the battery 
     * dropping below the given threshold during the constant voltage phase. At this point, the battery 
     * is considered fully charged and charging is completed. If charge termination is disabled, 
     * the charge current will naturally decay to 0mA, but this is rarely done in practice. 
     * This is because the amount of charge going into the battery exponentially decreases during CV charging, 
     * and it would take a significantly longer time to recharge the battery with a very little increase in capacity.
     * @param current End-of-charge current in milli amperes (mA).
     * The default end-of-charge current is set to 50 mA.
     * Supported values: 5, 10, 20, 30, 50
     * @return True if successful, false if an invalid value was provided or if the PMIC communication failed.
     */
    bool setEndOfChargeCurrent(uint16_t current);

    /**
     * @brief Get the end of charge current.
     * 
     * This function returns the current value at which the charging process is considered complete.
     * Charging is terminated when the supplied current drops below the pre-programmed end of charge level. 
     * 
     * @return The end of charge current.
     */
    uint16_t getEndOfChargeCurrent();

    /**
     * @brief The input current limit (ILIM) safeguards the device by preventing overcurrent, 
     * ensuring the charging current is within safe levels for the battery, and adapting to the maximum 
     * current the power source can provide, allowing you to charge and use the system at the same time. 
     * The default input current limit is set to 1.5A.
     * @param current Maximum input current in milli amperes (mA).
    * Supported values: 10, 15, 20, 25, 30, 35, 40, 45, 50, 100, 150, 200, 300, 
    * 400, 500, 600, 700, 800, 900, 1000, 1500
     * @return True if successful, false if an invalid value was provided or if the PMIC communication failed.
     */
    bool setInputCurrentLimit(uint16_t current);

    /**
     * @brief Get the input current limit. It is a safeguard to prevent overcurrent when charging
     * respectively to the maximum current the power source can provide.
     * 
     * @return The input current limit in milli amperes (mA).
     */
    uint16_t getInputCurrentLimit();

    /**
     * @brief Get the current charging status.
     * @return Charging status enum value (ChargingState).
     * The possible states are:
     * - none: Provided by the registers, not used in this API.
     * - preCharge: First stage of the charging process, prepares battery for the charging process.
     * - fastChargeConstantCurrent: Second phase of the charging process where the battery is charging in constant current mode until it reaches the voltage where the it's considered fully charged. (4.2V)
     * - fastChargeConstantVoltage: Third phase of the charging process where the battery is kept at the fully charged voltage and current is slowly decreased to the end of charge current.
     * - endOfCharge: If the battery is still connected, the charger will ensure it's kept at 4.2V by topping up the voltage to avoid self discharge.
     * - done: Battery is fully charged
     * - timerFaultError: The timer that is monitoring the charge status has encountered an error.
     * - thermistorSuspendError: Charging was suspended due to overheating
     * - chargerDisabled: Charger is disabled
     * - batteryOvervoltageError: Charging was suspended due to an overvoltage fault
     * - chargerBypassed: The charger is bypassed completely and the USB voltage is powering the board
     */
    ChargingState getState();

    /**
     * @brief Checks if the charger and thus charging is enabled.
     * By default, the charger is enabled.
     * @return true if the charger is enabled, false otherwise.
     */
    bool isEnabled();

    /**
     * @brief Sets the enabled state of the charger.
     * When enabling it uses the default settings or the last saved parameters, depending on what was set previously. 
     * @param enabled The desired enabled state of the charger.
     * @return true if the enabled state was successfully set, false otherwise.
     */
    bool setEnabled(bool enabled);
};

#endif // CHARGER_H