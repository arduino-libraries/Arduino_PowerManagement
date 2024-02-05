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
 * @see #ChargerBypassMode
 */

enum class ChargeStatus {
    /**
     * Provided by the registers, not used. 
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
    ChargerBypassMode = 12
};

/**
 * @brief Charger class for controlling charging parameters and monitoring charging status.
 */
class Charger {
public:
    /**
     * @brief Default constructor.
     */
    Charger();

    /**
     * @brief Constructor with PMIC instance.
     * @param pmic Pointer to the PF1550 PMIC instance.
     */
    Charger(PF1550* pmic);

    /**
     * @brief Set the charging current.
     * @param current Charging current enum value (ChargeCurrent).
     */
    void setChargeCurrent(ChargeCurrent current);

    /**
     * @brief Set the charging voltage.
     * @param voltage Charging voltage enum value (ChargeVoltage).
     */
    void setChargeVoltage(ChargeVoltage voltage);

    /**
     * @brief Set the end-of-charge current.
     * @param current End-of-charge current enum value (EndOfChargeCurrent).
     */
    void setEndOfChargeCurrent(EndOfChargeCurrent current);

    /**
     * @brief The input current limit (ILIM) safeguards the device by preventing overcurrent, ensuring the charging current is within safe levels for the battery, and adapting to the maximum current the power source can provide, allowing you to charge and use the system at the same time. 
     * @param current Maximum input current enum value (InputCurrentLimit).
     */
    void setInputCurrentLimit(InputCurrentLimit current);

    /**
     * @brief Get the current charging status.
     * @return Charging status enum value (ChargeStatus).
     */
    ChargeStatus getChargeStatus();

    /**
     * @brief Enables the charging functionality with either the default settings or the last saved parameters, depending on what was set previously. 
     * @return True if successful, false otherwise.
     */
    bool enable();


    /**
     * @brief Disable the charging functionality.
     * @return True if successful, false otherwise.
     */
    bool disable();

private:
    PF1550* pmic; /**< Pointer to the PF1550 PMIC instance. */
};
