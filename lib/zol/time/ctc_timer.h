#pragma once

#include <avr/io.h>

template<typename type_t, int number>
class CTC_Timer {
	volatile uint8_t &TCCRA;
	volatile uint8_t &TCCRB;
	volatile type_t &OCRA;
	volatile type_t &TCNT;
	volatile uint8_t &TIMSK;

public:
	void setup(const int prescaler, const int ocra) {
		if constexpr (number==1) {
			TCCRA = 0;
			TCCRB = (1 << WGM12) | (prescaler << CS10);
		} else {
			TCCRA = (2 << WGM00);
			TCCRB = (prescaler << CS00);
		}
		OCRA = ocra;
		enable_interrupt();
	}

	void enable_interrupt() {
		TIMSK = (1 << OCIE0A);
	}
	void disable_interrupt() {
		TIMSK = 0;
	}

	CTC_Timer()
		: TCCRA{*(volatile uint8_t *)(number==0
									  ? &TCCR0A
									  : number==1 ? &TCCR1A : &TCCR2A)},
		  TCCRB{*(volatile uint8_t *)(&TCCRA + 1)},
		  OCRA{*(volatile type_t *)(number==0
									? &OCR0A
									: number==1 ? &OCR1AL : &OCR2A)},
		  TCNT{*(volatile type_t *)(number==0
									? &TCNT0
									: number==1 ? &TCNT1L : &TCNT2)},
		  TIMSK{*(volatile uint8_t *)(number==0
									  ? &TIMSK0
									  : number==1 ? &TIMSK1 : &TIMSK2)} { }
};

#define ctc_timer0 CTC_Timer<uint8_t, 0>{}
#define ctc_timer1 CTC_Timer<uint16_t, 1>{}
#define ctc_timer2 CTC_Timer<uint8_t, 2>{}

#define ctc_timer0_100us    ctc_timer0.setup(3, 24)
#define ctc_timer0_500us    ctc_timer0.setup(3, 124)
#define ctc_timer0_1ms    	ctc_timer0.setup(3, 249)
#define ctc_timer0_2ms      ctc_timer0.setup(4, 124)
#define ctc_timer0_4ms      ctc_timer0.setup(4, 249)

#define ctc_timer1_100us    ctc_timer1.setup(3, 24)
#define ctc_timer1_500us    ctc_timer1.setup(3, 124)
#define ctc_timer1_1ms    	ctc_timer1.setup(3, 249)
#define ctc_timer1_2ms      ctc_timer1.setup(4, 124)
#define ctc_timer1_4ms      ctc_timer1.setup(4, 249)

#define ctc_timer2_100us    ctc_timer2.setup(3, 24)
#define ctc_timer2_500us    ctc_timer2.setup(3, 124)
#define ctc_timer2_1ms    	ctc_timer2.setup(3, 249)
#define ctc_timer2_2ms      ctc_timer2.setup(4, 124)
#define ctc_timer2_4ms      ctc_timer2.setup(4, 249)

#define ctc_timer0_isr TIMER0_COMPA_vect
#define ctc_timer1_isr TIMER1_COMPA_vect
#define ctc_timer2_isr TIMER2_COMPA_vect