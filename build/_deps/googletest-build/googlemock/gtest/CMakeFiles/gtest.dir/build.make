# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /home/levce/.local/lib/python3.9/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/levce/.local/lib/python3.9/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/levce/projectsDED/Elpidifor-s-legacy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/levce/projectsDED/Elpidifor-s-legacy/build

# Include any dependencies generated for this target.
include _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/flags.make

_deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/flags.make
_deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: _deps/googletest-src/googletest/src/gtest-all.cc
_deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/levce/projectsDED/Elpidifor-s-legacy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd /home/levce/projectsDED/Elpidifor-s-legacy/build/_deps/googletest-build/googlemock/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o -MF CMakeFiles/gtest.dir/src/gtest-all.cc.o.d -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /home/levce/projectsDED/Elpidifor-s-legacy/build/_deps/googletest-src/googletest/src/gtest-all.cc

_deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /home/levce/projectsDED/Elpidifor-s-legacy/build/_deps/googletest-build/googlemock/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/levce/projectsDED/Elpidifor-s-legacy/build/_deps/googletest-src/googletest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

_deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /home/levce/projectsDED/Elpidifor-s-legacy/build/_deps/googletest-build/googlemock/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/levce/projectsDED/Elpidifor-s-legacy/build/_deps/googletest-src/googletest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

_deps/googletest-build/googlemock/gtest/libgtest.a: _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
_deps/googletest-build/googlemock/gtest/libgtest.a: _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/build.make
_deps/googletest-build/googlemock/gtest/libgtest.a: _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/levce/projectsDED/Elpidifor-s-legacy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgtest.a"
	cd /home/levce/projectsDED/Elpidifor-s-legacy/build/_deps/googletest-build/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /home/levce/projectsDED/Elpidifor-s-legacy/build/_deps/googletest-build/googlemock/gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/build: _deps/googletest-build/googlemock/gtest/libgtest.a
.PHONY : _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/build

_deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/clean:
	cd /home/levce/projectsDED/Elpidifor-s-legacy/build/_deps/googletest-build/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/clean

_deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/depend:
	cd /home/levce/projectsDED/Elpidifor-s-legacy/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/levce/projectsDED/Elpidifor-s-legacy /home/levce/projectsDED/Elpidifor-s-legacy/build/_deps/googletest-src/googletest /home/levce/projectsDED/Elpidifor-s-legacy/build /home/levce/projectsDED/Elpidifor-s-legacy/build/_deps/googletest-build/googlemock/gtest /home/levce/projectsDED/Elpidifor-s-legacy/build/_deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/depend

