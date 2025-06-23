/**
 * Copyright (C) 2025 Carl Broman
 *
 * @file        bme280_registers.h
 * @author      Carl Broman <carl.broman@yh.nackademin.se>
 * @brief       Register map for the BME280 sensor.
 * @note This should not be included directly - it is included through bme280.h
 * @defgroup  bme280_registers BME280 Register Map
 * @ingroup bme280_settings
 * @{
 */

#ifndef BME280_REGISTERS_H_
#define BME280_REGISTERS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup BME280_registers_ID_and_reset ID and Reset
 * @ingroup bme280_registers
 * @brief Registers used for identification and reset.
 * @{
 */
#define BME280_ID_REG                    0xD0  /**< Chip ID register (expected value: 0x60) */
#define BME280_RESET_REGISTER            0xE0  /**< Reset register */
#define BME280_WRITE_RESET_BITS          0xB6  /**< Command to trigger a software reset */
/** @} */

/**
 * @defgroup BME280_registers_configurations Configuration Registers
 * @ingroup bme280_registers
 * @brief Registers used for configuring the reading mode, oversampling rates and IIR.
 * @{
 */
    /**
     * @brief Humidity control register.
     * @details Controls humidity oversampling rate
     */
    #define BME280_CONTROL_HUMIDITY          0xF2

    /**
     * @brief Temperature, pressure control and mode setting register.
     * @details 
     * - Temperature: bits [5:7]  
     * - Pressure: bits [2:4]  
     * - Mode: bits [0:1]
     */
    #define BME280_CONTROL_MEASURE           0xF4

    /**
     * @brief Configuration register used for standby interval and IIR filter.
     * @details 
     * - Standby interval: bits [5:7]  
     * - IIR filter: bits [2:4]
     */
    #define BME280_CONFIG_REGISTER           0xF5
 /**@} */

/**
 * @defgroup BME280_read_data_registers Read Data Registers
 * @ingroup bme280_registers
 * @brief Registers for reading raw sensor measurement values. The data-registers are place sequentially in memory.
 * @{
 */

#define BME280_PRESS_REG_MSB             0xF7
#define BME280_PRESS_REG_LSB             0xF8
#define BME280_PRESS_REG_XLSB            0xF9

#define BME280_TEMP_REG_MSB              0xFA
#define BME280_TEMP_REG_LSB              0xFB
#define BME280_TEMP_REG_XLSB             0xFC

#define BME280_HUMIDITY_REG_MSB          0xFD
#define BME280_HUMIDITY_REG_LSB          0xFE

#define BME280_READ_VALUES_REG_START     0xF7  /**< Starting address for bulk read */
#define BME280_READ_VALUES_REG_LEN       8     /**< Number of bytes to read all values */
/** @} */

/**
 * @defgroup BME280_calibration_registers Calibration Registers
 * @ingroup bme280_registers
 * @brief Registers holding factory calibration values.
 * @details 
 * Calibration registers are sequentially stored and grouped by measurement type.
 * @{
 */
#define BME280_TEMP_CALIB_PARAM_START    0x88
#define BME280_TEMP_PARAMS_LEN           6

#define BME280_PRESS_CALIB_PARAM_START   0x8E
#define BME280_PRESS_PARAMS_LEN          18

#define BME280_HUM_CALIB_FIRST           0xA1
#define BME280_HUM_CALIB_FIRST_LEN       1

#define BME280_HUM_CALIB_CONTINUE        0xE1
#define BME280_HUM_CALIB_CONTINUE_LEN    8

#define BME280_AMOUNT_CALIB_PARAMS \
    (BME280_TEMP_PARAMS_LEN + BME280_PRESS_PARAMS_LEN + \
     BME280_HUM_CALIB_FIRST_LEN + BME280_HUM_CALIB_CONTINUE_LEN)
/** @} */

#ifdef __cplusplus
}
#endif

#endif  // BME280_REGISTERS_H_
/** @} */  // End of bme280_registers