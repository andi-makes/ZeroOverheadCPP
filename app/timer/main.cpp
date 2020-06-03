#include "zol.h"

ISR(TIMER0_COMPA_vect) {
	static int i = 0;
	++i;
	if (i >= 500) {
		i = 0;
		digitalPin13::toggle();
	}
}

void setup() {
	// initializes timer0 to provide a 1ms timer interrupt
	zol::ctc_timer0::setup(3, 249);
	digitalPin13::output();
}

void loop() {}
