#include <avr/interrupt.h>
#include <avr/io.h>


ISR(TIMER0_COMPA_vect) {
	static int i = 0;
	++i;
	if (i >= 500) {
		i = 0;
		PINB |= (1 << 5);
	}
}

int main() {
	TCCR0A = (2 << WGM00);
	TCCR0B = (3 << CS00);
	OCR0A  = 249;
	TIMSK0 = (1 << OCIE0A);
	DDRB |= (1 << 5);

	sei();

	while (1) {
	}
}