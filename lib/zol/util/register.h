#pragma once

template<typename type, int address>
class Register {
public:
	/// @brief Sets the `bit_number`th bit in the register.
	/// @param bit_number ... Bit to set
	inline static void set_bit(const int bit_number) {
		*reinterpret_cast<volatile type*>(address) |= (1 << bit_number);
	}

	/// @brief Gets the `bit_number`th bit from the register.
	/// @param bit_number ... Bit to get
	/// @return true if bit is set, otherwise false
	inline static bool get_bit(const int bit_number) {
		return *reinterpret_cast<volatile type*>(address) &=
			   (1 << bit_number) == 0 ? false : true;
	}

	/// @brief Clears the `bit_number`th bit in the register.
	/// @param bit_number ... Bit to clear
	inline static void clear_bit(const int bit_number) {
		*reinterpret_cast<volatile type*>(address) &= ~(1 << bit_number);
	}

	/// @brief Toggles the `bit_number`th bit in the register.
	/// @param bit_number ... Bit to toggle
	inline static void toggle_bit(const int bit_number) {
		*reinterpret_cast<volatile type*>(address) ^= (1 << bit_number);
	}

	/// @brief Sets the register to `content`.
	/// @param content ... The new value of the register.
	inline static void set_reg(const type content) {
		*reinterpret_cast<volatile type*>(address) = content;
	}

	/// @brief Sets the register to 0.
	inline static void clear_reg() {
		*reinterpret_cast<volatile type*>(address) = 0;	   //
	}

	/// @brief Ors the register with `bitmask`.
	/// @param bitmask ... It's a bitmask, duh.
	inline static void or_reg(const type bitmask) {
		*reinterpret_cast<volatile type*>(address) |= bitmask;
	}

	/// @brief Ands the register with `bitmask`.
	/// @param bitmask ... It's a bitmask, duh
	inline static void and_reg(const type bitmask) {
		*reinterpret_cast<volatile type*>(address) &= bitmask;
	}

	/// @brief Toggles (XOrs) the register with `bitmask`.
	/// @param bitmask ... It's a bitmask, duh
	inline static void toggle_reg(const type bitmask) {
		*reinterpret_cast<volatile type*>(address) ^= bitmask;
	}

	constexpr static int get_address() { return address; }

private:
	Register();
};
