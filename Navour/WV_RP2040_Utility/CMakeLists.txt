#CMAKE for STATIC LIB
cmake_minimum_required(VERSION 3.12)

#include directories
include_directories(./hdr) #self headers
include_directories(${PICO_SDK_PATH}/src) #Pico headers

#files depending on this
aux_source_directory(./src LIB_SOURCES)

#create the library
add_library(WV_RP2040_Utility  ${LIB_SOURCES})

#link the dependencies
target_link_libraries(WV_RP2040_Utility
    pico_stdlib
    pico_util
    hardware_adc
)