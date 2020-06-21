#pragma once

#include "zol/chrono.h"

/// @brief 0th case for variadic template
/// @param current ... current time, unused in this case
/// @return Always returns false, no task was executed
bool execute(__attribute__((unused)) const zol::chrono::time_t& current) {
	return false;
}

/// @brief Gives timed tasks the current time
/// @param current ... current time
/// @param t ... task to execute right now
/// @param other ... other tasks to execute later
/// @tparam T ... type of t
/// @tparam tasks_t ... types of other
/// @return returns true if a task was executed, false otherwise
template<typename T, typename... tasks_t>
bool execute(const zol::chrono::time_t& current,
			 const T& t,
			 const tasks_t&... other) {
	if constexpr (t.needsTime) {
		if (t.execute(current)) {
			return true;
		}
	} else {
		if (t.execute()) {
			return true;
		}
	}
	return execute(current, other...);
}

/// @brief 0th case for variadic template
/// @return Always returns false, no task was executed
bool execute() {
	return false;
}

/// @brief Gives timed tasks the current time
/// @param t ... task to execute right now
/// @param other ... other tasks to execute later
/// @tparam T ... type of t
/// @tparam tasks_t ... types of other
/// @return returns true if a task was executed, false otherwise
template<typename T, typename... tasks_t>
bool execute(const T& t, const tasks_t&... other) {
	if (t.execute()) {
		return true;
	}
	return execute(other...);
}

/// @brief Provides functions to execute multiple tasks
class TaskScheduler {
public:
	/// @brief Can execute all tasks which do not require information about
	/// current time. Does not return.
	/// @param ts ... Tasks to execute
	/// @tparam tasks ... types of ts
	template<typename... tasks>
	inline static void simple(const tasks&... ts) {
		while (true) {
			execute(ts...);
		}
	}

	/// @brief Can execute all tasks. Does not return.
	/// @param ts ... Tasks to execute
	/// @tparam tasks ... types of ts
	template<typename... tasks>
	inline static void timed(const tasks&... ts) {
		zol::chrono::time_t current = 0;
		while (true) {
			current = zol::chrono::get_millis();
			execute(current, ts...);
		}
	}

private:
	TaskScheduler() {}
};
