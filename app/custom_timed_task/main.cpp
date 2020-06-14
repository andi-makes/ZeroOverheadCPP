/// Long story short: This version does the same as just using TimedTask,
/// but it is 72 Bytes smaller. I cannot abstract this into a class because
/// of a compiler bug.

#include "io/digital.h"
#include "time/ctc_timer.h"
#include "util/task.h"
#include "zol/chrono.h"

int main() {
	constexpr zol::chrono::time_t delta = 500;
	zol::chrono::time_t timestamp		= 0;
	zol::chrono::time_t current			= 0;

	Task toggle{ [&]() {
		current = zol::chrono::get_millis();
		if (current - timestamp > delta) {
			timestamp = current;
			digitalPin13::toggle();
		}
	} };

	/// Initialize HW
	digitalPin13::output();
	zol::chrono::setup();
	sei();

	SimpleTaskScheduler{ toggle };
}