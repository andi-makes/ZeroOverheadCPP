#include <util/delay.h>

#include <zol.h>

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
	ctc_timer0.ctc_1ms();
}

void loop() {

}
