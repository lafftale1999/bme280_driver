/**
 * Copyright (C) 2025 Carl Broman
 *
 * @file:       bme280_i2c.h
 * @author:     Carl Broman <carl.broman@yh.nackademin.se>
 * @brief:  I2C api for the bme280 driver.
 * @note This should not be included directly - it is included through bme280.h
 * @defgroup bme280_i2c BME280 I2C
 * @ingroup bme280_driver_internal
 * @{
 * @details The I2C api used for the BME280.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BME280_I2C_H_
#define BME280_I2C_H_

#include "hardware/i2c.h"
#include "hardware/gpio.h"

#include <stdint.h>

/**
 * @defgroup bme280_i2c_config I2C Configurations
 * @ingroup bme280_driver_internal
 * @brief Defines for configuring the i2c setup
 * @{
 */
#define I2C_SDA_PIN                 14              /**< SDA pin */
#define I2C_SCL_PIN                 15              /**< SCL pin */
#define I2C_PORT                    i2c1            /**< Which internal i2c module is used. Often i2c0 or i2c1 */
#define I2C_FREQUENCY               100000          /**< Frequency for communication */
/** @} */

/**
 * @brief Initializes the i2c communication.
 * 
 * @return 0 for success.
 */
uint8_t i2c_open();

/**
 * @brief Writes data on the initialized databus.
 * 
 * @param[in] device_address address for targeted device on the i2c bus.
 * @param[in] data pointer to array of bytes
 * @param[in] len length of array
 * @param[in] keepMaster true = keeps the master over bus | false = lets go of control over bus after transmitting data
 * 
 * @return 0 for success. 1 for fail.
 */
uint8_t i2c_write_data(const uint8_t *device_address, uint8_t *data, const size_t len, bool keepMaster);

/**
 * @brief Reads data from assigned address and increments the register address by 1 for _len long.
 * 
 * @param[in] device_address address for targeted device on the i2c bus.
 * @param[in] d_register pointer to variable containing the register address
 * @param[in] buf pointer to the byte array to write data to
 * @param[in] len the size of buf
 * 
 * @return 0 for success. 1 for fail.
 */
uint8_t i2c_read_data(const uint8_t *device_address, const uint8_t *d_register, uint8_t *buf, const size_t len);

#ifdef __cplusplus
}
#endif
/**@} */ // End of bme280_i2c 
#endif  // BME280_I2C_H_