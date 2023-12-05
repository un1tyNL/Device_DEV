/*************************************************************************\
 * Documentation
\*************************************************************************/
/**
 * @file     global.hpp
 * @brief
 * @details
 * @version  0.1
 */
#pragma once
/*************************************************************************\
* Includes
\*************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief uint8_t array pointer, type defined as it very common for type for communication through peripherals on embedded platforms (UART,
 * SPI, I2C etc.).
 */
typedef uint8_t (*uint8_array_t)[];
/*************************************************************************\
 * End of file
\*************************************************************************/
