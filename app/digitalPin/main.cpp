#include <util/delay.h>
#include "zol/zol.hpp"

int main() {
	digitalPin13.output();

	while (true) {
		digitalPin13.toggle();
		_delay_ms(500);
	}
}
