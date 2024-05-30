#include "GPIO_Util.h"

namespace WV_RP2040 {

    void digital_set_pin_mode(const DIGITAL_VALUE &pin, const DIGITAL_VALUE &mode) {
        gpio_init(pin);
        gpio_set_dir(pin, (mode == DIGITAL_IN) ? GPIO_IN : GPIO_OUT);
    }

    DIGITAL_VALUE digital_read(const DIGITAL_VALUE &pin) {
        return gpio_get(pin);
    }

    void digital_write(const DIGITAL_VALUE &pin, const DIGITAL_VALUE &value) {
        gpio_put(pin, value);
    }

    void digital_input_default(const DIGITAL_VALUE &pin, const DIGITAL_VALUE &value) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
        
        if (value != DIGITAL_LOW) {
            if (!gpio_is_pulled_up(pin)) {
                gpio_pull_up(pin);
            }
        } else {
            if (!gpio_is_pulled_down(pin)) {
                gpio_pull_down(pin);
            }
        }
    }

    void toggle_pin(const DIGITAL_VALUE &pin) {
        DIGITAL_VALUE current_state = gpio_get(pin);
        gpio_put(pin, !current_state);
    }

    void set_pull_up(const DIGITAL_VALUE &pin) {
        gpio_pull_up(pin);
    }

    void clear_pull_up(const DIGITAL_VALUE &pin) {
        gpio_disable_pulls(pin);
    }

    void set_pull_down(const DIGITAL_VALUE &pin) {
        gpio_pull_down(pin);
    }

    void clear_pull_down(const DIGITAL_VALUE &pin) {
        gpio_disable_pulls(pin);
    }

    DIGITAL_VALUE digital_read_debounce(const DIGITAL_VALUE &pin, unsigned int delay_ms) {
        DIGITAL_VALUE state = gpio_get(pin);
        sleep_ms(delay_ms);
        return (state == gpio_get(pin)) ? state : !state;
    }

    void initialize_pins(const std::vector<DIGITAL_VALUE> &pins, const DIGITAL_VALUE &mode) {
        for (const auto &pin : pins) {
            gpio_init(pin);
            gpio_set_dir(pin, (mode == DIGITAL_IN) ? GPIO_IN : GPIO_OUT);
        }
    }

    void blink_pin(const DIGITAL_VALUE &pin, unsigned int interval_ms, unsigned int times) {
        for (unsigned int i = 0; i < times; ++i) {
            gpio_put(pin, DIGITAL_HIGH);
            sleep_ms(interval_ms);
            gpio_put(pin, DIGITAL_LOW);
            sleep_ms(interval_ms);
        }
    }

    bool is_pin_high(const DIGITAL_VALUE &pin) {
        return gpio_get(pin) == DIGITAL_HIGH;
    }

    bool is_pin_low(const DIGITAL_VALUE &pin) {
        return gpio_get(pin) == DIGITAL_LOW;
    }

    void attach_interrupt(const DIGITAL_VALUE &pin, gpio_irq_callback_t callback, unsigned int event_mask) {
        gpio_set_irq_enabled_with_callback(pin, event_mask, true, callback);
    }

    void detach_interrupt(const DIGITAL_VALUE &pin, unsigned int event_mask) {
        gpio_set_irq_enabled(pin, event_mask, false);
    }

}
