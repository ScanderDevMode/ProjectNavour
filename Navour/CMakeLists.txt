#Check the minimum cmake version
cmake_minimum_required(VERSION 3.12)

#include the external files to set the SDK and extras paths
include(pico_sdk_import.cmake)
include(pico_extras_import_optional.cmake)

#set project name and standards
project(Navour C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#check the pico sdk version
if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

#set the project directory
set(NAVOUR_PROJ_PATH, ${PROJECT_SOURCE_DIR})

#init the pico sdk
pico_sdk_init()

#add the compiler options
add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

#Add subdirecttories
add_subdirectory(./WV_RP2040_Utility)
add_subdirectory(./WV_RP2040_LCD)

#main executable program
add_subdirectory(./NavourMain)