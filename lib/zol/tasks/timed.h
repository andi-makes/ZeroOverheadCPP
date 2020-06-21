#pragma once

#include "zol/chrono.h"

template<typename task_t>
class TimedTask {
	const zol::chrono::time_t delta;
	const task_t task;
	// zol::chrono::time_t timestamp;

	/// The story why I cannot make timestamp a private member variable:
	/// Well, the compiler simply does not want to compile `timestamp = current`
	/// in the if statement in execute. If I make the timestamp a static
	/// variable inside that function, it does work however. Making the variable
	/// static has the drawback that when using few TimedTasks the timestamp
	/// does not simply get stored inside a register but in RAM. Using static
	/// variables greatly impact code size and thus code speed, so I wouldn't
	/// recommend using this type of Task. See app/custom_timed_task for further
	/// detail.

public:
	static constexpr bool needsTime = true;

	bool execute(const zol::chrono::time_t& current) {
		static zol::chrono::time_t timestamp = zol::chrono::get_millis();
		const zol::chrono::time_t deltaTime	 = current - timestamp;
		if (deltaTime > delta) {
			timestamp = current;
			task();
			return true;
		}
		return false;
	}

	TimedTask(const zol::chrono::time_t& delta, const task_t& task) :
		delta(delta), task(task) {
		// timestamp = zol::chrono::get_millis();
	}
};