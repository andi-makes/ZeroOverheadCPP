#pragma once

template<typename task_t, typename condition_t>
class ConditionalTask {
private:
	task_t task;
	condition_t condition;

public:
	static constexpr bool needsTime = false;
	bool execute() {
		if (condition()) {
			task();
			return true;
		}
		return false;
	}

	ConditionalTask(const condition_t& condition, const task_t& task) :
		task(task), condition(condition) {}
};