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
CMAKE_BINARY_DIR = /home/jam/Downloads/cFS/build-sim

# Utility rule file for mission-clean.

# Include any custom commands dependencies for this target.
include CMakeFiles/mission-clean.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mission-clean.dir/progress.make

CMakeFiles/mission-clean:
	$(MAKE) clean

mission-clean: CMakeFiles/mission-clean
mission-clean: CMakeFiles/mission-clean.dir/build.make
.PHONY : mission-clean

# Rule to build all files generated by this target.
CMakeFiles/mission-clean.dir/build: mission-clean
.PHONY : CMakeFiles/mission-clean.dir/build

CMakeFiles/mission-clean.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mission-clean.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mission-clean.dir/clean

CMakeFiles/mission-clean.dir/depend:
	cd /home/jam/Downloads/cFS/build-sim && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jam/Downloads/cFS/cfe /home/jam/Downloads/cFS/cfe /home/jam/Downloads/cFS/build-sim /home/jam/Downloads/cFS/build-sim /home/jam/Downloads/cFS/build-sim/CMakeFiles/mission-clean.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mission-clean.dir/depend

