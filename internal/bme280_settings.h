/**
 * Copyright (C) 2025 Carl Broman
 *
 * @file:       bem280_settings.h
 * @author:     Carl Broman <carl.broman@yh.nackademin.se>
 * @brief:  The different setting available for the BME280.
 * @note This should not be included directly - it is included through bme280.h
 * @defgroup bme280_settings BME280 Settings
 * @ingroup bme280_driver_internal
 * @{
 * @details Macros and Defines for configuring the BME280 sensor.
 */

#ifndef BME280_SETTINGS_H_
#define BME280_SETTINGS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------------*/
#include "bme280_registers.h"

/**
 * @defgroup BME280_measurement_settings Measurements Settings
 * @ingroup BME280_settings
 * @brief The settings available for Oversampling and IIR filter
 * @{
*/
    /**
     * @fn BME280_SET_STANDBY_MS(ms)
     * @brief Macro for setting the standby interval. This will decide for how long the
     * BME280 will sleep between taking measurements. (Only effective in BME280_MODE_NORMAL)
     * 
     * This macro generate a bitfield for use in writing to BME280 configuration register.
     * Use the following values:
     * - INTERVAL_0_5MS
     * - INTERVAL_62_5MS
     * - INTERVAL_125MS
     * - INTEVAL_250MS
     * - INTERVAL_500MS
     * - INTERVAL_1000MS
     * - INTERVAL_10MS
     * - INTERVAL_20MS
     * 
     * @param ms Use the enum BME280_READ_INTERVALS_MS for the pre-defined values
     * @return Bitfield for BME280_CONFIG_REGISTER
    */
    #define BME280_SET_STANDBY_MS(ms)            ((((ms) & 0x07) << 5) | BME280_CONFIG_REGISTER)

    /**
     * @fn BME280_SET_IIR_FILTER(fs)
     * @brief Macros to configure temperature, pressure, and humidity oversampling.
     *
     * This macros generate a bitfield for use in writing to BME280 control registers.
     * Use the following values for oversampling:
     *   - BME280_SET_FILTER_OFF
     *   - BME280_SET_FILTER_2
     *   - BME280_SET_FILTER_4
     *   - BME280_SET_FILTER_8
     *   - BME280_SET_FILTER_16
     *
     * @param fs Filter settings from the predefined BME280_SET_FILTER_XXX
     * @return Bitfield for BME280_CONFIG_REGISTER
     */
    #define BME280_SET_IIR_FILTER(fs)            ((((fs) & 0x07) << 2) | BME280_CONFIG_REGISTER)

    /**
     * @defgroup BME280_oversampling_macros Oversampling Macros
     * @ingroup BME280_measurement_settings
     * @brief Macros to configure temperature, pressure, and humidity oversampling.
     *
     * These macros generate bitfields for use in writing to BME280 control registers.
     * Use the following values for oversampling:
     *   - BME280_OSRS_SKIPPED
     *   - BME280_OSRS_X1
     *   - BME280_OSRS_X2
     *   - BME280_OSRS_X4
     *   - BME280_OSRS_X8
     *   - BME280_OSRS_X16
     *
     * @note All macros return a bitfield; they do not write directly to registers.
     * @{
     */

    #define BME280_SET_TEMP_OSRS(osrs_t)         ((((osrs_t) & 0x07) << 5) | BME280_CONTROL_MEASURE) /**< Macro to configure temperature oversampling. */
    #define BME280_SET_PRESS_OSRS(osrs_p)        ((((osrs_p) & 0x07) << 2) | BME280_CONTROL_MEASURE) /**< Macro to configure pressure oversampling. */
    #define BME280_SET_HUM_OSRS(osrs_h)          (((osrs_h) & 0x07) | BME280_CONTROL_HUMIDITY) /**< Macro to configure humidity oversampling. */

    /** @} */ // End of BME280_oversampling_macros

    /**
     * @defgroup BME280_osrs Oversampling Rates
     * @ingroup BME280_measurement_settings
     * @brief
     * Predefined constants for oversampling settings in the BME280 sensor.
     *
     * These values are used in macros such as:
     * - BME280_SET_TEMP_OSRS()
     * - BME280_SET_PRESS_OSRS()
     * - BME280_SET_HUM_OSRS()
     *
     * Meaning of constants:
     * - SKIPPED: no measurement
     * - X1 to X16: increasing oversampling rate and accuracy
     *
     * @{
     */
    #define BME280_OSRS_SKIPPED      0b000  /**< Skip measurement (power saving) */
    #define BME280_OSRS_X1           0b001  /**< Oversampling x1 */
    #define BME280_OSRS_X2           0b010  /**< Oversampling x2 */
    #define BME280_OSRS_X4           0b011  /**< Oversampling x4 */
    #define BME280_OSRS_X8           0b100  /**< Oversampling x8 */
    #define BME280_OSRS_X16          0b101  /**< Oversampling x16 */

    /** @} */ // End of BME280_osrs


    /**
     * @defgroup BME280_iir IIR Settings
     * @ingroup BME280_measurement_settings
     * @brief
     * Predefined constants for IIR settings in the BME280 sensor.
     * 
     * These values are used in the macro:
     * - BME280_SET_IIR_FILTER()
     * 
     * Meaning of constants:
     * - OFF: No filter (Very sensitivte)
     * - X1 to X16: increasing stability
     * @{
    */
    #define BME280_SET_FILTER_OFF    0b000 /**< Filter off, very sensitive to changes */
    #define BME280_SET_FILTER_2      0b001 /**< Filter 2 */
    #define BME280_SET_FILTER_4      0b010 /**< Filter 4 */
    #define BME280_SET_FILTER_8      0b011 /**< Filter 8 */
    #define BME280_SET_FILTER_16     0b100 /**< Filter 16 */

    /**@}*/ // END OF BME280_iir

/**@} */ // END OF BME280_measurement_settings

/**
 * @defgroup BME280_reading_modes Reading Modes
 * @ingroup BME280_settings
 * @brief The different reading modes for the BME280. Coupled together with SET_MODE
 * @{
*/
    /**
     * @fn BME280_SET_MODE(mode)
     * @brief Macro for setting the mode on the BME280
     * 
     * This macro generate a bitfield for use in writing to the BME280 Control Measure Setting.
     * Use the following values for setting the mode:
     * - BME280_MODE_NORMAL
     * - BME280_MODE_SLEEP
     * - BME280_MODE_FORCED
     * 
     * @param mode Use the Defined BME280_MODE_XXX to assign the correct values.
     * @return Bitfield to be written into register.
     */
    #define BME280_SET_MODE(mode)                (((mode) & 0x03) | BME280_CONTROL_MEASURE)

    #define BME280_MODE_NORMAL                   0b11    /**< Perpetual cycling of measurements and inactive periods. */
    #define BME280_MODE_SLEEP                    0b00    /**< No operation, all registers accessible, lowest power, selected after startup */
    #define BME280_MODE_FORCED                   0b01    /**< Perform one measurement, store results and return to sleep mode */

/**}@ */ // End of BME280_reading_modes
#ifdef __cplusplus
}
#endif
/**@} */ // End of bme280_settings 
#endif  // BME280_SETTINGS_H_
