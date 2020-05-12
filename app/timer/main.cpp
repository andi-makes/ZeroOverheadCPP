// The function `loop` gets tied to the `ctc_timer0_isr`
#define ZOL_USE_TIMER0_LOOP

#include "zol/zol.h"


void setup() {
	// initializes timer0 to provide a 1ms timer interrupt
	ctc_timer0_1ms;
	digitalPin13.output();
}

void loop() {
	static int i = 0;
	++i;
	if (i >= 500) {
		i = 0;
		digitalPin13.toggle();
	}
}