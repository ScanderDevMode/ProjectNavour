//#include "hardware/spi.h"
#include "GPIO_Util.h"
#include "WV_RP2040_LCD.h"
#include "lv_conf.h"

void WV_RP2040::WV_RP2040_LCD::init_Onboard_LCD_Pins() {
    // Initialize the GPIO pins on the LCD
    digital_set_pin_mode(WV_RP2040_LCD_RST_PIN, DIGITAL_OUT);
    digital_set_pin_mode(WV_RP2040_LCD_DC_PIN, DIGITAL_OUT);
    digital_set_pin_mode(WV_RP2040_LCD_CS_PIN, DIGITAL_OUT);
    digital_set_pin_mode(WV_RP2040_LCD_BL_PIN, DIGITAL_OUT);
}

WV_RP2040::WV_RP2040_LCD::WV_RP2040_LCD() :
    isInit(false), isInDatM(false), isListening(false), isBLLit(false) {
    init_Onboard_LCD_Pins();

    set_Listen(false);
    set_DataMode(false);

    isInit = true;
}

WV_RP2040::WV_RP2040_LCD & WV_RP2040::WV_RP2040_LCD::get_Inst() {
    static WV_RP2040_LCD __instance;
    return __instance;
}

bool WV_RP2040::WV_RP2040_LCD::is_Initiated() {
    return isInit;
}

void WV_RP2040::WV_RP2040_LCD::set_DataMode(const bool setToDat) {
    digital_write(WV_RP2040_LCD_DC_PIN, (setToDat) ? DIGITAL_HIGH : DIGITAL_LOW);
    isInDatM = setToDat;
}

bool WV_RP2040::WV_RP2040_LCD::is_InDataMode() {
    return isInDatM;
}

void WV_RP2040::WV_RP2040_LCD::set_Listen(const bool setToListen) {
    digital_write(WV_RP2040_LCD_CS_PIN, (setToListen) ? DIGITAL_LOW : DIGITAL_HIGH);
    isListening = setToListen;
}

bool WV_RP2040::WV_RP2040_LCD::is_Listening() {
    return isListening;
}

void WV_RP2040::WV_RP2040_LCD::set_Backlight(const bool setLit) {
    digital_write(WV_RP2040_LCD_BL_PIN, (setLit) ? DIGITAL_HIGH : DIGITAL_LOW);
    isBLLit = setLit;
}

bool WV_RP2040::WV_RP2040_LCD::is_BacklightLit() {
    return isBLLit;
}

void WV_RP2040::WV_RP2040_LCD::initialize_LCD() {
    // Reset the LCD
    digital_write(WV_RP2040_LCD_RST_PIN, DIGITAL_LOW);
    sleep_ms(100);
    digital_write(WV_RP2040_LCD_RST_PIN, DIGITAL_HIGH);
    sleep_ms(100);

    // Send initialization commands to the LCD
    send_Command(0x01); // Software reset
    sleep_ms(5);
    send_Command(0x11); // Exit sleep mode
    sleep_ms(120);
    send_Command(0x29); // Display on
}

void WV_RP2040::WV_RP2040_LCD::send_Command(uint8_t cmd) {
    set_DataMode(false);
    set_Listen(true);
    spi_write_blocking(spi0, &cmd, 1);
    set_Listen(false);
}

void WV_RP2040::WV_RP2040_LCD::send_Data(uint8_t data) {
    set_DataMode(true);
    set_Listen(true);
    spi_write_blocking(spi0, &data, 1);
    set_Listen(false);
}

void WV_RP2040::WV_RP2040_LCD::draw_Pixel(uint16_t x, uint16_t y, uint16_t color) {
    send_Command(0x2A); // Column address set
    send_Data(x >> 8);
    send_Data(x & 0xFF);
    send_Data((x+1) >> 8);
    send_Data((x+1) & 0xFF);

    send_Command(0x2B); // Row address set
    send_Data(y >> 8);
    send_Data(y & 0xFF);
    send_Data((y+1) >> 8);
    send_Data((y+1) & 0xFF);

    send_Command(0x2C); // Memory write
    send_Data(color >> 8);
    send_Data(color & 0xFF);
}

void WV_RP2040::WV_RP2040_LCD::draw_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    // Bresenham's line algorithm
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        draw_Pixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void WV_RP2040::WV_RP2040_LCD::draw_Rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    for (uint16_t i = 0; i < h; i++) {
        draw_Line(x, y + i, x + w - 1, y + i, color);
    }
}

void WV_RP2040::WV_RP2040_LCD::draw_Char(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg) {
    for (int8_t i = 0; i < 5; i++ ) {
        uint8_t line = font[c * 5 + i];
        for (int8_t j = 0; j < 8; j++, line >>= 1) {
            if (line & 1) {
                draw_Pixel(x + i, y + j, color);
            } else {
                draw_Pixel(x + i, y + j, bg);
            }
        }
    }
}

void WV_RP2040::WV_RP2040_LCD::draw_String(uint16_t x, uint16_t y, const char *str, uint16_t color, uint16_t bg) {
    while (*str) {
        draw_Char(x, y, *str++, color, bg);
        x += 6; // Advance to next character
    }
}

void WV_RP2040::WV_RP2040_LCD::clear_Screen(uint16_t color) {
    draw_Rectangle(0, 0, 240, 240, color); // Assuming a 240x240 LCD
}

uint8_t WV_RP2040::WV_RP2040_LCD::read_Data() {
    set_DataMode(true);
    set_Listen(true);
    uint8_t data;
    spi_read_blocking(spi0, 0, &data, 1);
    set_Listen(false);
    return data;
}
