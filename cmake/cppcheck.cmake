# cppcheck
add_custom_target(
	cppcheck
	ALL
	COMMAND cppcheck
	${CMAKE_SOURCE_DIR}/app
	${CMAKE_SOURCE_DIR}/lib
    --enable=warning
    --std=c++17
	--output-file=${CMAKE_SOURCE_DIR}/analyse/cppcheck.txt
)