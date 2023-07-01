#include <stdio.h>
#include <pico/stdlib.h>
#include "hardware/adc.h"

#include "ADC_Util.h"


WV_RP2040::WV_RP2040_ADC & WV_RP2040::WV_RP2040_ADC::get_Inst()
{
    static WV_RP2040_ADC __instance;
    return __instance;
}


WV_RP2040::WV_RP2040_ADC::WV_RP2040_ADC() :
    isADCInit(false)
{
    adc_init();
}