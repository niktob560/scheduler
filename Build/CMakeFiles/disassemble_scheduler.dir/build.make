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

# Utility rule file for disassemble_scheduler.

# Include the progress variables for this target.
include CMakeFiles/disassemble_scheduler.dir/progress.make

CMakeFiles/disassemble_scheduler: scheduler-atmega2560.elf
	/usr/bin/avr-objdump -h -S scheduler-atmega2560.elf > scheduler.lst

disassemble_scheduler: CMakeFiles/disassemble_scheduler
disassemble_scheduler: CMakeFiles/disassemble_scheduler.dir/build.make

.PHONY : disassemble_scheduler

# Rule to build all files generated by this target.
CMakeFiles/disassemble_scheduler.dir/build: disassemble_scheduler

.PHONY : CMakeFiles/disassemble_scheduler.dir/build

CMakeFiles/disassemble_scheduler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/disassemble_scheduler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/disassemble_scheduler.dir/clean

CMakeFiles/disassemble_scheduler.dir/depend:
	cd /home/nikto_b/Documents/C++/scheduler/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nikto_b/Documents/C++/scheduler /home/nikto_b/Documents/C++/scheduler /home/nikto_b/Documents/C++/scheduler/Build /home/nikto_b/Documents/C++/scheduler/Build /home/nikto_b/Documents/C++/scheduler/Build/CMakeFiles/disassemble_scheduler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/disassemble_scheduler.dir/depend

