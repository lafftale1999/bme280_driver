/**
 * Copyright (C) 2025 Carl Broman
 *
 * @file:       bme280.c
 * @author:     Carl Broman <carl.broman@yh.nackademin.se>
 * @brief:      Source code for the external implementation of the BME280 driver.
 * @addtogroup  bme280_driver BME280 Driver
 * @{
 -------------------------------------------------------------------------------------------------*/

#include "internal/bme280_internal.h"
#include "internal/bme280_i2c.h"
#include <string.h>

/**
 * @defgroup BME280_driver_fn_impl External Functions Implementation
 * @ingroup bme280_driver
 * @brief External functions for the BME280 drivers
 * @{
 */

/**
 * @brief Read sensor data from BME280 and convert to human-readable values.
 * 
 * This function reads raw temperature, pressure, and humidity values from the sensor
 * and then converts them using Bosch's official compensation formulas. Then parses these values into JSON format.
 *
 * @param handle BME280 device handle.
 * @return 0 on success, 1 on error (e.g., I2C read or conversion failure).
 */
int bme280_read_data(const bme280_handle_t handle)
{

    uint8_t buf[BME280_READ_VALUES_REG_LEN];
    uint8_t register_start = BME280_READ_VALUES_REG_START;

    if(i2c_read_data(&handle->i2c_address, &register_start, buf, BME280_READ_VALUES_REG_LEN) != 0) {
        BME280_LOG("Unable to read data from registers.\n");
        return 1;
    }
    handle->press_raw = (buf[0] << 12) | (buf[1] << 4) | (buf[2] >> 4); 
    handle->temp_raw = (buf[3] << 12) | (buf[4] << 4) | (buf[5] >> 4);
    handle->hum_raw = (buf[6] << 8) | buf[7];

    if(bme280_convert_measurements(handle) != 0) {
        BME280_LOG("Unable to convert values.\n");
        return 1;
    }

    bme280_parse_json(handle);

    BME280_LOG("Temp: %0.1fC | Humidity: %0.1f%% | Pressure: %0.1fhPa\n", (float)handle->temperature / 100.0f, (float)handle->humidity / 1024.0f, ((float)handle->pressure / 256.0f) / 100.0f);
 
    return 0;
}

/**
 * @brief Initialize BME280 sensor and allocate internal handle.
 *
 * This function sets up the standard configuration for indoor use and reads
 * the calibration data from the sensor.
 *
 * @param[out] handle Pointer to driver handle (will be malloc'd internally).
 * @param[in] device_address I2C address of the sensor.
 * @param[in] interval Desired measurement interval / standby time.
 * @return PICO_W_OK on success, PICO_W_FAIL on error.
 */
int bme280_init(bme280_handle_t *handle, const uint8_t device_address, const BME280_READING_INTERVALS_MS interval)
{
    i2c_open();
    
    bme280_handle_t p_handle = malloc(sizeof(struct bme280_handle_internal));

    if (p_handle == NULL) {
        BME280_LOG("Unable to allocate handle on heap\n");
        goto exit;
    }

    p_handle->i2c_address = device_address;
    p_handle->address_length = BME280_ADDRESS_LENGTH;
    
    if (bme280_calibration(p_handle) != 0) {
        goto exit;
    }

    uint8_t humidity_set_up[2] = {
        BME280_CONTROL_HUMIDITY,
        BME280_SET_HUM_OSRS(BME280_OSRS_X1)
    };
    
    uint8_t measurement_set_up[3] = {
        BME280_CONTROL_MEASURE, 
        BME280_SET_TEMP_OSRS(BME280_OSRS_X2) | BME280_SET_PRESS_OSRS(BME280_OSRS_X16) | BME280_MODE_NORMAL
    };

    uint8_t config_set_up[2] = {
        BME280_CONFIG_REGISTER,
        BME280_SET_STANDBY_MS(interval) | BME280_SET_IIR_FILTER(BME280_SET_FILTER_16)
    };

    // Making sure that all configurations are set up correctly
    if (i2c_write_data(&p_handle->i2c_address, humidity_set_up, 2, true) != 0 ||
        i2c_write_data(&p_handle->i2c_address, config_set_up, 2, true) != 0 ||
        i2c_write_data(&p_handle->i2c_address, measurement_set_up, 2, false) != 0){
        BME280_LOG("Unable to correctly set up configurations on bme280.\n");
        goto exit;
    }

    *handle = p_handle;

    BME280_LOG("BME280 successfully intitialize.\n");
    return 0;

exit:
    BME280_LOG("Initialization of bme280 failed\n");

    if (p_handle != NULL) {
        free(p_handle);
    }

    return 1;
}

/**
 * @brief Get the latest sensor data as a JSON string.
 *
 * Returns a pointer to a statically stored JSON buffer. Returns NULL if no valid
 * data has been parsed yet.
 *
 * @param[in] handle BME280 device handle.
 * @return Pointer to JSON string, or NULL if `bme280_read_data` has not been called.
 */
const char* bme280_get_json(const bme280_handle_t handle)
{
    if (handle->json_parsed){
        return handle->json_string;
    }
    else {
        return NULL;
    }
}

/**
 * @brief Free memory allocated for BME280 driver handle.
 *
 * Should be called when the driver is no longer needed to avoid memory leaks.
 *
 * @param[in] handle BME280 device handle to be freed.
 */
void bme280_free(bme280_handle_t handle)
{
    if (handle) {
        free(handle);
    }
}
/**@} */ // end of BME280_driver_fn_impl

/**@} */ // end of bme280_driver_source_code