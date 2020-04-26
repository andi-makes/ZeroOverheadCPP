/// THE HELLO WORLD - ARDUINO STYLE
/// Here I've got the Arduino version of a blinking LED.
/// As you can see, it is much more readable than the C version.
/// But this readability comes at a cost:
///
/// Flash size: 1286 / 32256 Bytes (4.0%)
/// Amount of used RAM: 9 / 2048 Bytes (0.4%)
///
/// To be fair, that is with exactly the same compiler settings the C version uses.
/// If you compile it with the Arduino standard options, you'll get something more like this:
/// Flash size: 930 / 32256 Bytes (2.9%)
/// Amount of used RAM: 9 / 2048 Bytes (0.4%)
///
/// Still, compared to the C version this Arduino version is on the heavy side.
/// Some might say that that's the price for the gained abstraction. As we will see soon,
/// we can do better than that. We will gain:
///  - More functionality
///  - The same amount of abstraction
///  - Better Performance (No overhead compared to the C version)
///  - And all of that using evil C++! With classes! 

// Needed because we are writing in a .cpp file
#include <Arduino.h>

// Entry Point of the program, similar to `int main()`
void setup() {
	pinMode(13, OUTPUT);
}

// Main Loop of the program, similar to `while(1)`
void loop() {
	// We have no way of toggeling the port using Arduino functions, 
	// so we have to set HIGH and LOW explicitly.
	digitalWrite(13, HIGH);
	delay(500);
	digitalWrite(13, LOW);
	delay(500);
}