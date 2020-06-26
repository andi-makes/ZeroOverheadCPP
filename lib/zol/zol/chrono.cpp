#include "./chrono.h"

#if defined(CHRONO_CTC1)
ISR(TIMER1_COMPA_vect) {
	zol::chrono::millis = zol::chrono::millis + 1;
}
#elif defined(CHRONO_CTC2)
ISR(TIMER2_COMPA_vect) {
	zol::chrono::millis = zol::chrono::millis + 1;
}
#else
ISR(TIMER0_COMPA_vect) {
	zol::chrono::millis = zol::chrono::millis + 1;
}
#endif