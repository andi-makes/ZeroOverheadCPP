#pragma once

#include <assert.h>

template<typename task_t, typename condition_t>
class Task {
public:
	task_t task;
	condition_t condition;

	bool execute() const {
		if (condition()) {
			task();
			return true;
		}
		return false;
	}

	Task(task_t task, condition_t condition) :
		task(task), condition(condition) {}
};

template<typename task_t>
bool execute(task_t t) {
	return t->execute();
}