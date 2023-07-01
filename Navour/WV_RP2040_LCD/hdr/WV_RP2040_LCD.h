#ifndef _WV_RP_2040_LCD_HEADER_
#define _WV_RP_2040_LCD_HEADER_

/** \file WV_RP2040_LCD/GPIO_Util.h
 *  \headerfile WV_RP_2040_LCD.h
 *  \defgroup WV_RP2040_LCD WV_RP2040_LCD api can be used to use GPIO functionality.
 *  \author TheClownDev
 * 
 *  \brief Interface to communicate with the attached onboard LCD screen of WV_RP2040.
 * 
 *  The WV_RP2040 is designed to have an on-board attached LCD screen. This API helps in
 *  easily communicating with the same. This api uses the different communication interfaces
 *  required to communicate with the LCD, and provides a simpler interface to use the LCD.
 * 
 *  \subsection WV_RP2040_Utility APIs related to the WV_RP2040 HW.
 *  \addtogroup WV_RP2040_LCD
 * 
 *  \include WV_RP2040_LCD.h
*/

/*! \namespace WV_RP2040
 *  \brief Namspace for the WV_RP2040 APIs
 *  \subsection WV_RP2040_Utility
*/
namespace WV_RP2040
{

/*! \def WV RP2040 LCD Back Light Pin [25]
*  \brief Value
*  \details GPIO Pin connected with the LCD back light pin.
*  \ingroup WV_RP2040_LCD
*/
#define WV_RP2040_LCD_BL_PIN 25 //BackLight pin of the attached LCD

/*! \def WV RP2040 LCD Reset Pin [12]
*  \brief Value
*  \details GPIO Pin connected with the LCD reset pin.
*  \ingroup WV_RP2040_LCD
*/
#define WV_RP2040_LCD_RST_PIN 12 //Reset pin of the attached LCD

/*! \def WV RP2040 LCD Data/Command Pin [8]
*  \brief Value
*  \details GPIO Pin connected with the LCD Data/Command pin.
*  \ingroup WV_RP2040_LCD
*/
#define WV_RP2040_LCD_DC_PIN 8 //Data/Command pin of the attached LCD

/*! \def WV RP2040 LCD Chip Select Pin [9]
*  \brief Value
*  \details GPIO Pin connected with the LCD Chip Select pin.
*  \ingroup WV_RP2040_LCD
*/
#define WV_RP2040_LCD_CS_PIN 9 //Chip Select pin of the attached LCD

/*! \def WV RP2040 LCD Slave Clock Pin [10]
*  \brief Value
*  \details GPIO Pin connected with the LCD Slace Clock pin.
*  \ingroup WV_RP2040_LCD
*/
#define WV_RP2040_LCD_CLK_PIN 10 //Clock pin of the attached LCD

/*! \def WV RP2040 LCD Master In Slave Out Pin [11]
*  \brief Value
*  \details GPIO Pin connected with the LCD Master In Slave Out pin.
*  \ingroup WV_RP2040_LCD
*/
#define WV_RP2040_LCD_MOSI_PIN 11 //MOSI pin of the attached LCD

    /*! \brief singleton class for WV_RP2040 LCD communication
     *  \ingroup WV_RP2040_LCD
     *  \class WV_RP2040_ADC
     */
    class WV_RP2040_LCD
    {
    private:
        bool isInit;
        bool isInDatM;
        bool isListening;
        bool isBLLit;
        
        /*! \brief Init Onboard LCD Pins
         *  \ingroup WV_RP2040_LCD
         *
         *  \category Private Local Function
         * 
         *  Inits all the pins for the LCD using appropriate interfaces, used by the constructor.
         */
        void init_Onboard_LCD_Pins();

        /*! \brief Constructor
         *  \ingroup WV_RP2040_ADC
         *  
         *  Is private, cannot be called.
         */
        WV_RP2040_LCD();

    public:

        /*! \brief Is Initated
        *   \ingroup WV_RP2040_LCD
        *
        *   \category Local Function
        * 
        *   Checks if the LCD is Initiated or not.
        *   
        *   \return true if initiated, false if not.
        */
        bool is_Initiated();

        /*! \brief Set Data Mode
        *   \ingroup WV_RP2040_LCD
        *
        *   \category Local Function
        * 
        *   Sets the LCD to command mode, or to data mode.
        *   
        *   \param setToDat - if true, sets to Data mode, else sets to the Command mode.
        */
        void set_DataMode( const bool setToDat = true );

        /*! \brief Is In Data Mode
        *   \ingroup WV_RP2040_LCD
        *
        *   \category Local Function
        * 
        *   Checks if the LCD is in data mode or not.
        *   
        *   \return true if in data mode, flase if not.
        */
        bool is_InDataMode();

        /*! \brief Set Listen
        *   \ingroup WV_RP2040_LCD
        *
        *   \category Local Function
        * 
        *   Sets the LCD to listen mode, or not.
        *   The LCD reacts to the command and data sent to it,
        *   only if in listening mode.
        *   
        *   \param setToListen - if true, sets to listening, else does not.
        */
        void set_Listen( const bool setToListen = true );

        /*! \brief Is Listening
        *   \ingroup WV_RP2040_LCD
        *
        *   \category Local Function
        * 
        *   Checks if the LCD is listening or not.
        *   
        *   \return true if listening, flase if not.
        */
        bool is_Listening();

        /*! \brief Set Back Light
        *   \ingroup WV_RP2040_LCD
        *
        *   \category Local Function
        * 
        *   Sets the LCD back light to be lit, or not.
        *   
        *   \param setLit - if true, sets to Lit up, else does not.
        */
        void set_Backlight( const bool setLit = true );

        /*! \brief Is Back Light Lit
        *   \ingroup WV_RP2040_LCD
        *
        *   \category Local Function
        * 
        *   Checks if the LCD Back Light is lit or not.
        *   
        *   \return true if lit, false if not.
        */
        bool is_BacklightLit();


    };

}

#endif