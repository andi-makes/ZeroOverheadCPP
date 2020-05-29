#include <util/delay.h>
#include <zol/zol.h>

void setup() {
	Register<uint8_t>{ DDRB }.set_bit(5);
}

void loop() {
	Register<uint8_t>{ PINB }.set_bit(5);
	_delay_ms(500);
}
