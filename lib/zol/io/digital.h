#pragma once
#include "../util/register.h"

#include <inttypes.h>

/// @brief Provides Port manipulation
/// @tparam address ... Address of the PORT register
/// @tparam bit_number ... Which bit should be manipulated
template<int address, int bit_number>
class DigitalPin {
public:
	using PORT = Register<uint8_t, address>;
	using DDR  = Register<uint8_t, address - 1>;
	using PIN  = Register<uint8_t, address - 2>;

	// Defining a Pin as:
	/// @brief Defines the Pin as an output
	inline static void output() { DDR::set_bit(bit_number); }

	/// @brief Defines the Pin as an input
	inline static void input() {
		DDR::clear_bit(bit_number);
		PORT::clear_bit(bit_number);
	}

	/// @brief Defines the Pin as an input with pull-ups enabled
	inline static void pull_up() {
		DDR::clear_bit(bit_number);
		PORT::set_bit(bit_number);
	}

	// Setting a Pin:
	/// @brief Set the Pin high
	inline static void high() { PORT::set_bit(bit_number); }

	/// @brief Set the Pin low
	inline static void low() { PORT::clear_bit(bit_number); }

	/// @brief Toggles the state of the Pin
	inline static void toggle() { PIN::set_bit(bit_number); }

	// Read:
	/// @brief Checks whether the Pin is high or not
	/// @return true if Pin is high
	inline static bool is_high() { return PIN::get_bit(bit_number); }

	/// @brief Checks whether the Pin is low or not
	/// @return true if Pin is low
	inline static bool is_low() { return !PIN::get_bit(bit_number); }

private:
	DigitalPin() {}
};

// PORTD
using digitalPin0 = DigitalPin<0x2B, 0>;
using digitalPin1 = DigitalPin<0x2B, 1>;
using digitalPin2 = DigitalPin<0x2B, 2>;
using digitalPin3 = DigitalPin<0x2B, 3>;
using digitalPin4 = DigitalPin<0x2B, 4>;
using digitalPin5 = DigitalPin<0x2B, 5>;
using digitalPin6 = DigitalPin<0x2B, 6>;
using digitalPin7 = DigitalPin<0x2B, 7>;

// PORTB
using digitalPin8  = DigitalPin<0x25, 0>;
using digitalPin9  = DigitalPin<0x25, 1>;
using digitalPin10 = DigitalPin<0x25, 2>;
using digitalPin11 = DigitalPin<0x25, 3>;
using digitalPin12 = DigitalPin<0x25, 4>;
using digitalPin13 = DigitalPin<0x25, 5>;

// PORTC
using digitalPinA0	  = DigitalPin<0x28, 0>;
using digitalPinA1	  = DigitalPin<0x28, 1>;
using digitalPinA2	  = DigitalPin<0x28, 2>;
using digitalPinA3	  = DigitalPin<0x28, 3>;
using digitalPinA4	  = DigitalPin<0x28, 4>;
using digitalPinA5	  = DigitalPin<0x28, 5>;
using digitalPinRESET = DigitalPin<0x28, 6>;
