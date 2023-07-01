#include "GPIO_Util.h"

#include "WV_RP2040_LCD.h"


void WV_RP2040::WV_RP2040_LCD::init_Onboard_LCD_Pins()
{
    //init the GPIO pins on the LCD
    digital_set_pin_mode(WV_RP2040_LCD_RST_PIN, DIGITAL_OUT);
    digital_set_pin_mode(WV_RP2040_LCD_DC_PIN, DIGITAL_OUT);
    digital_set_pin_mode(WV_RP2040_LCD_CS_PIN, DIGITAL_OUT);
    digital_set_pin_mode(WV_RP2040_LCD_BL_PIN, DIGITAL_OUT);
}

WV_RP2040::WV_RP2040_LCD::WV_RP2040_LCD() :
    isInit(false), isInDatM(false), isListening(false), isBLLit(false)
{
    init_Onboard_LCD_Pins();

    set_Listen(false);
    set_DataMode(false);
    
    isInit = true;
}

bool WV_RP2040::WV_RP2040_LCD::is_Initiated()
{
    return isInit;
}

void WV_RP2040::WV_RP2040_LCD::set_DataMode(const bool setToDat)
{
    digital_write(WV_RP2040_LCD_DC_PIN, 
        (setToDat) ? DIGITAL_HIGH : DIGITAL_LOW);
    isInDatM = setToDat;
}

bool WV_RP2040::WV_RP2040_LCD::is_InDataMode()
{
    return false;
}

void WV_RP2040::WV_RP2040_LCD::set_Listen(const bool setToListen)
{
    digital_write(WV_RP2040_LCD_CS_PIN,
        (setToListen) ? DIGITAL_LOW : DIGITAL_HIGH);
    isListening = setToListen;
}

bool WV_RP2040::WV_RP2040_LCD::is_Listening()
{
    return isListening;
}

void WV_RP2040::WV_RP2040_LCD::set_Backlight(const bool setLit)
{
    digital_write(WV_RP2040_LCD_BL_PIN,
        (setLit) ? DIGITAL_HIGH : DIGITAL_LOW);
    isBLLit = setLit;
}

bool WV_RP2040::WV_RP2040_LCD::is_BacklightLit()
{
    return isBLLit;
}

