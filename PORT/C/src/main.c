/// THE HELLO WORLD
/// This is the "Hello, World!" of an embedded project.
/// As you can see, it is pretty straightforward. If you know how to do it.
/// Because I am using the Arduino UNO development board, I am making Digital Pin 13
/// of that board blink. Why? Because that's where this development board has a LED built in.
/// 
/// Now, how do you make Digital Pin 13 blink? All I see is just some DDRB, PORTB and a 5.
/// There is a valuable resource online available, which I highly recommend to Programmers
/// who want to use the extra gained speed of manipulating Registers directly.
///   1.: The Datasheet
///   2.: Some Pinout Diagram
/// There, you can see that Digital Pin 13 is using PB5, which is PORTB 5. Now, to make the 
/// LED on that Pin blink, you need to manipulate the DDRB and PORTB registers as shown below.
/// And voila! There you have your blinking LED. Hello World!

// Include needed for accessing the registers of the ATMEGA328p
#include <avr/io.h>
// So that we can use the _delay_ms() function
#include <util/delay.h>

// Entry Point of the Program, imagine it as the `void setup()` of an Arduino Program
int main() {
	// Defining PB5 as an Output. Comparable with `pinMode(13, OUTPUT)`
	DDRB |= (1<<5);
	
	// The main loop of the Program, imagine it as the `void loop()` of an Arduino Program
	while(1) {
		// Here we are setting PB5 LOW if it was HIGH and the other way around. This is also called toggeling a pin.
		// PORTB ^= (1<<5);
		
		// After reading the Datasheet in preperation for the ZOL version of this program, I discovered that toggling 
		// a pin can be achieved by writing a 1 to the corresponding bit in the PINx register.
		PINB |= (1<<5); 

		// Waiting 500ms, imagine it as the `delay()` function of an Arduino Program.
		_delay_ms(500);
	}
}