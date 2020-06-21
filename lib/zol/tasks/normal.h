#pragma once

template<typename task_t>
class Task {
private:
	const task_t task;

public:
	static constexpr bool needsTime = false;

	bool execute() const {
		task();
		return false;
	}

	Task(const task_t& task) : task(task) {}
};
