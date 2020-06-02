#include <avr/interrupt.h>
#include <avr/io.h>
#include <inttypes.h>

volatile int32_t millis = 0;

ISR(TIMER0_COMPA_vect) {
	millis += 1;
}

int32_t get_millis() {
	return millis;
}

int main() {
	TCCR0A = (2 << WGM00);
	TCCR0B = 3;
	OCR0A  = 249;
	TIMSK0 = (1 << OCIE0A);

	DDRB |= (1 << 5);

	sei();

	int32_t timestamp = get_millis();
	while (1) {
		int32_t current = get_millis();
		if (current - timestamp > 500) {
			timestamp = current;
			PINB |= (1 << 5);
		}
	}
}