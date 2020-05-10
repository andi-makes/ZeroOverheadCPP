#pragma once

#include "ctc_timer.h"

enum timer_modes : uint8_t {
	ctc,
	normal,
	pwm_fast,
	pwm_phase
};

enum timer_prescalers : uint8_t {

};

enum timer_ocras : uint8_t {
	A,
	B,
	C
};

template<typename type_t, uint8_t number>
class timer {
	void set_mode(const timer_modes& mode) {
		if (number == 1) { // TODO: constexpr
			// Timer 1
		} else if (number == 0 || number == 2) { // TODO: constexpr
			// Timer 0 and Timer 1 behave identically
		}
	}
	void set_prescaler(timer_prescalers);
	void set_ocr(timer_ocras ocr, type_t value);

	timer();
};