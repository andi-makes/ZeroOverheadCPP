#pragma once

#include "util/register.h"

#include <avr/io.h>

namespace zol {
	/// @brief Wrapper for the Counter Timer Compare features of the Timers
	/// @tparam type_t ... Type of the large registers of the Timer
	/// @tparam number ... Number of the Timer
	template<typename type_t, int number>
	class CTC_Timer {
		using TCCRA =
			Register<uint8_t, number == 0 ? 0x44 : number == 1 ? 0x80 : 0xB0>;
		using TCCRB = Register<uint8_t, TCCRA::get_address() + 1>;
		using OCRA =
			Register<type_t, number == 0 ? 0x47 : number == 1 ? 0x88 : 0xB3>;
		using TIMSK =
			Register<uint8_t, number == 0 ? 0x6E : number == 1 ? 0x6F : 0x70>;

	public:
		/// @brief Initialize the Timer with a specific prescaler and compare
		/// 	value
		/// @param prescaler ... Prescaler to use // TODO: prescaler values
		/// @param ocra ... Compare value
		inline static void setup(const type_t prescaler, const type_t ocra) {
			if constexpr (number == 1) {
				TCCRA::clear_reg();
				TCCRB::set_reg((1 << WGM12) | (prescaler << CS10));
			} else {
				TCCRA::set_reg(2 << WGM00);
				TCCRB::set_reg(prescaler << CS00);
			}
			OCRA::set_reg(ocra);
			enable_interrupt();
		}

		/// @brief Enables the corresponding Timer Compare Interrupt Service
		/// Routine
		inline static void enable_interrupt() { TIMSK::set_reg(1 << OCIE0A); }

		/// @brief Disables the corresponding Timer Compare Interrupt Service
		/// Routine
		inline static void disable_interrupt() { TIMSK::clear_reg(); }

	private:
		CTC_Timer() {}
	};
	using ctc_timer0 = CTC_Timer<uint8_t, 0>;
	using ctc_timer1 = CTC_Timer<uint16_t, 1>;
	using ctc_timer2 = CTC_Timer<uint8_t, 2>;
}

#define ctc_timer0_isr TIMER0_COMPA_vect
#define ctc_timer1_isr TIMER1_COMPA_vect
#define ctc_timer2_isr TIMER2_COMPA_vect