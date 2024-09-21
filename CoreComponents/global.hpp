/*************************************************************************\
 * Documentation
\*************************************************************************/
/**
 * @file     global.hpp
 * @version  0.1
 * @brief    Global definitions and base class declaration.
 * @details  This file provides shared type definitions, includes, and the 
 *           `baseClass` that serves as a foundation for all other classes 
 *           in the project. It should be included in every header file to 
 *           ensure access to common definitions and the base class.
 * @note     This file contains globally shared typedefinitions, includes, 
 *           and the declaration of the `baseClass`. All classes should derive 
 *           from `baseClass` and override its methods as needed.
 */
#pragma once
/*************************************************************************\
* Includes
\*************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*************************************************************************\
* Definitions
\*************************************************************************/
/**
 * @brief  uint8_t array pointer, type defined as it very common for type for communication through peripherals on embedded platforms (UART,
 *         SPI, I2C etc.).
 */
typedef uint8_t (*uint8_array_t)[];

/*************************************************************************\
 * Prototypes
\*************************************************************************/
/**
 * @brief    baseClass that serves as a minimal foundation for derived classes.
 * @details  This class provides a common interface for initialization and 
 *           processing operations, allowing derived classes to override 
 *           these methods to implement specific logic.
 */
class baseClass {
public:
    /**
     * @brief  Initializes the object.
     * @note   This function can be overridden by derived classes to 
     *         implement specific initialization logic.
     */
    virtual void init();

    /**
     * @brief  Processes the object.
     * @note   This function can be overridden by derived classes to  handle specific processing operations.
     */
    virtual void process();
};

/*************************************************************************\
 * Implementation
\*************************************************************************/
void baseClass::init() {
    // Placeholder for initialization logic. Derived classes can override this.
}

void baseClass::process() {
    // Placeholder for process logic. Derived classes can override this.
}

/*************************************************************************\
 * End of file
\*************************************************************************/
