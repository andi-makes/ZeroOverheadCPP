#pragma once

/// @brief This Task only gets executed when the condition function returns
/// true. After executing, the task queue starts over again.
/// @tparam task_t ... Type of the task, expect function with return type void
/// and no parameters
/// @tparam condition_t ... Type of the condition, expect function with return
/// type bool and no parameters
template<typename task_t, typename condition_t>
class ConditionalTask {
private:
	const task_t task;
	const condition_t condition;

public:
	/// @brief This type of Task does not need information about time
	static constexpr bool needsTime = false;

	/// @brief Executes the task if the condition is met, terminates the task
	/// queue
	/// @return true if executed, otherwise false
	bool execute() const {
		if (condition()) {
			task();
			return true;
		}
		return false;
	}

	ConditionalTask(const condition_t& condition, const task_t& task) :
		task(task), condition(condition) {}
};