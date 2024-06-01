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
#define WV_RP2040_LCD_BL_PIN 25 // BackLight pin of the attached LCD

/*! \def WV RP2040 LCD Reset Pin [12]
*  \brief Value
*  \details GPIO Pin connected with the LCD reset pin.
*  \ingroup WV_RP2040_LCD
*/
#define WV_RP2040_LCD_RST_PIN 12 // Reset pin of the attached LCD

/*! \def WV RP2040 LCD Data/Command Pin [8]
*  \brief Value
*  \details GPIO Pin connected with the LCD Data/Command pin.
*  \ingroup WV_RP2040_LCD
*/
#define WV_RP2040_LCD_DC_PIN 8 // Data/Command pin of the attached LCD

/*! \def WV RP2040 LCD Chip Select Pin [9]
*  \brief Value
*  \details GPIO Pin connected with the LCD Chip Select pin.
*  \ingroup WV_RP2040_LCD
*/
#define WV_RP2040_LCD_CS_PIN 9 // Chip Select pin of the attached LCD

/*! \def WV RP2040 LCD Slave Clock Pin [10]
*  \brief Value
*  \details GPIO Pin connected with the LCD Slace Clock pin.
*  \ingroup WV_RP2040_LCD
*/
#define WV_RP2040_LCD_CLK_PIN 10 // Clock pin of the attached LCD

/*! \def WV RP2040 LCD Data-In Pin [11]
*  \brief Value
*  \details GPIO Pin connected with the LCD Data-In pin.
*  \ingroup WV_RP2040_LCD
*/
#define WV_RP2040_LCD_DIN_PIN 11 // Data-In pin of the attached LCD

/*! \class WV_RP2040_LCD
 *  \ingroup WV_RP2040_LCD
 *  \brief WV_RP2040_LCD class
 * 
 *  This class provides an interface to communicate with the on-board LCD screen of the WV_RP2040.
 *  It includes methods to initialize the LCD, set data and command modes, control the backlight,
 *  and draw graphics.
 */
class WV_RP2040_LCD
{
private:
    bool isInit;   /*!< Flag to check if the LCD is initialized */
    bool isInDatM; /*!< Flag to check if the LCD is in data mode */
    bool isListening; /*!< Flag to check if the LCD is listening */
    bool isBLLit; /*!< Flag to check if the backlight is lit */

    /*! \brief Initialize LCD pins
    *  \ingroup WV_RP2040_LCD
    *  \category Local Function
    * 
    *  Initializes the GPIO pins connected to the LCD.
    */
    void init_Onboard_LCD_Pins();

    /*! \brief Constructor
    *  \ingroup WV_RP2040_LCD
    *  \category Local Function
    * 
    *  Initializes the LCD and its pins.
    */
    WV_RP2040_LCD();

public:
    /*! \brief Get Instance
    *  \ingroup WV_RP2040_LCD
    * 
    *  Singleton instance accessor.
    * 
    *  \return Reference to the single instance of the class.
    */
    static WV_RP2040_LCD & get_Inst();

    /*! \brief Is Initiated
    *  \ingroup WV_RP2040_LCD
    * 
    *  Checks if the LCD is initialized.
    * 
    *  \return True if initialized, false otherwise.
    */
    bool is_Initiated();

    /*! \brief Set Data Mode
    *  \ingroup WV_RP2040_LCD
    * 
    *  Sets the LCD to data mode or command mode.
    * 
    *  \param setToDat Set to true for data mode, false for command mode.
    */
    void set_DataMode(const bool setToDat);

    /*! \brief Is In Data Mode
    *  \ingroup WV_RP2040_LCD
    * 
    *  Checks if the LCD is in data mode.
    * 
    *  \return True if in data mode, false otherwise.
    */
    bool is_InDataMode();

    /*! \brief Set Listen
    *  \ingroup WV_RP2040_LCD
    * 
    *  Sets the LCD to listen mode or not.
    * 
    *  \param setToListen Set to true to listen, false to stop listening.
    */
    void set_Listen(const bool setToListen);

    /*! \brief Is Listening
    *  \ingroup WV_RP2040_LCD
    * 
    *  Checks if the LCD is in listening mode.
    * 
    *  \return True if listening, false otherwise.
    */
    bool is_Listening();

    /*! \brief Set Backlight
    *  \ingroup WV_RP2040_LCD
    * 
    *  Sets the backlight of the LCD.
    * 
    *  \param setLit Set to true to turn on the backlight, false to turn it off.
    */
    void set_Backlight(const bool setLit);

    /*! \brief Is Backlight Lit
    *  \ingroup WV_RP2040_LCD
    * 
    *  Checks if the LCD backlight is lit.
    * 
    *  \return True if backlight is lit, false otherwise.
    */
    bool is_BacklightLit();

    /*! \brief Initialize LCD
    *  \ingroup WV_RP2040_LCD
    * 
    *  Sends the initialization sequence to the LCD.
    */
    void initialize_LCD();

    /*! \brief Send Command
    *  \ingroup WV_RP2040_LCD
    * 
    *  Sends a command to the LCD.
    * 
    *  \param cmd The command byte to be sent.
    */
    void send_Command(uint8_t cmd);

    /*! \brief Send Data
    *  \ingroup WV_RP2040_LCD
    * 
    *  Sends data to the LCD.
    * 
    *  \param data The data byte to be sent.
    */
    void send_Data(uint8_t data);

    /*! \brief Draw Pixel
    *  \ingroup WV_RP2040_LCD
    * 
    *  Draws a pixel on the LCD.
    * 
    *  \param x The x-coordinate of the pixel.
    *  \param y The y-coordinate of the pixel.
    *  \param color The color of the pixel.
    */
    void draw_Pixel(uint16_t x, uint16_t y, uint16_t color);

    /*! \brief Draw Line
    *  \ingroup WV_RP2040_LCD
    * 
    *  Draws a line on the LCD.
    * 
    *  \param x0 The starting x-coordinate of the line.
    *  \param y0 The starting y-coordinate of the line.
    *  \param x1 The ending x-coordinate of the line.
    *  \param y1 The ending y-coordinate of the line.
    *  \param color The color of the line.
    */
    void draw_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

    /*! \brief Draw Rectangle
    *  \ingroup WV_RP2040_LCD
    * 
    *  Draws a rectangle on the LCD.
    * 
    *  \param x The x-coordinate of the top-left corner.
    *  \param y The y-coordinate of the top-left corner.
    *  \param w The width of the rectangle.
    *  \param h The height of the rectangle.
    *  \param color The color of the rectangle.
    */
    void draw_Rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

    /*! \brief Draw Character
    *  \ingroup WV_RP2040_LCD
    * 
    *  Draws a character on the LCD.
    * 
    *  \param x The x-coordinate of the character.
    *  \param y The y-coordinate of the character.
    *  \param c The character to be drawn.
    *  \param color The color of the character.
    *  \param bg The background color.
    */
    void draw_Char(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg);

    /*! \brief Draw String
    *  \ingroup WV_RP2040_LCD
    * 
    *  Draws a string on the LCD.
    * 
    *  \param x The x-coordinate of the string.
    *  \param y The y-coordinate of the string.
    *  \param str The string to be drawn.
    *  \param color The color of the string.
    *  \param bg The background color.
    */
    void draw_String(uint16_t x, uint16_t y, const char *str, uint16_t color, uint16_t bg);

    /*! \brief Clear Screen
    *  \ingroup WV_RP2040_LCD
    * 
    *  Clears the LCD screen with the given color.
    * 
    *  \param color The background color to fill the screen.
    */
    void clear_Screen(uint16_t color);

    /*! \brief Read Data
    *  \ingroup WV_RP2040_LCD
    * 
    *  Reads a byte of data from the LCD.
    * 
    *  \return The data byte read from the LCD.
    */
    uint8_t read_Data();

};

}

#endif
