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
include psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/compiler_depend.make

# Include the progress variables for this target.
include psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/progress.make

# Include the compile flags for this target's objects.
include psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/flags.make

psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.o: psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/flags.make
psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.o: /home/jam/Downloads/cFS/psp/fsw/modules/port_notimpl/cfe_psp_port_notimpl.c
psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.o: psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/port_notimpl-pc-linux-impl && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.o -MF CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.o.d -o CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.o -c /home/jam/Downloads/cFS/psp/fsw/modules/port_notimpl/cfe_psp_port_notimpl.c

psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/port_notimpl-pc-linux-impl && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/psp/fsw/modules/port_notimpl/cfe_psp_port_notimpl.c > CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.i

psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/port_notimpl-pc-linux-impl && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/psp/fsw/modules/port_notimpl/cfe_psp_port_notimpl.c -o CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.s

# Object files for target port_notimpl
port_notimpl_OBJECTS = \
"CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.o"

# External object files for target port_notimpl
port_notimpl_EXTERNAL_OBJECTS =

psp/port_notimpl-pc-linux-impl/libport_notimpl.a: psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/cfe_psp_port_notimpl.c.o
psp/port_notimpl-pc-linux-impl/libport_notimpl.a: psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/build.make
psp/port_notimpl-pc-linux-impl/libport_notimpl.a: psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libport_notimpl.a"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/port_notimpl-pc-linux-impl && $(CMAKE_COMMAND) -P CMakeFiles/port_notimpl.dir/cmake_clean_target.cmake
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/port_notimpl-pc-linux-impl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/port_notimpl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/build: psp/port_notimpl-pc-linux-impl/libport_notimpl.a
.PHONY : psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/build

psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/clean:
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/port_notimpl-pc-linux-impl && $(CMAKE_COMMAND) -P CMakeFiles/port_notimpl.dir/cmake_clean.cmake
.PHONY : psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/clean

psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/depend:
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jam/Downloads/cFS/cfe /home/jam/Downloads/cFS/psp/fsw/modules/port_notimpl /home/jam/Downloads/cFS/build-sim/native/default_cpu1 /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/port_notimpl-pc-linux-impl /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : psp/port_notimpl-pc-linux-impl/CMakeFiles/port_notimpl.dir/depend

