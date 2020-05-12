#pragma once

#include "io/digitalPin.h"
#include "zol/timer/timer.h"
#include "util/register.h"

#include <avr/interrupt.h>

extern "C" {

void setup();
void loop();
int main();

}

// region implementation

#ifdef ZOL_USE_TIMER0_LOOP
#define ZOL_USE_TIMER_LOOP
ISR(ctc_timer0_isr) {
	loop();
}
#endif

int main() {
	setup();
	sei();

	while (true) {
#ifndef ZOL_USE_TIMER_LOOP
		loop();
#endif
	}
}

// endregion