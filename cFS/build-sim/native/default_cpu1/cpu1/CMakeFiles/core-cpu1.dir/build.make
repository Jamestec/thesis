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
include cpu1/CMakeFiles/core-cpu1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include cpu1/CMakeFiles/core-cpu1.dir/compiler_depend.make

# Include the progress variables for this target.
include cpu1/CMakeFiles/core-cpu1.dir/progress.make

# Include the compile flags for this target's objects.
include cpu1/CMakeFiles/core-cpu1.dir/flags.make

cpu1/cfe_module_version_table.c: /home/jam/Downloads/cFS/build-sim/src/cfe_module_version_table.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating cfe_module_version_table.c"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cmake -E copy /home/jam/Downloads/cFS/build-sim/src/cfe_module_version_table.c /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_module_version_table.c

cpu1/cfe_build_env_table.c: /home/jam/Downloads/cFS/build-sim/src/cfe_build_env_table.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating cfe_build_env_table.c"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cmake -E copy /home/jam/Downloads/cFS/build-sim/src/cfe_build_env_table.c /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_build_env_table.c

cpu1/CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.o: cpu1/CMakeFiles/core-cpu1.dir/flags.make
cpu1/CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.o: /home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c
cpu1/CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.o: cpu1/CMakeFiles/core-cpu1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object cpu1/CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT cpu1/CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.o -MF CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.o.d -o CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.o -c /home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c

cpu1/CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c > CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.i

cpu1/CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c -o CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.s

cpu1/CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.o: cpu1/CMakeFiles/core-cpu1.dir/flags.make
cpu1/CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.o: cpu1/cfe_module_version_table.c
cpu1/CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.o: cpu1/CMakeFiles/core-cpu1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object cpu1/CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT cpu1/CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.o -MF CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.o.d -o CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.o -c /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_module_version_table.c

cpu1/CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_module_version_table.c > CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.i

cpu1/CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_module_version_table.c -o CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.s

cpu1/CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.o: cpu1/CMakeFiles/core-cpu1.dir/flags.make
cpu1/CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.o: cpu1/cfe_build_env_table.c
cpu1/CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.o: cpu1/CMakeFiles/core-cpu1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object cpu1/CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT cpu1/CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.o -MF CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.o.d -o CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.o -c /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_build_env_table.c

cpu1/CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_build_env_table.c > CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.i

cpu1/CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_build_env_table.c -o CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.s

cpu1/CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.o: cpu1/CMakeFiles/core-cpu1.dir/flags.make
cpu1/CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.o: cpu1/cfe_psp_module_list.c
cpu1/CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.o: cpu1/CMakeFiles/core-cpu1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object cpu1/CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT cpu1/CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.o -MF CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.o.d -o CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.o -c /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_psp_module_list.c

cpu1/CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_psp_module_list.c > CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.i

cpu1/CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_psp_module_list.c -o CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.s

cpu1/CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.o: cpu1/CMakeFiles/core-cpu1.dir/flags.make
cpu1/CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.o: cpu1/cfe_static_symbol_list.c
cpu1/CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.o: cpu1/CMakeFiles/core-cpu1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object cpu1/CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT cpu1/CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.o -MF CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.o.d -o CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.o -c /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_static_symbol_list.c

cpu1/CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_static_symbol_list.c > CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.i

cpu1/CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_static_symbol_list.c -o CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.s

cpu1/CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.o: cpu1/CMakeFiles/core-cpu1.dir/flags.make
cpu1/CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.o: cpu1/cfe_static_module_list.c
cpu1/CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.o: cpu1/CMakeFiles/core-cpu1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object cpu1/CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT cpu1/CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.o -MF CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.o.d -o CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.o -c /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_static_module_list.c

cpu1/CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_static_module_list.c > CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.i

cpu1/CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/cfe_static_module_list.c -o CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.s

cpu1/CMakeFiles/core-cpu1.dir/src/target_config.c.o: cpu1/CMakeFiles/core-cpu1.dir/flags.make
cpu1/CMakeFiles/core-cpu1.dir/src/target_config.c.o: /home/jam/Downloads/cFS/cfe/cmake/target/src/target_config.c
cpu1/CMakeFiles/core-cpu1.dir/src/target_config.c.o: cpu1/CMakeFiles/core-cpu1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object cpu1/CMakeFiles/core-cpu1.dir/src/target_config.c.o"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT cpu1/CMakeFiles/core-cpu1.dir/src/target_config.c.o -MF CMakeFiles/core-cpu1.dir/src/target_config.c.o.d -o CMakeFiles/core-cpu1.dir/src/target_config.c.o -c /home/jam/Downloads/cFS/cfe/cmake/target/src/target_config.c

cpu1/CMakeFiles/core-cpu1.dir/src/target_config.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/core-cpu1.dir/src/target_config.c.i"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jam/Downloads/cFS/cfe/cmake/target/src/target_config.c > CMakeFiles/core-cpu1.dir/src/target_config.c.i

cpu1/CMakeFiles/core-cpu1.dir/src/target_config.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/core-cpu1.dir/src/target_config.c.s"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jam/Downloads/cFS/cfe/cmake/target/src/target_config.c -o CMakeFiles/core-cpu1.dir/src/target_config.c.s

# Object files for target core-cpu1
core__cpu1_OBJECTS = \
"CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.o" \
"CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.o" \
"CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.o" \
"CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.o" \
"CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.o" \
"CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.o" \
"CMakeFiles/core-cpu1.dir/src/target_config.c.o"

# External object files for target core-cpu1
core__cpu1_EXTERNAL_OBJECTS =

cpu1/core-cpu1: cpu1/CMakeFiles/core-cpu1.dir/home/jam/Downloads/cFS/build-sim/src/cfe_mission_strings.c.o
cpu1/core-cpu1: cpu1/CMakeFiles/core-cpu1.dir/cfe_module_version_table.c.o
cpu1/core-cpu1: cpu1/CMakeFiles/core-cpu1.dir/cfe_build_env_table.c.o
cpu1/core-cpu1: cpu1/CMakeFiles/core-cpu1.dir/cfe_psp_module_list.c.o
cpu1/core-cpu1: cpu1/CMakeFiles/core-cpu1.dir/cfe_static_symbol_list.c.o
cpu1/core-cpu1: cpu1/CMakeFiles/core-cpu1.dir/cfe_static_module_list.c.o
cpu1/core-cpu1: cpu1/CMakeFiles/core-cpu1.dir/src/target_config.c.o
cpu1/core-cpu1: cpu1/CMakeFiles/core-cpu1.dir/build.make
cpu1/core-cpu1: es/libes.a
cpu1/core-cpu1: evs/libevs.a
cpu1/core-cpu1: fs/libfs.a
cpu1/core-cpu1: sb/libsb.a
cpu1/core-cpu1: tbl/libtbl.a
cpu1/core-cpu1: time/libtime.a
cpu1/core-cpu1: osal/libosal.a
cpu1/core-cpu1: psp/libpsp-pc-linux.a
cpu1/core-cpu1: msg/libmsg.a
cpu1/core-cpu1: sbr/libsbr.a
cpu1/core-cpu1: resourceid/libresourceid.a
cpu1/core-cpu1: config/libconfig.a
cpu1/core-cpu1: osal/libosal_bsp.a
cpu1/core-cpu1: psp/soft_timebase-pc-linux-impl/libsoft_timebase.a
cpu1/core-cpu1: psp/timebase_posix_clock-pc-linux-impl/libtimebase_posix_clock.a
cpu1/core-cpu1: psp/eeprom_mmap_file-pc-linux-impl/libeeprom_mmap_file.a
cpu1/core-cpu1: psp/ram_notimpl-pc-linux-impl/libram_notimpl.a
cpu1/core-cpu1: psp/port_notimpl-pc-linux-impl/libport_notimpl.a
cpu1/core-cpu1: cpu1/CMakeFiles/core-cpu1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jam/Downloads/cFS/build-sim/native/default_cpu1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C executable core-cpu1"
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/core-cpu1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cpu1/CMakeFiles/core-cpu1.dir/build: cpu1/core-cpu1
.PHONY : cpu1/CMakeFiles/core-cpu1.dir/build

cpu1/CMakeFiles/core-cpu1.dir/clean:
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 && $(CMAKE_COMMAND) -P CMakeFiles/core-cpu1.dir/cmake_clean.cmake
.PHONY : cpu1/CMakeFiles/core-cpu1.dir/clean

cpu1/CMakeFiles/core-cpu1.dir/depend: cpu1/cfe_build_env_table.c
cpu1/CMakeFiles/core-cpu1.dir/depend: cpu1/cfe_module_version_table.c
	cd /home/jam/Downloads/cFS/build-sim/native/default_cpu1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jam/Downloads/cFS/cfe /home/jam/Downloads/cFS/cfe/cmake/target /home/jam/Downloads/cFS/build-sim/native/default_cpu1 /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1 /home/jam/Downloads/cFS/build-sim/native/default_cpu1/cpu1/CMakeFiles/core-cpu1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cpu1/CMakeFiles/core-cpu1.dir/depend

