#include "zol/zol.hpp"

#include <avr/io.h>
#include <util/delay.h>

int main() {
	Register<uint8_t>{DDRB}.set_bit(5);

	while (true) {
		Register<uint8_t>{PINB}.set_bit(5);
		_delay_ms(500);
	}
}
