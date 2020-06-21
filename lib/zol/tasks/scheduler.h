#pragma once

#include "zol/chrono.h"

/// @brief 0th case for variadic template
/// @param current ... current time, unused in this case
/// @return Always returns false, no task was executed
bool execute(__attribute__((unused)) const zol::chrono::time_t& current) {
	return false;
}

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

bool execute() {
	return false;
}

template<typename T, typename... tasks_t>
bool execute(const T& t, const tasks_t&... other) {
	if (t.execute()) {
		return true;
	}
	return execute(other...);
}

class TaskScheduler {
public:
	template<typename... tasks>
	inline static void simple(const tasks&... ts) {
		while (true) {
			execute(ts...);
		}
	}

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
