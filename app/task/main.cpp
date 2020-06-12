#include "io/digital.h"
#include "time/ctc_timer.h"
#include "util/task.h"
#include "zol/chrono.h"

int main() {
	// zol::chrono::time_t delta	  = 500;
	// zol::chrono::time_t timestamp = 0;
	// zol::chrono::time_t current	  = 0;

	// Task toggle{ [&]() {
	// 	current = zol::chrono::get_millis();
	// 	if (current - timestamp > delta) {
	// 		timestamp = current;
	// 		digitalPin13::toggle();
	// 	}
	// } };

	TimedTask toggle{ 500, []() { digitalPin13::toggle(); } };

	/// Initialize HW
	digitalPin13::output();
	zol::chrono::setup();
	sei();

	TimedTaskScheduler{ toggle };
}