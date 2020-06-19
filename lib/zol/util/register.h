#pragma once

/// @brief Static Register Wrapper class
/// @tparam type ... Representative type of the register, for example uint8_t
/// 	for 8 bit registers and uin16_t for 16 bit registers
/// @tparam address ... Address of the register
template<typename type, int address>
class Register {
public:
	/// @brief Type of the register
	using type_t = type;

	/// @brief Get the address of the register
	/// @return The Address of the register
	constexpr static int get_address() { return address; }

	/// @brief Get the register
	/// @return The register
	inline static volatile type& get_reg() {
		return *reinterpret_cast<volatile type_t*>(address);
	}

	/// @brief Sets the `bit_number`th bit in the register.
	/// @param bit_number ... Bit to set
	inline static void set_bit(const int bit_number) {
		get_reg() = get_reg() | (1 << bit_number);
	}

	/// @brief Gets the `bit_number`th bit from the register.
	/// @param bit_number ... Bit to get
	/// @return true if bit is set, otherwise false
	inline static bool get_bit(const int bit_number) {
		if (get_reg() & (1 << bit_number) == 0) {
			return false;
		} else {
			return true;
		}
	}

	/// @brief Clears the `bit_number`th bit in the register.
	/// @param bit_number ... Bit to clear
	inline static void clear_bit(const int bit_number) {
		get_reg() = get_reg() & ~(1 << bit_number);
	}

	/// @brief Toggles the `bit_number`th bit in the register.
	/// @param bit_number ... Bit to toggle
	inline static void toggle_bit(const int bit_number) {
		get_reg() = get_reg() ^ (1 << bit_number);
	}

	/// @brief Sets the register to `content`.
	/// @param content ... The new value of the register.
	inline static void set_reg(const type content) { get_reg() = content; }

	/// @brief Sets the register to 0.
	inline static void clear_reg() { get_reg() = 0; }

	/// @brief Ors the register with `bitmask`.
	/// @param bitmask ... It's a bitmask, duh.
	inline static void or_reg(const type bitmask) {
		get_reg() = get_reg() | bitmask;
	}

	/// @brief Ands the register with `bitmask`.
	/// @param bitmask ... It's a bitmask, duh
	inline static void and_reg(const type bitmask) {
		get_reg() = get_reg() & bitmask;
	}

	/// @brief Toggles (XOrs) the register with `bitmask`.
	/// @param bitmask ... It's a bitmask, duh
	inline static void toggle_reg(const type bitmask) {
		get_reg() = get_reg() ^ bitmask;
	}

private:
	Register();
};
