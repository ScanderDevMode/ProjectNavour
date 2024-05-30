#include <stdio.h>
#include <pico/stdlib.h>

#include "hardware/adc.h"

#if CYW43_USES_VSYS_PIN
#include "pico/cyw43_arch.h"
#endif

#include "ADC_Util.h"
#include "List_Util.h"


WV_RP2040::WV_RP2040_ADC & WV_RP2040::WV_RP2040_ADC::get_Inst()
{
    static WV_RP2040_ADC __instance;
    return __instance;
}

bool WV_RP2040::WV_RP2040_ADC::isADCInitialized()
{
    return get_Inst().isADCInit;
}

WV_RP2040::WV_RP2040_ADC::WV_RP2040_ADC()
{
    //init the ADC class
    adc_init();
    isADCInit = true;
}

float WV_RP2040::WV_RP2040_ADC::get_VConvFact()
{
    return voltageConversionFactor;
}

float WV_RP2040::WV_RP2040_ADC::get_OnboardTemparature(bool inFarhenhite ) const
{
    if (!isADCInit)
        return 0.0f;

    adc_set_temp_sensor_enabled(true);
    adc_select_input(ADC_AINSEL_PIN_TEMP);
    
    //get the adc reading and convert into float
    float adcVoltage = (float)adc_read() * voltageConversionFactor;
    //convert to temparature in celcius
    float tempC = 27.0f - ( adcVoltage - 0.706 ) / 0.001721f;

    adc_set_temp_sensor_enabled(false);

    if (!inFarhenhite)
        return tempC;

    return conv_Temp(tempC, true);
}

float WV_RP2040::WV_RP2040_ADC::conv_Temp( const float value, const bool inFarhenhite)
{
    if ( inFarhenhite )
        return (value * 9 / 5) + 32;
    else
        return ( value - 32 ) * 5 / 9;
}

bool WV_RP2040::WV_RP2040_ADC::is_BatPow()
{
#if defined CYW43_WL_GPIO_VBUS_PIN
    return !cyw43_arch_gpio_get( CYW43_WL_GPIO_VBUS_PIN );
#elif defined PICO_VBUS_PIN
    gpio_set_function( PICO_VBUS_PIN, GPIO_FUNC_SIO );
    return !gpio_get( PICO_VBUS_PIN );
#else
    return false;
#endif
    return false;
}

float WV_RP2040::WV_RP2040_ADC::get_PowVolt()
{
#ifndef PICO_VSYS_PIN
    return 4.4f;
#else
#if CYW43_USES_VSYS_PIN
    cyw43_thread_enter();
    // Make sure cyw43 is awake
    int vbus_status = cyw43_arch_gpio_get(CYW43_WL_GPIO_VBUS_PIN);
    cyw43_thread_exit();
    return (vbus_status ? 5.0f : 0.0f); // Example logic to return a voltage based on VBUS status
#else
    adc_gpio_init ( PICO_VSYS_PIN ); //use the hw biased pin
    adc_select_input(PICO_VSYS_PIN); // Select the correct ADC input
    uint16_t adc_value = adc_read(); // Read the ADC value
    float voltage = adc_value * get_VConvFact(); // Convert the ADC value to voltage
    return voltage;
#endif
#endif
}

float WV_RP2040::WV_RP2040_ADC::get_sampled_result( const WV_RP2040_ADC_AINSEL_PINS apin, const WV_RP2040_ADC_GPIO_PINS gpin, const int sampleCount )
{
    if ( !isADCInit )
        return 0.0f;

    WV_RP2040_List<float> list;

    adc_gpio_init( gpin );
    adc_select_input( apin );

    adc_fifo_setup( true, false, 0, false, false );

    adc_run( true );

    //ignore the first 10 blocking to ignore the low read counts
    for ( int i = 0; !adc_fifo_is_empty() && i < 10; i++ ) {
        (void)adc_fifo_get_blocking();
    }

    //read the values
    for ( int i = 0; i < sampleCount; i++ ) {
        float val = (float)adc_fifo_get_blocking();
        list.append(val);
    }

    adc_run(false);
    adc_fifo_drain();
    adc_fifo_setup( false, false, 0, false, false );

    //get average
    float sum = 0.0f;
    for (int i = 1; i <= list.getCount(); ++i) {
        sum += list[i - 1];
    }
    float average = sum / sampleCount;

    return average;
}