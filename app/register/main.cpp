#include "zol.h"

#include <util/delay.h>

void setup() {
	Register<uint8_t, 0x24>{}.set_bit(5);
}

void loop() {
	Register<uint8_t, 0x23>{}.set_bit(5);
	_delay_ms(500);
}
