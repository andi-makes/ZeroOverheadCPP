#pragma once

template<typename type, int address>
class Register {
public:
	/// @brief Sets the `bit_number`th bit in the register.
	/// @param bit_number ... Bit to set
	inline void set_bit(const int bit_number) {
		*reinterpret_cast<volatile type*>(address) |= (1 << bit_number);
	}

	/// @brief Clears the `bit_number`th bit in the register.
	/// @param bit_number ... Bit to clear
	inline void clear_bit(const int bit_number) {
		*reinterpret_cast<volatile type*>(address) &= ~(1 << bit_number);
	}

	/// @brief Toggles the `bit_number`th bit in the register.
	/// @param bit_number ... Bit to toggle
	inline void toggle_bit(const int bit_number) {
		*reinterpret_cast<volatile type*>(address) ^= (1 << bit_number);
	}

	/// @brief Sets the register to `content`.
	/// @param content ... The new value of the register.
	inline void set_reg(const type content) {
		*reinterpret_cast<volatile type*>(address) = content;
	}

	/// @brief Sets the register to 0.
	inline void clear_reg() {
		*reinterpret_cast<volatile type*>(address) = 0;	   //
	}

	/// @brief Ors the register with `bitmask`.
	/// @param bitmask ... It's a bitmask, duh.
	inline void or_reg(const type bitmask) {
		*reinterpret_cast<volatile type*>(address) |= bitmask;
	}

	/// @brief Ands the register with `bitmask`.
	/// @param bitmask ... It's a bitmask, duh
	inline void and_reg(const type bitmask) {
		*reinterpret_cast<volatile type*>(address) &= bitmask;
	}

	/// @brief Toggles (XOrs) the register with `bitmask`.
	/// @param bitmask ... It's a bitmask, duh
	inline void toggle_reg(const type bitmask) {
		*reinterpret_cast<volatile type*>(address) ^= bitmask;
	}

	Register() {}
};
