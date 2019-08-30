
#ifndef _MYGPIO_H_
#define _MYGPIO_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"


/**
 * @brief Configures the specified pin to behave either as an input or an output
 * @param pin the pin whose mode you wish to set (according PORTNUM2PIN)
 * @param mode INPUT, OUTPUT, INPUT_PULLUP or INPUT_PULLDOWN.
 */
void MYgpioMode (pin_t pin, uint8_t mode);

/**
 * @brief Write a HIGH or a LOW value to a digital pin
 * @param pin the pin to write (according PORTNUM2PIN)
 * @param val Desired value (HIGH or LOW)
 */
void MYgpioWrite (pin_t pin, bool value);

/**
 * @brief Toggle the value of a digital pin (HIGH<->LOW)
 * @param pin the pin to toggle (according PORTNUM2PIN)
 */
void MYgpioToggle (pin_t pin);

/**
 * @brief Set the value of a digital pin
 * @param pin the pin to set (according PORTNUM2PIN)
 */
void MYgpioSet (pin_t pin);

/**
 * @brief Clear the value of a digital pin
 * @param pin the pin to clear (according PORTNUM2PIN)
 */
void MYgpioClear (pin_t pin);

/**
 * @brief Reads the value from a specified digital pin, either HIGH or LOW.
 * @param pin the pin to read (according PORTNUM2PIN)
 * @return HIGH or LOW
 */
bool MYgpioRead (pin_t pin);



//bool MYgpioIRQ (pin_t pin, uint8_t irqMode, pinIrqFun irqFun);

/*******************************************************************************
 ******************************************************************************/

#endif // _GPIO_H_
