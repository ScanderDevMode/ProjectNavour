#CMAKE for executable
cmake_minimum_required(VERSION 3.12)

#include directories
include_directories(./hdr) #self headers
include_directories(../WV_RP2040_LCD/hdr)
include_directories(../WV_RP2040_Utility/hdr)

#files building this
add_executable(NavourMain
    ./src/NavourMain.cpp
)

if (TARGET tinyusb_device)
    #CHANGE the stdio output and input interface
    pico_enable_stdio_usb(NavourMain 1) #enabled
    pico_enable_stdio_uart(NavourMain 0) #disabled
elseif(PICO_ON_DEVICE)
    message(WARNING "TinyUSB Submodule not found in SDK.")
endif()

#create the extra artifact outputs
pico_add_extra_outputs(NavourMain)

#pull in common dependencies
target_link_libraries(NavourMain 
    pico_stdlib
    WV_RP2040_LCD
)