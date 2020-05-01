#include "CTC_Timer.h"

template<>
CTC_Timer<0, uint8_t>::CTC_Timer() : 
	OCRB{*(volatile uint8_t *)(&OCR0B)},
	OCRA{*(volatile uint8_t *)(&OCR0A)},
	TCNT{*(volatile uint8_t *)(&TCNT0)},
	TCCRB{*(volatile uint8_t *)(&TCCR0B)},
	TCCRA{*(volatile uint8_t *)(&TCCR0A)},
	TIMSK{*(volatile uint8_t *)(&TIMSK0)} {	}

template<>
void CTC_Timer<0, uint8_t>::ctc_100us() {
	TCCRA = (2<<WGM00);
	TCCRB = (3<<CS00);
	OCR0A = 24;
	TIMSK = (1<<OCIE0A);
}

template<>
void CTC_Timer<0, uint8_t>::ctc_1ms() {
	TCCRA = (2<<WGM00);
	TCCRB = (3<<CS00);
	OCR0A = 249;
	TIMSK = (1<<OCIE0A);
}

template<>
void CTC_Timer<0, uint8_t>::ctc_2ms() {
	TCCRA = (2<<WGM00);
	TCCRB = (4<<CS00);
	OCR0A = 124;
	TIMSK = (1<<OCIE0A);
}

template<>
void CTC_Timer<0, uint8_t>::ctc_4ms() {
	TCCRA = (2<<WGM00);
	TCCRB = (4<<CS00);
	OCR0A = 249;
	TIMSK = (1<<OCIE0A);
}

template<>
void CTC_Timer<0, uint8_t>::ctc_8ms() {
	TCCRA = (2<<WGM00);
	TCCRB = (5<<CS00);
	OCR0A = 124;
	TIMSK = (1<<OCIE0A);
}

template<>
void CTC_Timer<0, uint8_t>::ctc_16ms() {
	TCCRA = (2<<WGM00);
	TCCRB = (5<<CS00);
	OCR0A = 249;
	TIMSK = (1<<OCIE0A);
}