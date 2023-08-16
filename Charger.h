#include <Arduino_PMIC.h>
#include "wireUtils.h"

typedef VFastCharge ChargeVoltage;
typedef IFastCharge ChargeCurrent;
typedef IEndOfCharge EndOfChargeCurrent;
typedef IInputCurrentLimit MaxInputCurrent;

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
     * @param _pPMIC Pointer to the PF1550 PMIC instance.
     */
    Charger(PF1550* _pPMIC);

    /**
     * @brief Set the charging current.
     * @param i Charging current enum value (ChargeCurrent).
     */
    void setChargeCurrent(ChargeCurrent i);

    /**
     * @brief Set the charging voltage.
     * @param v Charging voltage enum value (ChargeVoltage).
     */
    void setChargeVoltage(ChargeVoltage v);

    /**
     * @brief Set the end-of-charge current.
     * @param i End-of-charge current enum value (EndOfChargeCurrent).
     */
    void setEndOfChargeCurrent(EndOfChargeCurrent i);

    /**
     * @brief Set the maximum input current.
     * @param i Maximum input current enum value (MaxInputCurrent).
     */
    void setMaxInputCurrent(MaxInputCurrent i);

    /**
     * @brief Get the current charging status.
     * @return Charging status enum value (ChargeStatus).
     */
    ChargeStatus getChargeStatus();

    /**
     * @brief Enable the charger.
     * @return True if successful, false otherwise.
     */
    bool enableCharger();

    /**
     * @brief Disable the charger.
     * @return True if successful, false otherwise.
     */
    bool disableCharger();

private:
    PF1550* pPMIC; /**< Pointer to the PF1550 PMIC instance. */
};
