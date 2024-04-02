#include <Arduino_PF1550.h>
#include "wireUtils.h"

typedef VFastCharge ChargeVoltage;
typedef IFastCharge ChargeCurrent;
typedef IEndOfCharge EndOfChargeCurrent;
typedef IInputCurrentLimit InputCurrentLimit;

/**
 * Enum representing different states of charging. 
 * @see #None
 * @see #PreCharge
 * @see #FastChargeConstantCurrent
 * @see #FastChargeConstantVoltage
 * @see #EndOfCharge
 * @see #Done
 * @see #TimerFaultError
 * @see #ThermistorSuspendError
 * @see #ChargerDisabled
 * @see #BatteryOvervoltageError
 * @see #ChargerBypassed
 */

enum class ChargingState {
    /**
     * Provided by the registers, not used in this API.
     */
    None = -1,

    /**
     * First stage of the charging process, prepares battery for the charging process.
     */
    PreCharge = 0,

    /**
     * Second phase of the charging process where the battery is charging in constant current mode until it reaches the voltage where the it's considered fully charged. (4.2V)
     */
    FastChargeConstantCurrent = 1,

    /**
     * Third phase of the charging process where the battery is kept at the fully charged voltage and current is slowly decreased to the end of charge current.
     */
    FastChargeConstantVoltage = 2,

    /**
     * If the battery is still connected, the charger will ensure it's kept at 4.2V by topping up the voltage to avoid self discharge.
     */
    EndOfCharge = 3,

    /** 
     * Battery is fully charged
     */
    Done = 4,
    
    /** 
     * The timer that is monitoring the charge status has encountered an error.
     */
    TimerFaultError = 6,
    
    /** 
     * Charging was suspended due to overheating
     */
    ThermistorSuspendError = 7,
    
    /** 
     * Charger is disabled
     */
    ChargerDisabled = 8,
    
    /** 
     *  Charging was suspended due to an overvoltage fault
     */
    BatteryOvervoltageError = 9,
    
    /** 
     * The charger is bypassed completely and the USB voltage is powering the board
     */
    ChargerBypassed = 12
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
     * The default charging current is set to 0.1A.
     * @param current Charging current in amperes (A).
     * Supported values: 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0
     * @return True if successful, false if an invalid value was provided or if the PMIC communication failed.
     */
    bool setChargeCurrent(float current);

    /**
     * @brief Get the charge current in amperes (A).
     * @return The charge current in float.
     */
    float getChargeCurrent();

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
     * The default end-of-charge current is set to 0.05A.
     * @param current End-of-charge current in amperes (A).
     * Supported values: 0.005, 0.01, 0.02, 0.03, 0.05
     * @return True if successful, false if an invalid value was provided or if the PMIC communication failed.
     */
    bool setEndOfChargeCurrent(float current);

    /**
     * @brief Get the end of charge current.
     * 
     * This function returns the current value at which the charging process is considered complete.
     * Charging is terminated when the supplied current drops below the pre-programmed end of charge level. 
     * 
     * @return The end of charge current.
     */
    float getEndOfChargeCurrent();

    /**
     * @brief The input current limit (ILIM) safeguards the device by preventing overcurrent, 
     * ensuring the charging current is within safe levels for the battery, and adapting to the maximum 
     * current the power source can provide, allowing you to charge and use the system at the same time. 
     * The default input current limit is set to 1.5A.
     * @param current Maximum input current in amperes (A).
     * Supported values: 0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05, 0.1, 0.15, 0.2, 0.3, 
     * 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.5
     * @return True if successful, false if an invalid value was provided or if the PMIC communication failed.
     */
    bool setInputCurrentLimit(float current);

    /**
     * @brief Get the input current limit. It is a safeguard to prevent overcurrent when charging
     * respectively to the maximum current the power source can provide.
     * 
     * This function returns the current limit of the input power source.
     * 
     * @return The input current limit in amps.
     */
    float getInputCurrentLimit();

    /**
     * @brief Get the current charging status.
     * @return Charging status enum value (ChargingState).
     */
    ChargingState getState();

    /**
     * @brief Checks if the charger is enabled.
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
