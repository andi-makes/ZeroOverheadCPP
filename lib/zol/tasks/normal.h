#pragma once

/// @brief Simple task, gets executed every time
///
/// @tparam task_t ... Type of the task, expect function with return type void
/// and no parameters
template<typename task_t>
class Task {
private:
	const task_t task;

public:
	/// @brief This type of Task does not need information about time
	static constexpr bool needsTime = false;

	/// @brief Executes the task
	/// @return Always returns false
	bool execute() const {
		task();
		return false;
	}

	Task(const task_t& task) : task(task) {}
};
