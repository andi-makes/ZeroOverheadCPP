#include "io/digital.h"
#include "time/ctc_timer.h"
#include "util/task.h"

#include <avr/interrupt.h>

typedef int32_t time_t;

namespace {
	volatile time_t millis = 0;
}

ISR(TIMER0_COMPA_vect) {
	millis += 1;
}

time_t get_millis() {
	return millis;
}

int main() {
	uint32_t timestamp = get_millis();
	uint32_t current =
		0;	  // get_millis is redundant here, it will get initialized properly
			  // as the first instruction in the while loop
	constexpr uint32_t duration = 500;

	const auto task = [&]() {
		timestamp = current;
		digitalPin13::toggle();
	};
	const auto condition = [&]() -> bool {
		return current - timestamp > duration;
	};

	Task first{ []() {},
				[&]() {
					current = get_millis();
					return false;
				} };
	Task t{ task, condition };

	/// Initialize HW
	digitalPin13::output();
	zol::ctc_timer0::setup(3, 249);
	sei();

	TaskScheduler{ first, t };
}