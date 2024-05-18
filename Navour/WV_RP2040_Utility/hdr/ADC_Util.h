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
        static constexpr inline float voltageConversionFactor = 3.3f / (1 << 12);

        bool isADCInit = false;

        /*! \brief Constructor
         *  \ingroup WV_RP2040_ADC
         *  
         *  Is private, cannot be called.
         */
        WV_RP2040_ADC();

        /*! \brief Copy Constructor
         *  \ingroup WV_RP2040_ADC
         *  
         *  Is private, cannot be called.
         */
        WV_RP2040_ADC( const WV_RP2040_ADC & ) = delete;

        /*! \brief Operator =
         *  \ingroup WV_RP2040_ADC
         *  
         *  Is private, cannot be called.
         */
        WV_RP2040_ADC& operator=( const WV_RP2040_ADC & ) = delete;

    public:

        /*! \brief WV RP2040 ADC AINSEL Pins
        *   \ingroup WV_RP2040_ADC
        *
        *   Enum containing the ADC AINSEL pins on the board.
        *   These relates to the Ainsel Pins.
        */
        typedef enum _WV_RP2040_ADC_AINSEL_PINS_ {
            ADC_AINSEL_PIN_1                = 0,
            ADC_AINSEL_PIN_2                = 1,
            ADC_AINSEL_PIN_3                = 2,
            ADC_AINSEL_PIN_4                = 3, //channel used for Battery Aquisition
            ADC_AINSEL_PIN_BAT              = 3, //channel used for Battery Aquisition
            ADC_AINSEL_PIN_TEMP             = 4, //Channel used for onboard Temp Sensor
        } WV_RP2040_ADC_AINSEL_PINS;

        /*! \brief WV RP2040 ADC GPIO Pins
        *   \ingroup WV_RP2040_ADC
        *
        *   Enum containing the ADC GPIO pins on the board.
        *   These relates to the Ainsel Pins.
        */
        typedef enum _WV_RP2040_ADC_GPIO_PINS_ {
            ADC_GPIO_PIN_0                  = 26,
            ADC_GPIO_PIN_1                  = 27,
            ADC_GPIO_PIN_2                  = 28,
            ADC_GPIO_PIN_3                  = 29, //BAT Aquisition PIN
            ADC_GPIO_PIN_BAT                = 29, //BAT Aquisition PIN
        } WV_RP2040_ADC_GPIO_PINS;

        /*! \brief Get Instance
        *   \ingroup WV_RP2040_ADC
        *
        *   \category Global Function
        *
        *   Get the static instance of the singleton class WV_RP2040_ADC.
        */
        static WV_RP2040_ADC & get_Inst();

        /*! \brief Is ADC Initialized
        *   \ingroup WV_RP2040_ADC
        *
        *   \category Global Function
        *
        *   Checks if the hardware ADC is initialized.
        *   
        *   \return Usualy always returns true if called for now.
        */
        static bool isADCInitialized();

        /*! \brief Get Temparature
        *   \ingroup WV_RP2040_ADC
        *
        *   \category Local Function
        *
        *   Gets the temparature of from the onboard temparature sensor.
        *
        *   \param inFarhenhite - If true, returns the result in farhenhite else in Celcius.
        *   
        *   \return Returns the reading from the temparature sensor in the desired output.
        */
        float get_OnboardTemparature( bool inFarhenhite ) const;

        /*! \brief Get Voltage Conversion Factor
        *   \ingroup WV_RP2040_ADC
        *
        *   \category Global Function
        *
        *   Gets the Conversion Factor to convert Analog to Digital readings into voltage.
        *   Multiply this value with the current adc reading to convert the data into voltage.
        *   
        *   \return Returns the Voltage Conversion factor
        */
        static float get_VConvFact( bool inFarhenhite );

        /*! \brief Convert Temparature
        *   \ingroup WV_RP2040_ADC
        *
        *   \category Global Function
        *
        *   Converts the given value from celcius to farhenhite or vice versa.
        *   
        *   \param value - the value to be converted.
        *   \param inFarhenhite - if true, assumes the value to be celcius and converts to farhenhite, else does the opposite.
        * 
        *   \return the converted temparature value.
        */
        static float conv_Temp( const float value, const bool inFarhenhite );

        /*! \brief Is Battery Powered
        *   \ingroup WV_RP2040_ADC
        *
        *   \category Global Function
        *
        *   Checks if the device is battery powered or not.
        *   
        *   \return Returns true if battery powered, false if not.
        */
        static bool is_BatPow();

        /*! \brief Get Power Voltage
        *   \ingroup WV_RP2040_ADC
        *
        *   \category Global Function
        *
        *   Returns the power voltage, from the VSYS Pin.
        *   
        *   \return Returns the power voltage, from the VSYS Pin..
        */
        static float get_PowVolt();

        /*! \brief Get Sampled Result
         *  \ingroup WV_RP2040_ADC
         *  
         *  \category Local Function
         *  
         *  Returns the Most common sample out of all the n samples, where n = sample count.
         * 
         *  \param apin - The Ainsel pin to sample, should be respective to gpin.
         *  \param gpin - The GPIO pin to sample, should be respective to apin.
         *  \param sampleCount - The number of sample to be aquired.
        */
        float get_sampled_result( const WV_RP2040_ADC_AINSEL_PINS apin, const WV_RP2040_ADC_GPIO_PINS gpin, const int sampleCount );
    };
}

#endif