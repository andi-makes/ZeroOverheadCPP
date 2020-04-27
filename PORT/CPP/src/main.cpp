#include <util/delay.h>
#include <DigitalPin.h>

int main() {
	digitalPin13.output();

	while (true) {
		digitalPin13.toggle();
		_delay_ms(500);
	}
}
