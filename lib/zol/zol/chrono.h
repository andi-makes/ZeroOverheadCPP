#pragma once

#include "time/ctc_timer.h"

#include <avr/interrupt.h>
#include <inttypes.h>

namespace zol {
	template<typename timer_t>
	class chrono_def {
	public:
		using time_t = uint32_t;
		static volatile time_t millis;

		static time_t get_millis() { return millis; }
		static void setup() { timer_t::setup(3, 249); }
	};

#if defined(CHRONO_CTC1)
	using chrono = chrono_def<ctc_timer1>;
#elif defined(CHRONO_CTC2)
	using chrono = chrono_def<ctc_timer2>;
#else
	using chrono = chrono_def<ctc_timer0>;
#endif

	template<>
	volatile chrono::time_t chrono::millis = 0;
}

ISR(TIMER0_COMPA_vect) {
	zol::chrono::millis = zol::chrono::millis + 1;
}