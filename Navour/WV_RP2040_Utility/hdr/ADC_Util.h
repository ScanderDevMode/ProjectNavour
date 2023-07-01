#ifndef _RP2040_ADC_UTIL_HEADER_
#define _RP2040_ADC_UTIL_HEADER_

/** \file WV_RP2040_Utility/ADC_Util.h
 *  \headerfile ADC_Util.h
 *  \defgroup WV_RP2040_ADC WV_RP2040_ADC api can be used to use onboard ADC functionality.
 *  \author TheClownDev
 * 
 *  \brief GPIO PINs connected to the onboard Analog to Digital converter on WV_RP2040 board interface.
 * 
 * The RP2040 has GPIO pins onboard, out of which,
 * some are used for special inputs and outputs for pheripherals
 * like ADC, I2C, etc.. This API provides a generalized way to interact
 * with the ADC pins on high level ADC functionality like writing the inputs to the input pins,
 * converting the analog input data in digital, interacting with onboard sensors using ADC interface, etc. if any.
 * 
 *  \subsection WV_RP2040_Utility APIs related to the WV_RP2040 HW.
 *  \addtogroup WV_RP2040_ADC
 * 
 *  \include ADC_Util.h
*/

/*! \namespace WV_RP2040
 *  \brief Namspace for the WV_RP2040 APIs
 *  \subsection WV_RP2040_Utility
*/
namespace WV_RP2040 {

    /*! \brief singleton class for WV_RP2040 ADC communication
     *  \ingroup WV_RP2040_ADC
     *  \class WV_RP2040_ADC
     */
    class WV_RP2040_ADC {
    private:
        bool isADCInit;

        /*! \brief Constructor
         *  \ingroup WV_RP2040_ADC
         *  
         * Is private, cannot be called.
         */
        WV_RP2040_ADC();

    public:

        /*! \brief
        *   \ingroup WV_RP2040_ADC
        *
        *   Enum containing the ADC pins on the board.
        */
        typedef enum _WV_RP2040_ADC_PINS_ {
            ADC_BAT_AQUISITION      = 29,
            ADC_PIN_0               = 26,
            ADC_PIN_1               = 27,
            ADC_PIN_2               = 28,
            ADC_PIN_3               = 29
        } WV_RP2040_ADC_PINS;

        /*! \brief Get Instance
        *   \ingroup WV_RP2040_ADC
        *
        *   \category Local Function
        *
        *   Get the static instance of the singleton class WV_RP2040_ADC.
        */
        static WV_RP2040_ADC & get_Inst();
    };
}

#endif