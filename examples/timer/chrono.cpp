#include "zol.h"

typedef int32_t time_t;

namespace {
	volatile time_t millis = 0;
}

ISR(TIMER0_COMPA_vect) {
	millis = millis + 1;
}

time_t get_millis() {
	return millis;
}

void setup() {
	// Prescaler: 64
	// One Timer-Tick: 4us
	// Interrupt Interval: 1ms
	zol::ctc_timer0::setup(3, 249);
	digitalPin13::output();

	sei();

	constexpr time_t delta_time = 500;
	time_t timestamp			= get_millis();
	while (true) {
		time_t current = get_millis();

		if (current - timestamp > delta_time) {
			timestamp = current;
			digitalPin13::toggle();
		}
	}
}

void loop() {}