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
include psp/CMakeFiles/psp-pc-linux.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include psp/CMakeFiles/psp-pc-linux.dir/compiler_depend.make

# Include the progress variables for this target.
include psp/CMakeFiles/psp-pc-linux.dir/progress.make

# Include the compile flags for this target's objects.
include psp/CMakeFiles/psp-pc-linux.dir/flags.make

psp/CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.o: psp/CMakeFiles/psp-pc-linux.dir/flags.make
psp/CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.o: psp/pc-linux_module_list.c
psp/CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.o: psp/CMakeFiles/psp-pc-linux.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object psp/CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT psp/CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.o -MF CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.o.d -o CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.o -c /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux_module_list.c

psp/CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux_module_list.c > CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.i

psp/CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux_module_list.c -o CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.s

# Object files for target psp-pc-linux
psp__pc__linux_OBJECTS = \
"CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.o"

# External object files for target psp-pc-linux
psp__pc__linux_EXTERNAL_OBJECTS = \
"/home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.o" \
"/home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.o" \
"/home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.o" \
"/home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.o" \
"/home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.o" \
"/home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.o" \
"/home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-impl/CMakeFiles/psp-pc-linux-impl.dir/src/cfe_psp_exception.c.o" \
"/home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-impl/CMakeFiles/psp-pc-linux-impl.dir/src/cfe_psp_memory.c.o" \
"/home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-impl/CMakeFiles/psp-pc-linux-impl.dir/src/cfe_psp_ssr.c.o" \
"/home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-impl/CMakeFiles/psp-pc-linux-impl.dir/src/cfe_psp_start.c.o" \
"/home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-impl/CMakeFiles/psp-pc-linux-impl.dir/src/cfe_psp_support.c.o" \
"/home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-impl/CMakeFiles/psp-pc-linux-impl.dir/src/cfe_psp_watchdog.c.o"

psp/libpsp-pc-linux.a: psp/CMakeFiles/psp-pc-linux.dir/pc-linux_module_list.c.o
psp/libpsp-pc-linux.a: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.o
psp/libpsp-pc-linux.a: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.o
psp/libpsp-pc-linux.a: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.o
psp/libpsp-pc-linux.a: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.o
psp/libpsp-pc-linux.a: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.o
psp/libpsp-pc-linux.a: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.o
psp/libpsp-pc-linux.a: psp/pc-linux-impl/CMakeFiles/psp-pc-linux-impl.dir/src/cfe_psp_exception.c.o
psp/libpsp-pc-linux.a: psp/pc-linux-impl/CMakeFiles/psp-pc-linux-impl.dir/src/cfe_psp_memory.c.o
psp/libpsp-pc-linux.a: psp/pc-linux-impl/CMakeFiles/psp-pc-linux-impl.dir/src/cfe_psp_ssr.c.o
psp/libpsp-pc-linux.a: psp/pc-linux-impl/CMakeFiles/psp-pc-linux-impl.dir/src/cfe_psp_start.c.o
psp/libpsp-pc-linux.a: psp/pc-linux-impl/CMakeFiles/psp-pc-linux-impl.dir/src/cfe_psp_support.c.o
psp/libpsp-pc-linux.a: psp/pc-linux-impl/CMakeFiles/psp-pc-linux-impl.dir/src/cfe_psp_watchdog.c.o
psp/libpsp-pc-linux.a: psp/CMakeFiles/psp-pc-linux.dir/build.make
psp/libpsp-pc-linux.a: psp/CMakeFiles/psp-pc-linux.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libpsp-pc-linux.a"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp && $(CMAKE_COMMAND) -P CMakeFiles/psp-pc-linux.dir/cmake_clean_target.cmake
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/psp-pc-linux.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
psp/CMakeFiles/psp-pc-linux.dir/build: psp/libpsp-pc-linux.a
.PHONY : psp/CMakeFiles/psp-pc-linux.dir/build

psp/CMakeFiles/psp-pc-linux.dir/clean:
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp && $(CMAKE_COMMAND) -P CMakeFiles/psp-pc-linux.dir/cmake_clean.cmake
.PHONY : psp/CMakeFiles/psp-pc-linux.dir/clean

psp/CMakeFiles/psp-pc-linux.dir/depend:
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jam/Downloads/cFS/cfe /home/jam/Downloads/cFS/psp /home/jam/Downloads/cFS/build-sim/native/default_cpu1 /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/CMakeFiles/psp-pc-linux.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : psp/CMakeFiles/psp-pc-linux.dir/depend
