#pragma once

#include "zol/chrono.h"

template<typename task_t>
class Task {
private:
	const task_t task;

public:
	bool execute() const {
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
	bool execute() {
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
private:
	task_t t;
	int32_t delta; // Make me a template as well please
	int32_t timestamp;
public:
	bool execute() {
		if (zol::chrono::get_millis() - timestamp > delta) {
			t();
			return true;
		}
		return false;
	}

	TimedTask(int32_t delta, task_t task) : t(task), delta(delta) {
		timestamp = zol::chrono::get_millis();
	}
};

/// @brief 0th case for variadic template
/// @return Always returns false, no task was executed
bool execute() {
	return false;
}

template<typename T, typename... tasks_t>
bool execute(T t, tasks_t... other) {
	if (t.execute()) {
		return true;
	}
	return execute(other...);
}

template<typename... tasks_t>
class TaskScheduler {
public:
	TaskScheduler(tasks_t... tasks) {
		while (true) {
			execute(tasks...);
		}
	}
};