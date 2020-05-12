# ZeroOverheadCPP
Exploring the concept of Zero Overhead C++ in Microcontrollers.

## Setup
 * [cmake](https://cmake.org/download/)
 * [avr-gcc 9.2.0](https://blog.zakkemble.net/avr-gcc-builds/)
 * [Arduino UNO](https://store.arduino.cc/arduino-uno-rev3)

## Folder Structure
 * `app`: The program files implementing some kind of blink program
 * `bin`: The resulting binary files. I only commit the `.lss` and `.map` files, not the `.elf` nor the `.hex` files.
 * `build`: See *Building*
 * `lib`: The zero overhead library

## Basic Concept of `ZOL`
The basic concept is that the compiler produces the same Assembler Code for the `C` and the `C++` program.

## Building
Please execute the following commands:
```shell script
mkdir build
cd build
cmake ..
cmake --build .
```
You'll find the compiled output files in the `bin` folder.

## Goals
Provide similar functionality to the `Arduino` Libraries. Have a nice API. Be as fast as `C`.

## Todos:
Basically, the headings from the [Arduino Reference](https://www.arduino.cc/reference/en).
 * [X] Digital I/O
 * [ ] Analog I/O
 * [ ] Time
 * [ ] Math
 * [ ] Trigonometry
 * [ ] Random
 * [ ] Communication