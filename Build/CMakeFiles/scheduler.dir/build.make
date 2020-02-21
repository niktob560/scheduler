# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nikto_b/Documents/C++/scheduler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nikto_b/Documents/C++/scheduler/Build

# Utility rule file for scheduler.

# Include the progress variables for this target.
include CMakeFiles/scheduler.dir/progress.make

CMakeFiles/scheduler: scheduler-atmega2560.hex
CMakeFiles/scheduler: scheduler-atmega2560.lst
CMakeFiles/scheduler: scheduler-atmega2560-eeprom.hex


scheduler-atmega2560.hex: scheduler-atmega2560.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/nikto_b/Documents/C++/scheduler/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating scheduler-atmega2560.hex"
	/usr/bin/avr-objcopy -j .text -j .data -O ihex scheduler-atmega2560.elf scheduler-atmega2560.hex
	/usr/bin/avr-size -C --mcu=atmega2560 scheduler-atmega2560.elf

scheduler-atmega2560.lst: scheduler-atmega2560.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/nikto_b/Documents/C++/scheduler/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating scheduler-atmega2560.lst"
	/usr/bin/avr-objdump -d scheduler-atmega2560.elf > scheduler-atmega2560.lst

scheduler-atmega2560-eeprom.hex: scheduler-atmega2560.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/nikto_b/Documents/C++/scheduler/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating scheduler-atmega2560-eeprom.hex"
	/usr/bin/avr-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex scheduler-atmega2560.elf scheduler-atmega2560-eeprom.hex

scheduler: CMakeFiles/scheduler
scheduler: scheduler-atmega2560.hex
scheduler: scheduler-atmega2560.lst
scheduler: scheduler-atmega2560-eeprom.hex
scheduler: CMakeFiles/scheduler.dir/build.make

.PHONY : scheduler

# Rule to build all files generated by this target.
CMakeFiles/scheduler.dir/build: scheduler

.PHONY : CMakeFiles/scheduler.dir/build

CMakeFiles/scheduler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/scheduler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/scheduler.dir/clean

CMakeFiles/scheduler.dir/depend:
	cd /home/nikto_b/Documents/C++/scheduler/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nikto_b/Documents/C++/scheduler /home/nikto_b/Documents/C++/scheduler /home/nikto_b/Documents/C++/scheduler/Build /home/nikto_b/Documents/C++/scheduler/Build /home/nikto_b/Documents/C++/scheduler/Build/CMakeFiles/scheduler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/scheduler.dir/depend
