#ifndef BATTERY_CONSTANTS_H

// SEE: https://www.analog.com/media/en/technical-documentation/data-sheets/MAX17262.pdf

// Initial Values (for resetting registers)
#define MAXMIN_VOLT_INITIAL_VALUE 0x00FF

// Conversion factors (See section "ModelGauge m5 Register Standard Resolutions" in the datasheet)
#define VOLTAGE_MULTIPLIER_MV (1.25 / 16) // Resolution: 78.125 μV per LSB
#define CURRENT_MULTIPLIER_MA 0.15625 // Resolution: 0.15625 mA per LSB for MAX17262R
#define CAPACITY_MULTIPLIER_MAH 0.5 // Resolution: 0.5mAh per LSB for MAX17262R
#define PERCENTAGE_MULTIPLIER (1.0 / 256) // Resolution: 1/256% per LSB
#define TIME_MULTIPLIER_S 5.625 // Resolution: 5.625 seconds per LSB
#define TEMPERATURE_MULTIPLIER_C (1.0 / 256) // Resolution: 1/256°C per LSB
#define EMPTY_VOLTAGE_MULTIPLIER_MV 10 // Resolution: 10mV per LSB
#define RECOVERY_VOLTAGE_MULTIPLIER_MV 40 // Resolution: 40mV per LSB
#define MAXMIN_VOLT_MULTIPLIER_MV 20 // Resolution: 20mV per LSB

// Voltage Registers
#define VCELL_REG 0x09 // VCell reports the voltage measured between BATT and GND.
#define AVG_VCELL_REG 0x19 // The AvgVCell register reports an average of the VCell register readings.
#define VRIPPLE_REG 0xBC
#define MAXMIN_VOLT_REG 0x1B // The MaxMinVolt register maintains the maximum and minimum of VCell register values since device reset.

// Temperature Registers
#define TEMP_REG 0x08 // The Temp register provides the temperature measured by the thermistor or die temperature based on the Config register setting.
#define AVG_TA_REG 0x16 // The AvgTA register reports an average of the readings from the Temp register.
#define AIN_REG 0x027
#define T_GAIN_REG 0x2C
#define T_OFF_REG 0x02D
#define DIE_TEMP_REG 0x34

// Capacity Registers
#define REP_CAP_REG 0x05 // RepCap or reported remaining capacity in mAh. 
#define Q_RESIDUAL_REG 0x0C
#define MIX_CAP_REG 0x0Fs
#define FULL_CAP_REP_REG 0x10 // This register reports the full capacity that goes with RepCap, generally used for reporting to the GUI.
#define DESIGN_CAP_REG 0x18 // The DesignCap register holds the expected capacity of the cell.
#define AV_CAP_REG 0x1F
#define FULL_CAP_NOM_REG 0x23
#define DQ_ACC_REG 0x45
#define VFR_REM_CAP_REG 0x4A
#define QH_REG 0x4D
#define AT_QRESIDUAL_REG 0xDC
#define AT_AV_CAP_REG 0xDF

// current/timers
#define AT_RATE_REG 0x04
#define CURRENT_REG 0x0A // The MAX17262 uses internal current sensing to monitor the current through the SYS pin. The measurement value is stored in two's-complement format.
#define AVG_CURRENT_REG 0x0B // The AvgCurrent register reports an average of Current register readings.
#define TTE_REG 0x11
#define TTF_REG 0x20
#define TIMER_REG 0x3E
#define TIMER_H_REG 0xBE
#define AT_TTE_REG 0xDD

// percentages
#define REP_SOC_REG 0x06 // the reported state-of-charge percentage output for use by the application GUI.
#define AGE_REG 0x07
#define MIX_SOC_REG 0x0D
#define AV_SOC_REG 0x0E
#define DP_ACC_REG 0x46
#define AT_AV_SOC_REG 0xDE

// Model Registers
#define QR_TABLE_00_REG 0x12
#define FULL_SOC_THR_REG 0x13
#define CONFIG_REG 0x1D // The Config registers hold all shutdown enable, alert enable, and temperature enable control bits. Writing a bit location enables the corresponding function within one task period. (One task period is 175ms in active mode, and 5.6 seconds in hibernate mode by default.) 
#define I_CHG_TERM_REG 0x1E // The IChgTerm register allows the device to detect when a charge cycle of the cell has completed.
#define QR_TABLE_10_REG 0x22
#define LEARN_CFG_REG 0x28
#define FILTER_CFG_REG 0x29
#define RELAX_CFG_REG 0x2A
#define MISC_CFG_REG 0x2B
#define QR_TABLE_20_REG 0x32
#define FULL_CAP_REG 0x35
#define R_COMP_0_REG 0x38
#define TEMP_CO_REG 0x39
#define V_EMPTY_REG 0x3A
#define QR_TABLE_30_REG 0x42

// Status Registers
#define STATUS_REG 0x00
#define STATUS2_REG 0xB0 // The Status2 register maintains status of various firmware functions.
#define F_STAT_REG 0x3D // The FStat register is a read-only register that monitors the status of the ModelGauge m5 algorithm.
#define HIB_CFG_REG 0xBA // The HibCfg register controls hibernate mode functionality. The MAX1726x enters and exits hibernate when the battery current is less than approximately C/100.
#define SHDN_TIMER 0x3F
#define SOFT_WAKEUP_REG 0x60 // The Command register accepts commands to perform functions to wake up the IC for configuration changes.
#define MODEL_CFG_REG 0xDB
#define CYCLES_REG 0x17
#define DEV_NAME_REG 0x21
#define POWER_REG 0xB1
#define AVG_POWER_REG 0xB3

// POR (Power-On Reset): This bit is set to 1 when the device detects that 
// a software or hardware POR event has occurred. This bit must be cleared 
// by system software to detect the next POR event. POR is set to 1 at power-up.
#define POR_BIT 1
#define DNR_BIT 0 // Data Not Ready. This bit is set to 1 at cell insertion and remains set until the output registers have been updated. Afterward, the IC clears this bit, indicating the fuel gauge calculations are up to date. This takes 710ms from power-up
#define E_DET_BIT 8 // FStat Register: Empty Detection. This bit is set to 1 when the IC detects that the cell empty point has been reached. This bit is reset to 0 when the cell voltage rises above the recovery threshold.
#define FULL_DET_BIT 5 // Status2 Register: Full Detection. This bit is set to 1 when the IC detects that the cell full point has been reached.
#define EN_HIBERNATION_BIT 15
#define HIB_BIT 1 // Hibernate Status. This bit is set to a 1 when the device is in hibernate mode or 0 when the device is in active mode. Hib is set to 0 at power-up.
#define R100_BIT 13 // The R100 bit needs to be set when using a 100k NTC resistor
#define MODEL_CFG_REFRESH_BIT 15 // Model Configuration Refresh. This bit is set to 1 to refresh the ModelGauge m5 algorithm configuration. This bit is automatically cleared to 0 after the refresh is complete.
#define BATTERY_STATUS_BIT 3 //  Useful when the IC is used in a host-side application. This bit is set to 0 when a battery is present in the system, and set to 1 when the battery is absent. Bst is set to 0 at power-up.
#define TSEL_BIT 15 // Temperature sensor select. Set to 0 to use internal die temperature. Set to 1 to use temperature information from thermistor. ETHRM bit must be set to 1 when TSel is 1.
#define ETHRM_BIT 4 // Enable Thermistor. Set to logic 1 to enable the TH pin measurement.
#define TEN_BIT 9 // Enable Temperature Channel. Set to 1 and set ETHRM or FTHRM to 1 to enable temperature measurement.

#endif