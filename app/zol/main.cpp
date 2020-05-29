#include "zol/zol.h"

#include <util/delay.h>

ISR(TIMER0_COMPA_vect) {
	static int i = 0;
	++i;
	if (i >= 500) {
		i = 0;
		digitalPin13.toggle();
	}
}

void setup() {
	digitalPin13.output();
	ctc_timer0.setup(3, 249);
}

void loop() {}
