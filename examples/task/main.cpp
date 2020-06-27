#include "io/digital.h"
#include "tasks/task.h"
#include "time/ctc_timer.h"
#include "zol/chrono.h"


template<typename task_t>
void local_execute(zol::chrono::time_t current, TimedTask<task_t> t) {
	t.execute(current);
}

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

	// Does not work
	// TimedTaskScheduler{ toggle };

	// Works
	// while (true) {
	// 	zol::chrono::time_t current = zol::chrono::get_millis();
	// 	toggle.execute(current);
	// }

	// Does not work
	// while (true) {
	// 	zol::chrono::time_t current = zol::chrono::get_millis();
	// 	execute(current, toggle);
	// }

	while (true) {
		zol::chrono::time_t current = zol::chrono::get_millis();
		local_execute(current, toggle);
	}
}