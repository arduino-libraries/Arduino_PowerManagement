#include <Arduino_PMIC.h>
#include "wireUtils.h"

typedef VFastCharge ChargeVoltage;
typedef IFastCharge ChargeCurrent;
typedef IEndOfCharge EndOfChargeCurrent;
typedef IInputCurrentLimit MaxInputCurrent;


// TODO: Explain these enums.
// TODO: Avoid abbreviations in enum names.
// TODO: Avoid all caps in enum names. Use CamelCase instead.
// TODO: Use enum class instead of enum.
/**
 * Enum representing different charging statuses.
 */
enum ChargeStatus {
    NONE = -1,
    PRECHARGE = 0,
    FAST_CHARGE_CC = 1,
    FAST_CHARGE_CV = 2,
    END_OF_CHARGE = 3,
    DONE = 4,
    TIMER_FAULT = 6,
    THERMISTOR_SUSPEND = 7,
    OFF = 8,
    BATTERY_OVERVOLTAGE = 9,
    LINEAR_ONLY = 12
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

    // TODO: Explain what is the input current. Input to the charger? Input to the battery? both?
    // Why is this setting useful?
    /**
     * @brief Set the maximum input current.
     * @param current Maximum input current enum value (MaxInputCurrent).
     */
    void setMaxInputCurrent(MaxInputCurrent current);

    /**
     * @brief Get the current charging status.
     * @return Charging status enum value (ChargeStatus).
     */
    ChargeStatus getChargeStatus();

    // TODO: Enables charging or just enables the charger?
    // TODO: Explain charging behaviour, what's the default charging current, etc.
    /**
     * @brief Enable the charger.
     * @return True if successful, false otherwise.
     */
    bool enable();

    // TODO: Enables charging or just enables the charger?
    /**
     * @brief Disable the charger.
     * @return True if successful, false otherwise.
     */
    bool disable();

private:
    PF1550* pmic; /**< Pointer to the PF1550 PMIC instance. */
};
