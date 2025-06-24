cmake_minimum_required(VERSION 3.13)

# === Ditt drivrutinsbibliotek ===
add_library(bme280 STATIC
    bme280.c
    internal/bme280_internal.c
)

# Inkludera headers
target_include_directories(bme280
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/internal
)

# Länka mot Pico SDK-funktioner
target_link_libraries(bme280
    pico_stdlib
    hardware_i2c
)