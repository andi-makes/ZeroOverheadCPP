#pragma once
#include "../util/register.h"

#include <avr/io.h>
#include <inttypes.h>

template<int address, int bit_number>
class DigitalPin {
private:
public:
	using PORT = Register<uint8_t, address>;
	using DDR  = Register<uint8_t, address - 1>;
	using PIN  = Register<uint8_t, address - 2>;

	// Defining a Pin as:
	inline void output() { DDR::set_bit(bit_number); }

	inline void input() {
		DDR::clear_bit(bit_number);
		PORT::clear_bit(bit_number);
	}

	inline void pull_up() {
		DDR::clear_bit(bit_number);
		PORT::set_bit(bit_number);
	}

	// Setting a Pin:
	inline void high() { PORT::set_bit(bit_number); }
	inline void low() { PORT::clear_bit(bit_number); }
	inline void toggle() { PIN::set_bit(bit_number); }

	// Read:
	inline bool is_high() const { return PIN::get_bit(bit_number); }
	inline bool is_low() const { return !PIN::get_bit(bit_number); }

	DigitalPin() {}
};

// clang-format off
#define digitalPin0 	DigitalPin{ PORTD, 0 }
#define digitalPin1 	DigitalPin{ PORTD, 1 }
#define digitalPin2 	DigitalPin{ PORTD, 2 }
#define digitalPin3 	DigitalPin{ PORTD, 3 }
#define digitalPin4 	DigitalPin{ PORTD, 4 }
#define digitalPin5 	DigitalPin{ PORTD, 5 }
#define digitalPin6 	DigitalPin{ PORTD, 6 }
#define digitalPin7 	DigitalPin{ PORTD, 7 }
#define digitalPin8 	DigitalPin{ PORTB, 0 }
#define digitalPin9 	DigitalPin{ PORTB, 1 }
#define digitalPin10 	DigitalPin{ PORTB, 2 }
#define digitalPin11 	DigitalPin{ PORTB, 3 }
#define digitalPin12 	DigitalPin{ PORTB, 4 }
#define digitalPin13 	DigitalPin<0x25, 5>{}

#define digitalPinA0 	DigitalPin{ PORTC, 0 }
#define digitalPinA1 	DigitalPin{ PORTC, 1 }
#define digitalPinA2 	DigitalPin{ PORTC, 2 }
#define digitalPinA3 	DigitalPin{ PORTC, 3 }
#define digitalPinA4 	DigitalPin{ PORTC, 4 }
#define digitalPinA5 	DigitalPin{ PORTC, 5 }

#define digitalPinRESET DigitalPin{ PORTC, 6 }
