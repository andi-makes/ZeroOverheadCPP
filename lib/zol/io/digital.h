#pragma once
#include <avr/io.h>
#include <inttypes.h>

class DigitalPin {
private:
	const uint8_t BIT_NUMBER;
	volatile uint8_t& PORT;
	volatile uint8_t& DDR;
	volatile uint8_t& PIN;

public:
	// Defining a Pin as:
	inline void output() { DDR |= (1 << BIT_NUMBER); }

	inline void input() {
		DDR &= ~(1 << BIT_NUMBER);
		PORT &= ~(1 << BIT_NUMBER);
	}

	inline void pull_up() {
		DDR &= ~(1 << BIT_NUMBER);
		PORT |= (1 << BIT_NUMBER);
	}

	// Setting a Pin:
	inline void high() { PORT |= (1 << BIT_NUMBER); }
	inline void low() { PORT &= ~(1 << BIT_NUMBER); }
	inline void toggle() { PIN |= (1 << BIT_NUMBER); }

	// Read:
	inline bool is_high() const { return (PIN & (1 << BIT_NUMBER)); }
	inline bool is_low() const { return !(PIN & (1 << BIT_NUMBER)); }

	// Getting Pin Information
	inline volatile uint8_t& get_port() { return PORT; }
	inline volatile uint8_t& get_ddr() { return DDR; }
	inline volatile uint8_t& get_pin() { return PIN; }
	inline uint8_t get_bit_number() const { return BIT_NUMBER; }

	DigitalPin(volatile uint8_t& port, uint8_t bit_number) :
		BIT_NUMBER{ bit_number }, PORT{ *(volatile uint8_t*) (&port) },
		DDR{ *(volatile uint8_t*) (&port - 1) },	// TODO: Fix Pin Alignment
		PIN{ *(volatile uint8_t*) (&port - 2) } {}
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
#define digitalPin13 	DigitalPin{ PORTB, 5 }

#define digitalPinA0 	DigitalPin{ PORTC, 0 }
#define digitalPinA1 	DigitalPin{ PORTC, 1 }
#define digitalPinA2 	DigitalPin{ PORTC, 2 }
#define digitalPinA3 	DigitalPin{ PORTC, 3 }
#define digitalPinA4 	DigitalPin{ PORTC, 4 }
#define digitalPinA5 	DigitalPin{ PORTC, 5 }

#define digitalPinRESET DigitalPin{ PORTC, 6 }
