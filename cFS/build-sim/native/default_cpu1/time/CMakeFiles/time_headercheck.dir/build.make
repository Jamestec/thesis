# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jam/Downloads/cFS/cfe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jam/Downloads/cFS/build-sim/native/default_cpu1

# Include any dependencies generated for this target.
include time/CMakeFiles/time_headercheck.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include time/CMakeFiles/time_headercheck.dir/compiler_depend.make

# Include the progress variables for this target.
include time/CMakeFiles/time_headercheck.dir/progress.make

# Include the compile flags for this target's objects.
include time/CMakeFiles/time_headercheck.dir/flags.make

time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.o: time/CMakeFiles/time_headercheck.dir/flags.make
time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.o: time/src/check_cfe_time_events.h.c
time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.o: time/CMakeFiles/time_headercheck.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.o -MF CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.o.d -o CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.o -c /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time/src/check_cfe_time_events.h.c

time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time/src/check_cfe_time_events.h.c > CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.i

time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time/src/check_cfe_time_events.h.c -o CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.s

time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.o: time/CMakeFiles/time_headercheck.dir/flags.make
time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.o: time/src/check_cfe_time_msg.h.c
time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.o: time/CMakeFiles/time_headercheck.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.o -MF CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.o.d -o CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.o -c /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time/src/check_cfe_time_msg.h.c

time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time/src/check_cfe_time_msg.h.c > CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.i

time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time/src/check_cfe_time_msg.h.c -o CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.s

# Object files for target time_headercheck
time_headercheck_OBJECTS = \
"CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.o" \
"CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.o"

# External object files for target time_headercheck
time_headercheck_EXTERNAL_OBJECTS =

time/libtime_headercheck.a: time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_events.h.c.o
time/libtime_headercheck.a: time/CMakeFiles/time_headercheck.dir/src/check_cfe_time_msg.h.c.o
time/libtime_headercheck.a: time/CMakeFiles/time_headercheck.dir/build.make
time/libtime_headercheck.a: time/CMakeFiles/time_headercheck.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libtime_headercheck.a"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time && $(CMAKE_COMMAND) -P CMakeFiles/time_headercheck.dir/cmake_clean_target.cmake
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/time_headercheck.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
time/CMakeFiles/time_headercheck.dir/build: time/libtime_headercheck.a
.PHONY : time/CMakeFiles/time_headercheck.dir/build

time/CMakeFiles/time_headercheck.dir/clean:
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time && $(CMAKE_COMMAND) -P CMakeFiles/time_headercheck.dir/cmake_clean.cmake
.PHONY : time/CMakeFiles/time_headercheck.dir/clean

time/CMakeFiles/time_headercheck.dir/depend:
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jam/Downloads/cFS/cfe /home/jam/Downloads/cFS/cfe/modules/time /home/jam/Downloads/cFS/build-sim/native/default_cpu1 /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time /home/jam/Downloads/cFS/build-sim/native/default_cpu1/time/CMakeFiles/time_headercheck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : time/CMakeFiles/time_headercheck.dir/depend
