#include "io/digital.h"
#include "time/ctc_timer.h"
#include "util/task.h"
#include "zol/chrono.h"

int main() {
	zol::chrono::time_t timestamp = zol::chrono::get_millis();
	zol::chrono::time_t current =
		0;	  // get_millis is redundant here, it will get initialized properly
			  // as the first instruction in the while loop
	constexpr zol::chrono::time_t duration = 500;

	const auto task = [&]() {
		timestamp = current;
		digitalPin13::toggle();
	};
	const auto condition = [&]() -> bool {
		return current - timestamp > duration;
	};

	Task first{ [&]() { current = zol::chrono::get_millis(); } };
	ConditionalTask t{ condition, task };

	/// Initialize HW
	digitalPin13::output();
	zol::chrono::setup();
	sei();

	TaskScheduler{ first, t };
}