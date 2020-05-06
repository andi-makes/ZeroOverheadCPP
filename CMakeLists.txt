cmake_minimum_required(VERSION 3.17)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_CROSSCOMPILING 1)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

project(cmake_drives_me_crazy)
add_definitions(
	"-mmcu=atmega328p"
	"-DF_CPU=16000000UL"
	"-Os"
	"-std=c++17"
	"-Wno-error=narrowing -fno-exceptions -fno-threadsafe-statics -fpermissive"
	"-Wall -ffunction-sections -fdata-sections"
)

function(add_avr_executable EXECUTABLE_NAME)
	add_executable(
		${EXECUTABLE_NAME}.elf
		${ARGN}
	)

	target_link_options(
		${EXECUTABLE_NAME}.elf
		PRIVATE
		"-Wl,-Map,${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}.map"
	)

	add_custom_command(
		OUTPUT ${EXECUTABLE_NAME}.hex
		COMMAND
			avr-objcopy -j .text -j .data -O ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}.hex
		DEPENDS ${EXECUTABLE_NAME}.elf	
	)

	add_custom_command(
		OUTPUT ${EXECUTABLE_NAME}.lss
		COMMAND
			avr-objdump -d ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}.elf > ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}.lss
		DEPENDS ${EXECUTABLE_NAME}.elf
	)

	add_custom_target(
		${EXECUTABLE_NAME}
		ALL
		DEPENDS ${EXECUTABLE_NAME}.hex ${EXECUTABLE_NAME}.lss
	)

	get_directory_property(clean_files ADDITIONAL_MAKE_CLEAN_FILES)
	set_directory_properties(
		PROPERTIES
			ADDITIONAL_MAKE_CLEAN_FILES "${clean_files};${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}.map;${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}.hex;${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}.lss"
	)
endfunction(add_avr_executable)


include_directories(lib)

add_subdirectory(lib)
add_subdirectory(app)
