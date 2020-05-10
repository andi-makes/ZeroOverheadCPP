#include <util/delay.h>
#include "zol/zol.h"

int main() {
	digitalPin13.output();

	while (true) {
		digitalPin13.toggle();
		_delay_ms(500);
	}
}
