cmake_minimum_required(VERSION 3.16)

set(MCU_NAME "atmega328p")
set(CPU_FREQ "16000000")
set(PORT "COM4")

include(cmake/avr.cmake)
include(cmake/cppcheck.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

project(zol)

add_subdirectory(lib)
add_subdirectory(app)

add_subdirectory(examples)