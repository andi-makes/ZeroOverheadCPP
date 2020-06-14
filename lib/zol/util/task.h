#pragma once

#include "zol/chrono.h"

template<typename task_t>
class Task {
private:
	const task_t task;

public:
	bool execute(zol::chrono::time_t current) const {
		task();
		return false;
	}

	Task(const task_t& task) : task(task) {}
};

template<typename task_t, typename condition_t>
class ConditionalTask {
private:
	task_t task;
	condition_t condition;

public:
	bool execute(zol::chrono::time_t current) {
		if (condition()) {
			task();
			return true;
		}
		return false;
	}

	ConditionalTask(condition_t condition, task_t task) :
		task(task), condition(condition) {}
};

template<typename task_t>
class TimedTask {
	zol::chrono::time_t delta_;
	task_t task;
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
	bool execute(zol::chrono::time_t current) {
		static zol::chrono::time_t timestamp = zol::chrono::get_millis();
		if (current - timestamp > delta_) {
			timestamp = current;
			task();
			return true;
		}
		return false;
	}

	[[deprecated(
		"I don't recommend using this type of Task. See "
		"app/custom_timed_task for further detail!")]] TimedTask(zol::chrono::
																	 time_t
																		 delta,
																 task_t task) :
		delta_(delta),
		task(task) {
		// timestamp = zol::chrono::get_millis();
	}
};

/// @brief 0th case for variadic template
/// @return Always returns false, no task was executed
bool execute(zol::chrono::time_t current) {
	return false;
}

template<typename T, typename... tasks_t>
bool execute(zol::chrono::time_t current, T t, tasks_t... other) {
	if (t.execute(current)) {
		return true;
	}
	return execute(current, other...);
}

template<typename... tasks_t>
class SimpleTaskScheduler {
public:
	SimpleTaskScheduler(tasks_t... tasks) {
		while (true) {
			execute(0, tasks...);
		}
	}
};

template<typename... task_ts>
class TimedTaskScheduler {
public:
	TimedTaskScheduler(task_ts... tasks) {
		zol::chrono::time_t current = 0;
		while (true) {
			current = zol::chrono::get_millis();
			execute(current, tasks...);
		}
	}
};