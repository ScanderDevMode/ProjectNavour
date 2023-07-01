#ifndef _RP2040_GPIO_UTIL_HEADER_
#define _RP2040_GPIO_UTIL_HEADER_


/** \file WV_RP2040_Utility/GPIO_Util.h
 *  \headerfile GPIO_Util.h
 *  \defgroup WV_RP2040_GPIO WV_RP2040_GPIO api can be used to use GPIO functionality.
 *  \author TheClownDev 
 * 
 *  \brief General Purpose Input/Output PIN functionalities on WV_RP2040 board interface.
 * 
 * The RP2040 has GPIO pins onboard, out of which,
 * some are used for special inputs and outputs for pheripherals
 * like ADC, I2C, etc.. This API provides a generalized way to interact
 * with those pins on a low level GPIO functionality like reading, writing, etc.
 * regardless of the pins being special pins connected to the pheripherals.
 * 
 *  \subsection WV_RP2040_Utility APIs related to the WV_RP2040 HW.
 *  \addtogroup WV_RP2040_GPIO
 * 
 *  \include GPIO_Util.h
*/



/*! \namespace WV_RP2040
 *  \brief Namspace for the WV_RP2040 APIs
 *  \subsection WV_RP2040_Utility
*/
namespace WV_RP2040 {

/*! \def DIGITAL VALUE
*  \brief Data Type
*  \details A definition acting as digital value data type.
*  \ingroup WV_RP2040_GPIO
*/
#define DIGITAL_VALUE   unsigned short

/*! \def DIGITAL Low
*  \brief Value
*  \details Value for digital low.
*  \ingroup WV_RP2040_GPIO
*/
#define DIGITAL_LOW     0

/*! \def DIGITAL High
*  \brief Value
*  \details Value for digital high.
*  \ingroup WV_RP2040_GPIO
*/
#define DIGITAL_HIGH    1

/*! \def DIGITAL In
*  \brief Value
*  \details Value for digital in.
*  \ingroup WV_RP2040_GPIO
*/
#define DIGITAL_IN      DIGITAL_LOW

/*! \def DIGITAL Out
*  \brief Value
*  \details Value for digital out.
*  \ingroup WV_RP2040_GPIO
*/
#define DIGITAL_OUT     DIGITAL_HIGH


    /*! \brief Digital Set Pin Mode
    *   \ingroup WV_RP2040_GPIO
    *
    *   \category Global Function
    * 
    *   Sets the digital pin mode to DIGITAL_IN / DIGITAL_OUT
    *   
    *   \param pin The pin to be set
    *   \param mode The mode to be set for the given pin, DIGITAL_IN / DIGITAL_OUT
    */
    void digital_set_pin_mode( const DIGITAL_VALUE & pin, const DIGITAL_VALUE & mode );

    /*! \brief Digital Read
    *   \ingroup WV_RP2040_GPIO
    *
    *   \category Global Function
    * 
    *   Reads on a pin using GPIO / digital read
    *   
    *   \param pin the pin to read from
    *   \return - DIGITAL_HIGH / DIGITAL_LOW
    */
    DIGITAL_VALUE digital_read( const DIGITAL_VALUE & pin );

    /*! \brief Digital Write
    *   \ingroup WV_RP2040_GPIO
    *
    *   \category Global Function
    *   
    *   Writes on a pin using GPIO / digital wirte
    *   
    *   \param pin - the pin to write on
    *   \param value - the value to write, DIGITAL_HIGH / DIGITAL_LOW
    */    
    void digital_write( const DIGITAL_VALUE & pin, const DIGITAL_VALUE & value );

    /*! \brief Digital Input Default
    *   \ingroup WV_RP2040_GPIO
    *
    *   \category Global Function
    *   
    *   Sets a pin to input mode, and sets the default state of the
    *   pin to DIGITAL_HIGH / DIGITAL_LOW using the pull_up resistors,
    *   An external source can make it low or high again
    * 
    *   \param pin - the pin to set
    *   \param value - the default state, DIGITAL_HIGH / DIGITAL_LOW
    */
    void digital_input_default( const DIGITAL_VALUE & pin, const DIGITAL_VALUE & value);

}

#endif