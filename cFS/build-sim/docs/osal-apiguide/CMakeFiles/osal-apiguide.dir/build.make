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

# Utility rule file for osal-apiguide.

# Include any custom commands dependencies for this target.
include docs/osal-apiguide/CMakeFiles/osal-apiguide.dir/compiler_depend.make

# Include the progress variables for this target.
include docs/osal-apiguide/CMakeFiles/osal-apiguide.dir/progress.make

docs/osal-apiguide/CMakeFiles/osal-apiguide: docs/osal-apiguide/html/index.html
	cd /home/jam/Downloads/cFS/build-sim/docs/osal-apiguide && echo OSAL\ API\ Guide:\ file:///home/jam/Downloads/cFS/build-sim/docs/osal-apiguide/html/index.html

docs/osal-apiguide/html/index.html: docs/osal-apiguide/osal-apiguide.doxyfile
docs/osal-apiguide/html/index.html: docs/osal-common.doxyfile
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/docs/src/osal_frontpage.dox
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/docs/src/osal_fs.dox
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/docs/src/osal_timer.dox
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/common_types.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-binsem.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-bsp.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-clock.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-common.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-constants.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-countsem.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-dir.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-error.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-file.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-filesys.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-heap.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-idmap.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-macros.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-module.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-mutex.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-network.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-printf.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-queue.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-select.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-shell.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-sockets.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-task.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-timebase.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-timer.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi-version.h
docs/osal-apiguide/html/index.html: /home/jam/Downloads/cFS/osal/src/os/inc/osapi.h
docs/osal-apiguide/html/index.html: docs/osconfig-example.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jam/Downloads/cFS/build-sim/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating html/index.html"
	cd /home/jam/Downloads/cFS/build-sim/docs/osal-apiguide && doxygen /home/jam/Downloads/cFS/build-sim/docs/osal-apiguide/osal-apiguide.doxyfile

osal-apiguide: docs/osal-apiguide/CMakeFiles/osal-apiguide
osal-apiguide: docs/osal-apiguide/html/index.html
osal-apiguide: docs/osal-apiguide/CMakeFiles/osal-apiguide.dir/build.make
.PHONY : osal-apiguide

# Rule to build all files generated by this target.
docs/osal-apiguide/CMakeFiles/osal-apiguide.dir/build: osal-apiguide
.PHONY : docs/osal-apiguide/CMakeFiles/osal-apiguide.dir/build

docs/osal-apiguide/CMakeFiles/osal-apiguide.dir/clean:
	cd /home/jam/Downloads/cFS/build-sim/docs/osal-apiguide && $(CMAKE_COMMAND) -P CMakeFiles/osal-apiguide.dir/cmake_clean.cmake
.PHONY : docs/osal-apiguide/CMakeFiles/osal-apiguide.dir/clean

docs/osal-apiguide/CMakeFiles/osal-apiguide.dir/depend:
	cd /home/jam/Downloads/cFS/build-sim && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jam/Downloads/cFS/cfe /home/jam/Downloads/cFS/osal/docs/src /home/jam/Downloads/cFS/build-sim /home/jam/Downloads/cFS/build-sim/docs/osal-apiguide /home/jam/Downloads/cFS/build-sim/docs/osal-apiguide/CMakeFiles/osal-apiguide.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : docs/osal-apiguide/CMakeFiles/osal-apiguide.dir/depend
