# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_SOURCE_DIR = /home/igor/Study/Programming/4SEM/Futex

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/igor/Study/Programming/4SEM/Futex

# Include any dependencies generated for this target.
include CMakeFiles/FutexUnitTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FutexUnitTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FutexUnitTest.dir/flags.make

CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o: CMakeFiles/FutexUnitTest.dir/flags.make
CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o: src/futex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/igor/Study/Programming/4SEM/Futex/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o -c /home/igor/Study/Programming/4SEM/Futex/src/futex.cpp

CMakeFiles/FutexUnitTest.dir/src/futex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FutexUnitTest.dir/src/futex.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/igor/Study/Programming/4SEM/Futex/src/futex.cpp > CMakeFiles/FutexUnitTest.dir/src/futex.cpp.i

CMakeFiles/FutexUnitTest.dir/src/futex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FutexUnitTest.dir/src/futex.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/igor/Study/Programming/4SEM/Futex/src/futex.cpp -o CMakeFiles/FutexUnitTest.dir/src/futex.cpp.s

CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o.requires:

.PHONY : CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o.requires

CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o.provides: CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o.requires
	$(MAKE) -f CMakeFiles/FutexUnitTest.dir/build.make CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o.provides.build
.PHONY : CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o.provides

CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o.provides.build: CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o


CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o: CMakeFiles/FutexUnitTest.dir/flags.make
CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o: src/UnitTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/igor/Study/Programming/4SEM/Futex/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o -c /home/igor/Study/Programming/4SEM/Futex/src/UnitTest.cpp

CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/igor/Study/Programming/4SEM/Futex/src/UnitTest.cpp > CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.i

CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/igor/Study/Programming/4SEM/Futex/src/UnitTest.cpp -o CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.s

CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o.requires:

.PHONY : CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o.requires

CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o.provides: CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/FutexUnitTest.dir/build.make CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o.provides.build
.PHONY : CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o.provides

CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o.provides.build: CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o


# Object files for target FutexUnitTest
FutexUnitTest_OBJECTS = \
"CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o" \
"CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o"

# External object files for target FutexUnitTest
FutexUnitTest_EXTERNAL_OBJECTS =

FutexUnitTest: CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o
FutexUnitTest: CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o
FutexUnitTest: CMakeFiles/FutexUnitTest.dir/build.make
FutexUnitTest: CMakeFiles/FutexUnitTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/igor/Study/Programming/4SEM/Futex/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable FutexUnitTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FutexUnitTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FutexUnitTest.dir/build: FutexUnitTest

.PHONY : CMakeFiles/FutexUnitTest.dir/build

CMakeFiles/FutexUnitTest.dir/requires: CMakeFiles/FutexUnitTest.dir/src/futex.cpp.o.requires
CMakeFiles/FutexUnitTest.dir/requires: CMakeFiles/FutexUnitTest.dir/src/UnitTest.cpp.o.requires

.PHONY : CMakeFiles/FutexUnitTest.dir/requires

CMakeFiles/FutexUnitTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FutexUnitTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FutexUnitTest.dir/clean

CMakeFiles/FutexUnitTest.dir/depend:
	cd /home/igor/Study/Programming/4SEM/Futex && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/igor/Study/Programming/4SEM/Futex /home/igor/Study/Programming/4SEM/Futex /home/igor/Study/Programming/4SEM/Futex /home/igor/Study/Programming/4SEM/Futex /home/igor/Study/Programming/4SEM/Futex/CMakeFiles/FutexUnitTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FutexUnitTest.dir/depend

