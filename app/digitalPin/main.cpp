#include <util/delay.h>
#include "zol/zol.h"

void setup() {
	digitalPin13.output();
}

void loop() {
	digitalPin13.toggle();
	_delay_ms(500);
}
