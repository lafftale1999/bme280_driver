/**
 * Copyright (C) 2025 Carl Broman
 *
 * @file        bme280.h
 * @author      Carl Broman <carl.broman@yh.nackademin.se>
 * @brief       Complete driver for the BME280 sensor: temperature, pressure, and humidity.
 * @addtogroup  bme280_driver BME280 Driver
 * @{
 *
 * @details
 * This is a complete driver for the BME280 sensor using I2C communication.
 * It includes JSON support to export measurement data in a structured format.
 *
 * Example usage:
 * @code
 *   #include "bme280.h"
 * 
 *   bme280_init(bme280_handle_t *handle, 0x76, INTERVAL_1000MS);
 *   bme280_read_data(*handle);
 *   http_post(bme280_get_json(*handle));
 * @endcode
 */

 /**
  * @defgroup bme280_headerfile BME280 Headerfile
  * @ingroup bme280_driver
  * @brief Headerfile for the BME280 driver.
  * @{
  */
#ifndef BME280_DRIVER_H_
#define BME280_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "pico/stdio.h"
#include "pico/stdlib.h"

/* -------------------------- DEFINES -------------------------------------------*/

/**
 * @defgroup bme280_config Configurations
 * @ingroup bme280_driver
 * @brief Defines that can be changed depending on usage.
 * @{
 */
#define BME280_UNITS_ON_BUS          1       /**< Number of BME280 units connected */
#define BME280_ADDRESSES_ON_BUS      {0x76}  /**< I2C addresses of connected BME280 units */
#define BME280_ADDRESS_LENGTH        7       /**< BME280 I2C address length (7-bit) */
/** @} */

/* -------------------------- MACROS -------------------------------------------*/
/**
 * @defgroup bme280_debug Debug Macro
 * @ingroup bme280_driver
 * @brief Macros for logging messages
 * @{
 */
#define BME280_DEBUG 0
#if BME280_DEBUG
#define BME280_LOG(...) printf(__VA_ARGS__)
#else
#define BME280_LOG(...)
#endif
/**@} */

/* -------------------------- TYPEDEFS -------------------------------------------*/

/**
 * @defgroup bme280_typedefs Typedefinitions
 * @ingroup bme280_driver
 * @brief External handle and predefined interval settings.
 * @{
 */

typedef struct bme280_handle_internal *bme280_handle_t; /**< Opaque handle to a BME280 instance */

typedef enum {
    INTERVAL_0_5MS      = 0b000,
    INTERVAL_62_5MS     = 0b001,
    INTERVAL_125MS      = 0b010,
    INTERVAL_250MS      = 0b011,
    INTERVAL_500MS      = 0b100,
    INTERVAL_1000MS     = 0b101,
    INTERVAL_10MS       = 0b110,
    INTERVAL_20MS       = 0b111
} BME280_READING_INTERVALS_MS; /**< Predefined standby intervals used in BME280 configuration */
/** @} */

/* -------------------------- FUNCTIONS -------------------------------------------*/

/**
 * @defgroup bme280_functions Functions
 * @ingroup bme280_driver
 * @brief Public functions provided by the BME280 driver.
 * @{
 */

/**
 * @brief Initialize the BME280 sensor.
 * @param handle Pointer to store the handle.
 * @param device_address I2C address.
 * @param interval Measurement standby interval.
 * @return PICO_W_OK if successful, otherwise PICO_W_FAIL.
 */
int bme280_init(bme280_handle_t *handle, const uint8_t device_address, const BME280_READING_INTERVALS_MS interval);

/**
 * @brief Read temperature, pressure, and humidity from the BME280.
 * @param handle Handle to the BME280 instance.
 * @return PICO_W_OK if successful, otherwise PICO_W_FAIL.
 */
int bme280_read_data(const bme280_handle_t handle);

/**
 * @brief Get latest measurement as a JSON string.
 * @param handle Handle to the BME280 instance.
 * @return Pointer to JSON string, or NULL if not available.
 */
const char* bme280_get_json(const bme280_handle_t handle);

/** @} */ // End of bme280_functions

/**@} */
#ifdef __cplusplus
}
#endif

#endif  // BME280_DRIVER_H_
/** @} */ // End of bme280_driver
