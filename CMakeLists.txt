cmake_minimum_required(VERSION 3.16)

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
	"-O1 -g -flto"
	"-std=c++17"
	"-fno-exceptions -fno-threadsafe-statics -fpermissive"
	"-Wall -Wextra -ffunction-sections -fdata-sections"
#    "-Werror"
)

add_link_options(
	"-mmcu=atmega328p"
	"-Wl,--gc-sections"
	"-flto"
	"-fuse-linker-plugin"
	"-Wl,--start-group"
	"-lm"
	"-Wl,--end-group"
)

function(add_avr_executable EXECUTABLE_NAME)
	set(BIN_FOLDER ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME})
	add_executable(
		${EXECUTABLE_NAME}.elf
		${ARGN}
	)

	target_link_options(
		${EXECUTABLE_NAME}.elf
		PRIVATE
		"-Wl,-Map,${BIN_FOLDER}.map"
	)

	add_custom_command(
		OUTPUT ${EXECUTABLE_NAME}.hex
		COMMAND
			avr-objcopy -j .text -j .data -O ihex ${BIN_FOLDER}.elf ${BIN_FOLDER}.hex
		COMMAND
			avr-size -t -d ${BIN_FOLDER}.elf
		DEPENDS ${EXECUTABLE_NAME}.elf	
	)

	add_custom_command(
		OUTPUT ${EXECUTABLE_NAME}.lss
		COMMAND
			avr-objdump -h -d ${BIN_FOLDER}.elf > ${BIN_FOLDER}.lss
		DEPENDS ${EXECUTABLE_NAME}.elf
	)

	add_custom_target(
		${EXECUTABLE_NAME}
		ALL
		DEPENDS ${EXECUTABLE_NAME}.hex ${EXECUTABLE_NAME}.lss
	)

	add_custom_target(
		upload_${EXECUTABLE_NAME}
		avrdude -p atmega328p -c arduino -b 115200 -D -P "COM9" -U flash:w:${BIN_FOLDER}.hex:i
		DEPENDS ${EXECUTABLE_NAME}.hex
		COMMENT "Uploading ${EXECUTABLE_NAME}.hex to atmega328p using arduino"
	)

	get_directory_property(clean_files ADDITIONAL_MAKE_CLEAN_FILES)
	set_directory_properties(
		PROPERTIES
			ADDITIONAL_MAKE_CLEAN_FILES "${clean_files};${BIN_FOLDER}.map;${BIN_FOLDER}.hex;${BIN_FOLDER}.lss"
	)
endfunction(add_avr_executable)


include_directories(lib)

add_subdirectory(lib)
add_subdirectory(app)
