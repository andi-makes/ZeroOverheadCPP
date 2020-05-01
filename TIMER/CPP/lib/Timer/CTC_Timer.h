#pragma once

#include <inttypes.h>
#include <avr/io.h>

template<int number, typename register_width>
class CTC_Timer {
private:
	volatile register_width& OCRB;
	volatile register_width& OCRA;
	volatile register_width& TCNT;
	volatile register_width& TCCRB;
	volatile register_width& TCCRA;

	volatile register_width& TIMSK;
public:
	void ctc_100us();
	void ctc_1ms();
	void ctc_2ms();
	void ctc_4ms();
	void ctc_8ms();
	void ctc_16ms();

	CTC_Timer();
};

#define ctc_timer0 CTC_Timer<0, uint8_t>{}
#define ctc_timer1 CTC_Timer<1, uint16_t>{}
#define ctc_timer2 CTC_Timer<2, uint8_t>{}
