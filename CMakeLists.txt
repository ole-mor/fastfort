cmake_minimum_required(VERSION 3.10)
project(fastfort C)

# Set C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --- NVM Backend ---
set(NVM_BACKEND "SIM" CACHE STRING "NVM backend: SIM, FILE, NVS, LITTLEFS, EEPROM, STM32")

if(NVM_BACKEND STREQUAL "NVS")
    set(NVM_SOURCE domain/edge/mcu/peripherals/nvm/nvm_nvs.c)
elseif(NVM_BACKEND STREQUAL "FILE")
    set(NVM_SOURCE domain/edge/mcu/peripherals/nvm/nvm_file.c)
elseif(NVM_BACKEND STREQUAL "LITTLEFS")
    set(NVM_SOURCE domain/edge/mcu/peripherals/nvm/nvm_littlefs.c)
elseif(NVM_BACKEND STREQUAL "EEPROM")
    set(NVM_SOURCE domain/edge/mcu/peripherals/nvm/nvm_eeprom.c)
elseif(NVM_BACKEND STREQUAL "STM32")
    set(NVM_SOURCE domain/edge/mcu/peripherals/nvm/nvm_stm32.c)
else()
    set(NVM_SOURCE domain/edge/mcu/peripherals/nvm/nvm_sim.c)
endif()

# --- MCU Target ---
set(MCU_TARGET "SIM" CACHE STRING "MCU target: SIM, STM32, ESP32")

# --- Bus Backend ---
if(MCU_TARGET STREQUAL "STM32")
    set(I2C_SOURCE domain/edge/mcu/protocols/bus/i2c/i2c_stm32.c)
    set(SPI_SOURCE domain/edge/mcu/protocols/bus/spi/spi_stm32.c)
    set(UART_SOURCE domain/edge/mcu/protocols/bus/uart/uart_stm32.c)
    set(CAN_SOURCE domain/edge/mcu/protocols/bus/can/can_stm32.c)
elseif(MCU_TARGET STREQUAL "ESP32")
    set(I2C_SOURCE domain/edge/mcu/protocols/bus/i2c/i2c_esp32.c)
    set(SPI_SOURCE domain/edge/mcu/protocols/bus/spi/spi_esp32.c)
    set(UART_SOURCE domain/edge/mcu/protocols/bus/uart/uart_esp32.c)
    set(CAN_SOURCE domain/edge/mcu/protocols/bus/can/can_esp32.c)
else()
    set(I2C_SOURCE domain/edge/mcu/protocols/bus/i2c/i2c_sim.c)
    set(SPI_SOURCE domain/edge/mcu/protocols/bus/spi/spi_sim.c)
    set(UART_SOURCE domain/edge/mcu/protocols/bus/uart/uart_sim.c)
    set(CAN_SOURCE domain/edge/mcu/protocols/bus/can/can_sim.c)
endif()

# --- Sources ---
set(SOURCES
    cmd/main.c
    lib/mo/mo.c
    lib/mm/mm.c
    lib/bsp/bsp.c
    lib/bds/bds.c
    lib/bmu/bmu.c
    lib/bfi/bfi.c
    domain/edge/mcu/peripherals/tmp/tmp.c
    ${NVM_SOURCE}
    ${I2C_SOURCE}
    ${SPI_SOURCE}
    ${UART_SOURCE}
    ${CAN_SOURCE}
)

# Include directories (project root for relative includes)
set(INCLUDE_DIRS
    .
)

# Define the executable
add_executable(fastfort ${SOURCES})

# --- Configure Target ---
target_include_directories(fastfort PUBLIC ${INCLUDE_DIRS})

# Add compiler warnings
if(MSVC)
    target_compile_options(fastfort PRIVATE /W4)
else()
    target_compile_options(fastfort PRIVATE -Wall -Wextra -Wpedantic)
endif()
