#include "bme280.h"
#include "pico/stdlib.h"

#include <stdio.h>

int main(void) {
    stdio_init_all();

    bme280_handle_t handle = NULL;
    if(bme280_init(&handle, 0x76, INTERVAL_1000MS) == 0) {
        BME280_LOG("BME280 handle succesfully initiated!\n");
    }

    time

    while(1) {
        bme280_read_data(handle);
        printf("%s\n", bme280_get_json(handle));

        sleep_ms(5000);
    }

    return 0;
}