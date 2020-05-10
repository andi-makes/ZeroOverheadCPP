#include "zol/zol.h"

ISR(ctc_timer0_isr) {
	static int i = 0;
	++i;
	if (i >= 500) {
		i = 0;
		digitalPin13.toggle();
	}
}

int main() {
	ctc_timer0.setup(3, 249);
	digitalPin13.output();
	sei();

	while (true) { }
}