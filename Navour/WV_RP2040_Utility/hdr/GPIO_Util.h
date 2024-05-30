#ifndef _RP2040_GPIO_UTIL_HEADER_
#define _RP2040_GPIO_UTIL_HEADER_

#include <vector>
#include "pico/stdlib.h"

/** \file WV_RP2040_Utility/GPIO_Util.h
 *  \headerfile GPIO_Util.h
 *  \defgroup WV_RP2040_GPIO WV_RP2040_GPIO api can be used to use GPIO functionality.
 *  \author TheClownDev 
 * 
 *  \brief General Purpose Input/Output PIN functionalities on WV_RP2040 board interface.
 * 
 *  The RP2040 has GPIO pins onboard, out of which,
 *  some are used for special inputs and outputs for peripherals
 *  like ADC, I2C, etc.. This API provides a generalized way to interact
 *  with those pins on a low level GPIO functionality like reading, writing, etc.
 *  regardless of the pins being special pins connected to the peripherals.
 * 
 *  \subsection WV_RP2040_Utility APIs related to the WV_RP2040 HW.
 *  \addtogroup WV_RP2040_GPIO
 * 
 *  \include GPIO_Util.h
 */

/*! \namespace WV_RP2040
 *  \brief Namespace for the WV_RP2040 APIs
 *  \subsection WV_RP2040_Utility
 */
namespace WV_RP2040 {

/*! \def DIGITAL VALUE
 *  \brief Data Type
 *  \details A definition acting as digital value data type.
 *  \ingroup WV_RP2040_GPIO
 */
#define DIGITAL_VALUE unsigned short

/*! \def DIGITAL Low
 *  \brief Value
 *  \details Value for digital low.
 *  \ingroup WV_RP2040_GPIO
 */
#define DIGITAL_LOW 0

/*! \def DIGITAL High
 *  \brief Value
 *  \details Value for digital high.
 *  \ingroup WV_RP2040_GPIO
 */
#define DIGITAL_HIGH 1

/*! \def DIGITAL In
 *  \brief Value
 *  \details Value for digital in.
 *  \ingroup WV_RP2040_GPIO
 */
#define DIGITAL_IN DIGITAL_LOW

/*! \def DIGITAL Out
 *  \brief Value
 *  \details Value for digital out.
 *  \ingroup WV_RP2040_GPIO
 */
#define DIGITAL_OUT DIGITAL_HIGH

/*! \brief Digital Set Pin Mode
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Sets the digital pin mode to DIGITAL_IN / DIGITAL_OUT
 * 
 *  \param pin The pin to be set
 *  \param mode The mode to set the pin to (DIGITAL_IN / DIGITAL_OUT)
 */
void digital_set_pin_mode(const DIGITAL_VALUE &pin, const DIGITAL_VALUE &mode);

/*! \brief Digital Read
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Reads on a pin using GPIO / digital read
 * 
 *  \param pin The pin to read from
 *  \return DIGITAL_HIGH / DIGITAL_LOW
 */
DIGITAL_VALUE digital_read(const DIGITAL_VALUE &pin);

/*! \brief Digital Write
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Writes on a pin using GPIO / digital write
 * 
 *  \param pin The pin to write on
 *  \param value The value to write (DIGITAL_HIGH / DIGITAL_LOW)
 */
void digital_write(const DIGITAL_VALUE &pin, const DIGITAL_VALUE &value);

/*! \brief Digital Input Default
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Sets a pin to input mode, and sets the default state of the
 *  pin to DIGITAL_HIGH / DIGITAL_LOW using the pull-up/pull-down resistors,
 *  An external source can make it low or high again.
 * 
 *  \param pin The pin to set
 *  \param value The default state (DIGITAL_HIGH / DIGITAL_LOW)
 */
void digital_input_default(const DIGITAL_VALUE &pin, const DIGITAL_VALUE &value);

/*! \brief Toggle Pin
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Toggles the state of a GPIO pin.
 * 
 *  \param pin The pin to toggle
 */
void toggle_pin(const DIGITAL_VALUE &pin);

/*! \brief Set Pull-Up Resistor
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Enables the pull-up resistor on a GPIO pin.
 * 
 *  \param pin The pin to set the pull-up resistor on
 */
void set_pull_up(const DIGITAL_VALUE &pin);

/*! \brief Clear Pull-Up Resistor
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Disables the pull-up resistor on a GPIO pin.
 * 
 *  \param pin The pin to clear the pull-up resistor on
 */
void clear_pull_up(const DIGITAL_VALUE &pin);

/*! \brief Set Pull-Down Resistor
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Enables the pull-down resistor on a GPIO pin.
 * 
 *  \param pin The pin to set the pull-down resistor on
 */
void set_pull_down(const DIGITAL_VALUE &pin);

/*! \brief Clear Pull-Down Resistor
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Disables the pull-down resistor on a GPIO pin.
 * 
 *  \param pin The pin to clear the pull-down resistor on
 */
void clear_pull_down(const DIGITAL_VALUE &pin);

/*! \brief Digital Read with Debounce
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Reads the state of a GPIO pin with software debouncing.
 * 
 *  \param pin The pin to read from
 *  \param delay_ms The debounce delay in milliseconds (default is 50ms)
 *  \return DIGITAL_HIGH / DIGITAL_LOW
 */
DIGITAL_VALUE digital_read_debounce(const DIGITAL_VALUE &pin, unsigned int delay_ms = 50);

/*! \brief Initialize Multiple Pins
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Initializes multiple GPIO pins at once.
 * 
 *  \param pins A vector of pins to initialize
 *  \param mode The mode to set the pins to (DIGITAL_IN / DIGITAL_OUT)
 */
void initialize_pins(const std::vector<DIGITAL_VALUE> &pins, const DIGITAL_VALUE &mode);

/*! \brief Blink Pin
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Blinks a GPIO pin at a specified interval.
 * 
 *  \param pin The pin to blink
 *  \param interval_ms The interval in milliseconds
 *  \param times The number of times to blink
 */
void blink_pin(const DIGITAL_VALUE &pin, unsigned int interval_ms, unsigned int times);

/*! \brief Check if Pin is High
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Checks if a GPIO pin is in a high state.
 * 
 *  \param pin The pin to check
 *  \return true if the pin is high, false otherwise
 */
bool is_pin_high(const DIGITAL_VALUE &pin);

/*! \brief Check if Pin is Low
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Checks if a GPIO pin is in a low state.
 * 
 *  \param pin The pin to check
 *  \return true if the pin is low, false otherwise
 */
bool is_pin_low(const DIGITAL_VALUE &pin);

/*! \brief Attach Interrupt
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Attaches an interrupt handler to a GPIO pin.
 * 
 *  \param pin The pin to attach the interrupt to
 *  \param callback The callback function to call when the interrupt occurs
 *  \param event_mask The event mask for the interrupt (e.g., GPIO_IRQ_EDGE_RISE)
 */
void attach_interrupt(const DIGITAL_VALUE &pin, gpio_irq_callback_t callback, unsigned int event_mask);

/*! \brief Detach Interrupt
 *  \ingroup WV_RP2040_GPIO
 * 
 *  \category Global Function
 * 
 *  Detaches an interrupt handler from a GPIO pin.
 * 
 *  \param pin The pin to detach the interrupt from
 *  \param event_mask The event mask for the interrupt (e.g., GPIO_IRQ_EDGE_RISE)
 */
void detach_interrupt(const DIGITAL_VALUE &pin, unsigned int event_mask);

}

#endif