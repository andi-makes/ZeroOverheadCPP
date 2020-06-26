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
		static void setup() {
			if constexpr (timer_t::timer_number == 0) {
				timer_t::setup(3, 249);
			} else if constexpr (timer_t::timer_number == 1) {
			} else {
			}
		}
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

#if defined(ZOL_CHRONO_IMPL)
#include "./chrono.cpp"
#endif