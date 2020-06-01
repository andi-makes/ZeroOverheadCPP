#pragma once

#include "../util/register.h"

#include <avr/io.h>
namespace zol {
	template<typename type_t, int number>
	class CTC_Timer {
		// volatile uint8_t& TCCRA;
		// volatile uint8_t& TCCRB;
		// volatile type_t& OCRA;
		// volatile type_t& TCNT;
		// volatile uint8_t& TIMSK;

		using TCCRA =
			Register<uint8_t, number == 0 ? 0x44 : number == 1 ? 0x80 : 0xB0>;
		using TCCRB = Register<uint8_t, TCCRA::get_address() + 1>;
		using OCRA =
			Register<type_t, number == 0 ? 0x47 : number == 1 ? 0x88 : 0xB3>;
		using TIMSK =
			Register<uint8_t, number == 0 ? 0x6E : number == 1 ? 0x6F : 0x70>;

	public:
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

		inline static void enable_interrupt() { TIMSK::set_reg(1 << OCIE0A); }
		inline static void disable_interrupt() { TIMSK::clear_reg(); }

	private:
		CTC_Timer() {}
	};
	using ctc_timer0 = CTC_Timer<uint8_t, 0>;
	using ctc_timer1 = CTC_Timer<uint16_t, 1>;
	using ctc_timer2 = CTC_Timer<uint8_t, 2>;
}

// #define ctc_timer0_100us    ctc_timer0::setup(3, 24)
// #define ctc_timer0_500us    ctc_timer0::setup(3, 124)
// #define ctc_timer0_1ms    	ctc_timer0::setup(3, 249)
// #define ctc_timer0_2ms      ctc_timer0::setup(4, 124)
// #define ctc_timer0_4ms      ctc_timer0::setup(4, 249)

// #define ctc_timer1_100us    ctc_timer1::setup(3, 24)
// #define ctc_timer1_500us    ctc_timer1::setup(3, 124)
// #define ctc_timer1_1ms    	ctc_timer1::setup(3, 249)
// #define ctc_timer1_2ms      ctc_timer1::setup(4, 124)
// #define ctc_timer1_4ms      ctc_timer1::setup(4, 249)

// #define ctc_timer2_100us    ctc_timer2::setup(3, 24)
// #define ctc_timer2_500us    ctc_timer2::setup(3, 124)
// #define ctc_timer2_1ms    	ctc_timer2::setup(3, 249)
// #define ctc_timer2_2ms      ctc_timer2::setup(4, 124)
// #define ctc_timer2_4ms      ctc_timer2::setup(4, 249)

#define ctc_timer0_isr TIMER0_COMPA_vect
#define ctc_timer1_isr TIMER1_COMPA_vect
#define ctc_timer2_isr TIMER2_COMPA_vect