#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER0_COMPA_vect) {
	static int count = 0;
	++count;
	if (count >= 500) {
		count = 0;
		PINB |= (1<<5);
	}
}

int main() {
	DDRB |= (1<<5);

	TCCR0A |= (2<<WGM00);
	TCCR0B |= (3<<CS00);
	OCR0A = 249;
	TIMSK0 |= (1<<OCIE0A);
	sei();
	
	while (1) { };
}