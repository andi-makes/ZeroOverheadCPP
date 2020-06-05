#pragma once

#include <assert.h>

template<typename task_t, typename condition_t>
class Task {
public:
	task_t task;
	condition_t condition;

	Task(task_t task, condition_t condition) :
		task(task), condition(condition) {}
};

/// @brief 0th case for variadic template
/// @return Always returns false, no task was executed
bool execute() {
	return false;
}

template<typename T, typename... tasks_t>
bool execute(T t, tasks_t... other) {
	if (t.condition()) {
		t.task();
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