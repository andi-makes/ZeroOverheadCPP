#pragma once

#include <avr/io.h>

template<typename type_t, int number>
class CTC_Timer {
	volatile uint8_t &TCCRA;
	volatile uint8_t &TCCRB;
	volatile type_t &OCRA;
	volatile uint8_t &TIMSK;

public:
	void setup(int prescaler, int ocra) {
		if constexpr (number==1) {
			TCCRA &= ~(0b11 << WGM10);
			TCCRB |= (1 << WGM12) | (prescaler << CS10);
		} else {
			TCCRA |= (2 << WGM00);
			TCCRB |= (prescaler << CS00);
		}
		OCRA = ocra;
		enable_interrupt();
	}

	void enable_interrupt() {
		TIMSK |= (1 << OCIE0A);
	}
	void disable_interrupt() {
		TIMSK &= ~(1 << OCIE0A);
	}

	CTC_Timer()
		: TCCRA{*(volatile uint8_t *)(number==0
									  ? &TCCR0A
									  : number==1 ? &TCCR1A : &TCCR2A)},
		  TCCRB{*(volatile uint8_t *)(&TCCRA + 1)},
		  OCRA{*(volatile type_t *)(number==0
									? &OCR0A
									: number==1 ? &OCR1AL : &OCR2A)},
		  TIMSK{*(volatile type_t *)(number==0
									 ? &TIMSK0
									 : number==1 ? &TIMSK1 : &TIMSK2)} { }
};

#define ctc_timer0 CTC_Timer<uint8_t, 0>{}
#define ctc_timer1 CTC_Timer<uint16_t, 1>{}
#define ctc_timer2 CTC_Timer<uint8_t, 2>{}

#define ctc_timer0_isr TIMER0_COMPA_vect