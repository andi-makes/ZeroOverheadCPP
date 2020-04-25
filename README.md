# ZeroOverheadCPP
Exploring the concept of Zero Overhead C++ in Microcontrollers.

## Setup
 * [PlatformIO with Visual Studio Code](https://platformio.org/install/ide?install=vscode)
 * Arduino UNO

## Folder Structure
There will be a folder for each topic I'll develop a Zero Overhead Library (`ZOL`) for. In there, I'll create two PlatformIO Project:
 * A plain `C` one: Just plain old Register Manipulating with lots of comments. This will be the reference for "Zero Overhead".
 * A `C++` one: Here I will try to add some syntax sugar to the `C` version using classes. I will compare the flash and RAM size of the program to the `C` program.
 * Maybe a Program using the Arduino Library.

At the root of each folder I'll put a `README.md` file, where I discuss my findings while developing the Zero Overhead Library. There will also be a resume at the end, discussing my final findings.

## Basic Concept of `ZOL`
The basic concept is, that the compiler produces the same Assembler Code for the `C` and the `C++` program. This is possible through compile-time optimizations such as function inlining.