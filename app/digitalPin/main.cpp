#include "zol.h"

#include <util/delay.h>

void setup() {
	digitalPin13::output();
}

void loop() {
	digitalPin13::toggle();
	_delay_ms(500);
}
