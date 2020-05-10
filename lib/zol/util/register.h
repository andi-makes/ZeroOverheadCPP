#pragma once

template<typename type>
class Register {
public:
	volatile type& reg;

	inline void set_bit(const int bit_number) {
		reg |= (1 << bit_number);
	}
	inline void clear_bit(const int bit_number) {
		reg &= ~(1 << bit_number);
	}
	inline void toggle_bit(const int bit_number) {
		reg ^= (1 << bit_number);
	}

	inline void set_reg(const type content) {
		reg = content;
	}
	inline void clear_reg() {
		reg = 0;
	}
	inline void or_reg(const type content) {
		reg |= content;
	}
	inline void and_reg(const type content) {
		reg &= content;
	}
	inline void toggle_reg(const type content) {
		reg ^= content;
	}

	Register(volatile type& address) : 
		reg{*(volatile type *)(&address)} { }
};