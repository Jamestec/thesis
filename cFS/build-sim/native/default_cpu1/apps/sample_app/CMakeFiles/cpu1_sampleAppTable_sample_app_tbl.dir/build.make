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
include apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/compiler_depend.make

# Include the progress variables for this target.
include apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/progress.make

# Include the compile flags for this target's objects.
include apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/flags.make

apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.o: apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/flags.make
apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.o: /home/jam/Downloads/cFS/apps/sample_app/fsw/tables/sample_app_tbl.c
apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.o: apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/apps/sample_app && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.o -MF CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.o.d -o CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.o -c /home/jam/Downloads/cFS/apps/sample_app/fsw/tables/sample_app_tbl.c

apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/apps/sample_app && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/apps/sample_app/fsw/tables/sample_app_tbl.c > CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.i

apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/apps/sample_app && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/apps/sample_app/fsw/tables/sample_app_tbl.c -o CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.s

# Object files for target cpu1_sampleAppTable_sample_app_tbl
cpu1_sampleAppTable_sample_app_tbl_OBJECTS = \
"CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.o"

# External object files for target cpu1_sampleAppTable_sample_app_tbl
cpu1_sampleAppTable_sample_app_tbl_EXTERNAL_OBJECTS =

apps/sample_app/libcpu1_sampleAppTable_sample_app_tbl.a: apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/fsw/tables/sample_app_tbl.c.o
apps/sample_app/libcpu1_sampleAppTable_sample_app_tbl.a: apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/build.make
apps/sample_app/libcpu1_sampleAppTable_sample_app_tbl.a: apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libcpu1_sampleAppTable_sample_app_tbl.a"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/apps/sample_app && $(CMAKE_COMMAND) -P CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/cmake_clean_target.cmake
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/apps/sample_app && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/build: apps/sample_app/libcpu1_sampleAppTable_sample_app_tbl.a
.PHONY : apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/build

apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/clean:
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/apps/sample_app && $(CMAKE_COMMAND) -P CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/cmake_clean.cmake
.PHONY : apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/clean

apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/depend:
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jam/Downloads/cFS/cfe /home/jam/Downloads/cFS/apps/sample_app /home/jam/Downloads/cFS/build-sim/native/default_cpu1 /home/jam/Downloads/cFS/build-sim/native/default_cpu1/apps/sample_app /home/jam/Downloads/cFS/build-sim/native/default_cpu1/apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : apps/sample_app/CMakeFiles/cpu1_sampleAppTable_sample_app_tbl.dir/depend

