#include "pico/stdlib.h"

#include "GPIO_Util.h"


void WV_RP2040::digital_set_pin_mode(const DIGITAL_VALUE & pin, const DIGITAL_VALUE & mode)
{
    gpio_init(pin);
    gpio_set_dir(pin, (mode == DIGITAL_IN) ? DIGITAL_IN : DIGITAL_OUT);
}

DIGITAL_VALUE WV_RP2040::digital_read(const DIGITAL_VALUE & pin)
{
    return gpio_get(pin);
}

void WV_RP2040::digital_write(const DIGITAL_VALUE & pin, const DIGITAL_VALUE & value)
{
    gpio_put(pin, value);
}

void WV_RP2040::digital_input_default(const DIGITAL_VALUE & pin, const DIGITAL_VALUE & value)
{
    gpio_init(pin);
    gpio_set_dir(pin, DIGITAL_IN);
    
    if ( value != DIGITAL_LOW ) {
        if ( !gpio_is_pulled_up(pin) )
            gpio_pull_up(pin);
    }
    else {
        if ( !gpio_is_pulled_down(pin) )
            gpio_pull_down(pin);
    }
}