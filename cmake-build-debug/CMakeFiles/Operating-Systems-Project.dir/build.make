# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /mnt/d/RPI/2019Summer/Operating-Systems-Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/RPI/2019Summer/Operating-Systems-Project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Operating-Systems-Project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Operating-Systems-Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Operating-Systems-Project.dir/flags.make

CMakeFiles/Operating-Systems-Project.dir/main.c.o: CMakeFiles/Operating-Systems-Project.dir/flags.make
CMakeFiles/Operating-Systems-Project.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/RPI/2019Summer/Operating-Systems-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Operating-Systems-Project.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Operating-Systems-Project.dir/main.c.o   -c /mnt/d/RPI/2019Summer/Operating-Systems-Project/main.c

CMakeFiles/Operating-Systems-Project.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Operating-Systems-Project.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/RPI/2019Summer/Operating-Systems-Project/main.c > CMakeFiles/Operating-Systems-Project.dir/main.c.i

CMakeFiles/Operating-Systems-Project.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Operating-Systems-Project.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/RPI/2019Summer/Operating-Systems-Project/main.c -o CMakeFiles/Operating-Systems-Project.dir/main.c.s

CMakeFiles/Operating-Systems-Project.dir/main.c.o.requires:

.PHONY : CMakeFiles/Operating-Systems-Project.dir/main.c.o.requires

CMakeFiles/Operating-Systems-Project.dir/main.c.o.provides: CMakeFiles/Operating-Systems-Project.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/Operating-Systems-Project.dir/build.make CMakeFiles/Operating-Systems-Project.dir/main.c.o.provides.build
.PHONY : CMakeFiles/Operating-Systems-Project.dir/main.c.o.provides

CMakeFiles/Operating-Systems-Project.dir/main.c.o.provides.build: CMakeFiles/Operating-Systems-Project.dir/main.c.o


CMakeFiles/Operating-Systems-Project.dir/RR.c.o: CMakeFiles/Operating-Systems-Project.dir/flags.make
CMakeFiles/Operating-Systems-Project.dir/RR.c.o: ../RR.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/RPI/2019Summer/Operating-Systems-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Operating-Systems-Project.dir/RR.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Operating-Systems-Project.dir/RR.c.o   -c /mnt/d/RPI/2019Summer/Operating-Systems-Project/RR.c

CMakeFiles/Operating-Systems-Project.dir/RR.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Operating-Systems-Project.dir/RR.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/RPI/2019Summer/Operating-Systems-Project/RR.c > CMakeFiles/Operating-Systems-Project.dir/RR.c.i

CMakeFiles/Operating-Systems-Project.dir/RR.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Operating-Systems-Project.dir/RR.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/RPI/2019Summer/Operating-Systems-Project/RR.c -o CMakeFiles/Operating-Systems-Project.dir/RR.c.s

CMakeFiles/Operating-Systems-Project.dir/RR.c.o.requires:

.PHONY : CMakeFiles/Operating-Systems-Project.dir/RR.c.o.requires

CMakeFiles/Operating-Systems-Project.dir/RR.c.o.provides: CMakeFiles/Operating-Systems-Project.dir/RR.c.o.requires
	$(MAKE) -f CMakeFiles/Operating-Systems-Project.dir/build.make CMakeFiles/Operating-Systems-Project.dir/RR.c.o.provides.build
.PHONY : CMakeFiles/Operating-Systems-Project.dir/RR.c.o.provides

CMakeFiles/Operating-Systems-Project.dir/RR.c.o.provides.build: CMakeFiles/Operating-Systems-Project.dir/RR.c.o


CMakeFiles/Operating-Systems-Project.dir/SJF.c.o: CMakeFiles/Operating-Systems-Project.dir/flags.make
CMakeFiles/Operating-Systems-Project.dir/SJF.c.o: ../SJF.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/RPI/2019Summer/Operating-Systems-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Operating-Systems-Project.dir/SJF.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Operating-Systems-Project.dir/SJF.c.o   -c /mnt/d/RPI/2019Summer/Operating-Systems-Project/SJF.c

CMakeFiles/Operating-Systems-Project.dir/SJF.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Operating-Systems-Project.dir/SJF.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/RPI/2019Summer/Operating-Systems-Project/SJF.c > CMakeFiles/Operating-Systems-Project.dir/SJF.c.i

CMakeFiles/Operating-Systems-Project.dir/SJF.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Operating-Systems-Project.dir/SJF.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/RPI/2019Summer/Operating-Systems-Project/SJF.c -o CMakeFiles/Operating-Systems-Project.dir/SJF.c.s

CMakeFiles/Operating-Systems-Project.dir/SJF.c.o.requires:

.PHONY : CMakeFiles/Operating-Systems-Project.dir/SJF.c.o.requires

CMakeFiles/Operating-Systems-Project.dir/SJF.c.o.provides: CMakeFiles/Operating-Systems-Project.dir/SJF.c.o.requires
	$(MAKE) -f CMakeFiles/Operating-Systems-Project.dir/build.make CMakeFiles/Operating-Systems-Project.dir/SJF.c.o.provides.build
.PHONY : CMakeFiles/Operating-Systems-Project.dir/SJF.c.o.provides

CMakeFiles/Operating-Systems-Project.dir/SJF.c.o.provides.build: CMakeFiles/Operating-Systems-Project.dir/SJF.c.o


CMakeFiles/Operating-Systems-Project.dir/SRT.c.o: CMakeFiles/Operating-Systems-Project.dir/flags.make
CMakeFiles/Operating-Systems-Project.dir/SRT.c.o: ../SRT.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/RPI/2019Summer/Operating-Systems-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Operating-Systems-Project.dir/SRT.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Operating-Systems-Project.dir/SRT.c.o   -c /mnt/d/RPI/2019Summer/Operating-Systems-Project/SRT.c

CMakeFiles/Operating-Systems-Project.dir/SRT.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Operating-Systems-Project.dir/SRT.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/RPI/2019Summer/Operating-Systems-Project/SRT.c > CMakeFiles/Operating-Systems-Project.dir/SRT.c.i

CMakeFiles/Operating-Systems-Project.dir/SRT.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Operating-Systems-Project.dir/SRT.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/RPI/2019Summer/Operating-Systems-Project/SRT.c -o CMakeFiles/Operating-Systems-Project.dir/SRT.c.s

CMakeFiles/Operating-Systems-Project.dir/SRT.c.o.requires:

.PHONY : CMakeFiles/Operating-Systems-Project.dir/SRT.c.o.requires

CMakeFiles/Operating-Systems-Project.dir/SRT.c.o.provides: CMakeFiles/Operating-Systems-Project.dir/SRT.c.o.requires
	$(MAKE) -f CMakeFiles/Operating-Systems-Project.dir/build.make CMakeFiles/Operating-Systems-Project.dir/SRT.c.o.provides.build
.PHONY : CMakeFiles/Operating-Systems-Project.dir/SRT.c.o.provides

CMakeFiles/Operating-Systems-Project.dir/SRT.c.o.provides.build: CMakeFiles/Operating-Systems-Project.dir/SRT.c.o


CMakeFiles/Operating-Systems-Project.dir/output.c.o: CMakeFiles/Operating-Systems-Project.dir/flags.make
CMakeFiles/Operating-Systems-Project.dir/output.c.o: ../output.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/RPI/2019Summer/Operating-Systems-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Operating-Systems-Project.dir/output.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Operating-Systems-Project.dir/output.c.o   -c /mnt/d/RPI/2019Summer/Operating-Systems-Project/output.c

CMakeFiles/Operating-Systems-Project.dir/output.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Operating-Systems-Project.dir/output.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/RPI/2019Summer/Operating-Systems-Project/output.c > CMakeFiles/Operating-Systems-Project.dir/output.c.i

CMakeFiles/Operating-Systems-Project.dir/output.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Operating-Systems-Project.dir/output.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/RPI/2019Summer/Operating-Systems-Project/output.c -o CMakeFiles/Operating-Systems-Project.dir/output.c.s

CMakeFiles/Operating-Systems-Project.dir/output.c.o.requires:

.PHONY : CMakeFiles/Operating-Systems-Project.dir/output.c.o.requires

CMakeFiles/Operating-Systems-Project.dir/output.c.o.provides: CMakeFiles/Operating-Systems-Project.dir/output.c.o.requires
	$(MAKE) -f CMakeFiles/Operating-Systems-Project.dir/build.make CMakeFiles/Operating-Systems-Project.dir/output.c.o.provides.build
.PHONY : CMakeFiles/Operating-Systems-Project.dir/output.c.o.provides

CMakeFiles/Operating-Systems-Project.dir/output.c.o.provides.build: CMakeFiles/Operating-Systems-Project.dir/output.c.o


CMakeFiles/Operating-Systems-Project.dir/helper.c.o: CMakeFiles/Operating-Systems-Project.dir/flags.make
CMakeFiles/Operating-Systems-Project.dir/helper.c.o: ../helper.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/RPI/2019Summer/Operating-Systems-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Operating-Systems-Project.dir/helper.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Operating-Systems-Project.dir/helper.c.o   -c /mnt/d/RPI/2019Summer/Operating-Systems-Project/helper.c

CMakeFiles/Operating-Systems-Project.dir/helper.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Operating-Systems-Project.dir/helper.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/RPI/2019Summer/Operating-Systems-Project/helper.c > CMakeFiles/Operating-Systems-Project.dir/helper.c.i

CMakeFiles/Operating-Systems-Project.dir/helper.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Operating-Systems-Project.dir/helper.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/RPI/2019Summer/Operating-Systems-Project/helper.c -o CMakeFiles/Operating-Systems-Project.dir/helper.c.s

CMakeFiles/Operating-Systems-Project.dir/helper.c.o.requires:

.PHONY : CMakeFiles/Operating-Systems-Project.dir/helper.c.o.requires

CMakeFiles/Operating-Systems-Project.dir/helper.c.o.provides: CMakeFiles/Operating-Systems-Project.dir/helper.c.o.requires
	$(MAKE) -f CMakeFiles/Operating-Systems-Project.dir/build.make CMakeFiles/Operating-Systems-Project.dir/helper.c.o.provides.build
.PHONY : CMakeFiles/Operating-Systems-Project.dir/helper.c.o.provides

CMakeFiles/Operating-Systems-Project.dir/helper.c.o.provides.build: CMakeFiles/Operating-Systems-Project.dir/helper.c.o


# Object files for target Operating-Systems-Project
Operating__Systems__Project_OBJECTS = \
"CMakeFiles/Operating-Systems-Project.dir/main.c.o" \
"CMakeFiles/Operating-Systems-Project.dir/RR.c.o" \
"CMakeFiles/Operating-Systems-Project.dir/SJF.c.o" \
"CMakeFiles/Operating-Systems-Project.dir/SRT.c.o" \
"CMakeFiles/Operating-Systems-Project.dir/output.c.o" \
"CMakeFiles/Operating-Systems-Project.dir/helper.c.o"

# External object files for target Operating-Systems-Project
Operating__Systems__Project_EXTERNAL_OBJECTS =

Operating-Systems-Project: CMakeFiles/Operating-Systems-Project.dir/main.c.o
Operating-Systems-Project: CMakeFiles/Operating-Systems-Project.dir/RR.c.o
Operating-Systems-Project: CMakeFiles/Operating-Systems-Project.dir/SJF.c.o
Operating-Systems-Project: CMakeFiles/Operating-Systems-Project.dir/SRT.c.o
Operating-Systems-Project: CMakeFiles/Operating-Systems-Project.dir/output.c.o
Operating-Systems-Project: CMakeFiles/Operating-Systems-Project.dir/helper.c.o
Operating-Systems-Project: CMakeFiles/Operating-Systems-Project.dir/build.make
Operating-Systems-Project: CMakeFiles/Operating-Systems-Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/RPI/2019Summer/Operating-Systems-Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable Operating-Systems-Project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Operating-Systems-Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Operating-Systems-Project.dir/build: Operating-Systems-Project

.PHONY : CMakeFiles/Operating-Systems-Project.dir/build

CMakeFiles/Operating-Systems-Project.dir/requires: CMakeFiles/Operating-Systems-Project.dir/main.c.o.requires
CMakeFiles/Operating-Systems-Project.dir/requires: CMakeFiles/Operating-Systems-Project.dir/RR.c.o.requires
CMakeFiles/Operating-Systems-Project.dir/requires: CMakeFiles/Operating-Systems-Project.dir/SJF.c.o.requires
CMakeFiles/Operating-Systems-Project.dir/requires: CMakeFiles/Operating-Systems-Project.dir/SRT.c.o.requires
CMakeFiles/Operating-Systems-Project.dir/requires: CMakeFiles/Operating-Systems-Project.dir/output.c.o.requires
CMakeFiles/Operating-Systems-Project.dir/requires: CMakeFiles/Operating-Systems-Project.dir/helper.c.o.requires

.PHONY : CMakeFiles/Operating-Systems-Project.dir/requires

CMakeFiles/Operating-Systems-Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Operating-Systems-Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Operating-Systems-Project.dir/clean

CMakeFiles/Operating-Systems-Project.dir/depend:
	cd /mnt/d/RPI/2019Summer/Operating-Systems-Project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/RPI/2019Summer/Operating-Systems-Project /mnt/d/RPI/2019Summer/Operating-Systems-Project /mnt/d/RPI/2019Summer/Operating-Systems-Project/cmake-build-debug /mnt/d/RPI/2019Summer/Operating-Systems-Project/cmake-build-debug /mnt/d/RPI/2019Summer/Operating-Systems-Project/cmake-build-debug/CMakeFiles/Operating-Systems-Project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Operating-Systems-Project.dir/depend

