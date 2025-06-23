/**
 * Copyright (C) 2025 Carl Broman
 *
 * @file:       bme280_json.h
 * @author:     Carl Broman <carl.broman@yh.nackademin.se
 * @brief:  Json headerfile for correctly parsing bme280 values
 * @note This should not be included directly - it is included through bme280.h
 * @defgroup bme280_json BME280_JSON
 * @ingroup bme280_driver_internal
 * @{
 * @brief Headerfile for defines regarding parsing BME280 values into JSON strings.
 * @details Headerfile for defines regarding parsing BME280 values into JSON strings.
 -------------------------------------------------------------------------------------------------*/

#ifndef BME280_JSON_H_
#define BME280_JSON_H_

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @defgroup BME280_json_defines BME280 JSON defines
 * @brief Definitions for parsing the BME280 values to a JSON string
 * @{
*/
#define BME280_JSON_TEMP_KEY                 "temperature"
#define BME280_JSON_PRESS_KEY                "pressure"
#define BME280_JSON_HUM_KEY                  "humidity"
#define BME280_JSON_KEYS                     {BME280_JSON_TEMP_KEY, BME280_JSON_HUM_KEY, BME280_JSON_PRESS_KEY}
#define BME280_JSON_KEYS_LEN                 20
#define BME280_JSON_KEYS_SIZE                3
#define BME280_JSON_VALS_LEN                 10
#define BME280_JSON_STR_MAX_LEN              ((BME280_JSON_KEYS_LEN + BME280_JSON_VALS_LEN + 5) * BME280_JSON_KEYS_SIZE)
#define BME280_JSON_BUF_SIZE                 64
/** @} BME280_json_defines */

#ifdef __cplusplus
}
#endif

#endif  // BME280_JSON_H_
/** @} BME280_JSON */
