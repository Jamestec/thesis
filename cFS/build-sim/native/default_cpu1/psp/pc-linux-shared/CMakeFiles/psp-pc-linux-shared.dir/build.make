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
include psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/compiler_depend.make

# Include the progress variables for this target.
include psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/progress.make

# Include the compile flags for this target's objects.
include psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/flags.make

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.o: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/flags.make
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.o: /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_error.c
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.o: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.o -MF CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.o.d -o CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.o -c /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_error.c

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_error.c > CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.i

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_error.c -o CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.s

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.o: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/flags.make
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.o: /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_exceptionstorage.c
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.o: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.o -MF CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.o.d -o CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.o -c /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_exceptionstorage.c

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_exceptionstorage.c > CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.i

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_exceptionstorage.c -o CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.s

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.o: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/flags.make
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.o: /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_memrange.c
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.o: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.o -MF CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.o.d -o CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.o -c /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_memrange.c

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_memrange.c > CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.i

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_memrange.c -o CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.s

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.o: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/flags.make
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.o: /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_memutils.c
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.o: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.o -MF CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.o.d -o CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.o -c /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_memutils.c

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_memutils.c > CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.i

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_memutils.c -o CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.s

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.o: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/flags.make
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.o: /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_module.c
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.o: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.o -MF CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.o.d -o CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.o -c /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_module.c

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_module.c > CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.i

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_module.c -o CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.s

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.o: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/flags.make
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.o: /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_version.c
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.o: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.o -MF CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.o.d -o CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.o -c /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_version.c

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_version.c > CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.i

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/psp/fsw/shared/src/cfe_psp_version.c -o CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.s

psp-pc-linux-shared: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_error.c.o
psp-pc-linux-shared: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_exceptionstorage.c.o
psp-pc-linux-shared: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memrange.c.o
psp-pc-linux-shared: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_memutils.c.o
psp-pc-linux-shared: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_module.c.o
psp-pc-linux-shared: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/src/cfe_psp_version.c.o
psp-pc-linux-shared: psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/build.make
.PHONY : psp-pc-linux-shared

# Rule to build all files generated by this target.
psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/build: psp-pc-linux-shared
.PHONY : psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/build

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/clean:
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared && $(CMAKE_COMMAND) -P CMakeFiles/psp-pc-linux-shared.dir/cmake_clean.cmake
.PHONY : psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/clean

psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/depend:
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jam/Downloads/cFS/cfe /home/jam/Downloads/cFS/psp/fsw/shared /home/jam/Downloads/cFS/build-sim/native/default_cpu1 /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared /home/jam/Downloads/cFS/build-sim/native/default_cpu1/psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : psp/pc-linux-shared/CMakeFiles/psp-pc-linux-shared.dir/depend

