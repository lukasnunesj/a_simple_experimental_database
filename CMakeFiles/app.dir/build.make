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
CMAKE_SOURCE_DIR = /home/guilherme/my-git/a_simple_experimental_database

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/guilherme/my-git/a_simple_experimental_database

# Include any dependencies generated for this target.
include CMakeFiles/app.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/app.dir/flags.make

CMakeFiles/app.dir/src/REPL.o: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/src/REPL.o: src/REPL.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guilherme/my-git/a_simple_experimental_database/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/app.dir/src/REPL.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app.dir/src/REPL.o   -c /home/guilherme/my-git/a_simple_experimental_database/src/REPL.c

CMakeFiles/app.dir/src/REPL.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/src/REPL.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/guilherme/my-git/a_simple_experimental_database/src/REPL.c > CMakeFiles/app.dir/src/REPL.i

CMakeFiles/app.dir/src/REPL.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/src/REPL.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/guilherme/my-git/a_simple_experimental_database/src/REPL.c -o CMakeFiles/app.dir/src/REPL.s

# Object files for target app
app_OBJECTS = \
"CMakeFiles/app.dir/src/REPL.o"

# External object files for target app
app_EXTERNAL_OBJECTS =

app: CMakeFiles/app.dir/src/REPL.o
app: CMakeFiles/app.dir/build.make
app: CMakeFiles/app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/guilherme/my-git/a_simple_experimental_database/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/app.dir/build: app

.PHONY : CMakeFiles/app.dir/build

CMakeFiles/app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/app.dir/clean

CMakeFiles/app.dir/depend:
	cd /home/guilherme/my-git/a_simple_experimental_database && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/guilherme/my-git/a_simple_experimental_database /home/guilherme/my-git/a_simple_experimental_database /home/guilherme/my-git/a_simple_experimental_database /home/guilherme/my-git/a_simple_experimental_database /home/guilherme/my-git/a_simple_experimental_database/CMakeFiles/app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/app.dir/depend

