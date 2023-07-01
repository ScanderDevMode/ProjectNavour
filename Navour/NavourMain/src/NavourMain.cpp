#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "WV_RP_2040_LCD.h"

//function to embbed the signature
bool embbedSignature() {
    bi_decl(bi_program_description("Navour 0.1[Alpha Build]\nPBWA CORP."));
    return true;
}


int main() {
    
    bool lit = false;
    WV_RP2040::WV_RP2040_LCD lcd;

    //embbed Signature Information
    embbedSignature();

    //init the std input and output
    stdio_init_all();

    //print signature
    printf("Navour 0.1[Alpha Build]\nPBWA CORP.\n\n");

    //work for now
    while (true) {
        printf("Hello from Navour!!!\n");
        printf("The world is your Navmesh!!!\n");
        lcd.set_Backlight(lit);
        lit = !lit;
        sleep_ms(1000);
    }

    return 0;
}