# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = "/Applications/CMake 2.8-12.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-12.app/Contents/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-12.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/build"

# Include any dependencies generated for this target.
include booster/CMakeFiles/test_aio_timer.dir/depend.make

# Include the progress variables for this target.
include booster/CMakeFiles/test_aio_timer.dir/progress.make

# Include the compile flags for this target's objects.
include booster/CMakeFiles/test_aio_timer.dir/flags.make

booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o: booster/CMakeFiles/test_aio_timer.dir/flags.make
booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o: ../booster/lib/aio/test/test_timer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/build/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o"
	cd "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/build/booster" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o -c "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/booster/lib/aio/test/test_timer.cpp"

booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.i"
	cd "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/build/booster" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/booster/lib/aio/test/test_timer.cpp" > CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.i

booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.s"
	cd "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/build/booster" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/booster/lib/aio/test/test_timer.cpp" -o CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.s

booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o.requires:
.PHONY : booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o.requires

booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o.provides: booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o.requires
	$(MAKE) -f booster/CMakeFiles/test_aio_timer.dir/build.make booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o.provides.build
.PHONY : booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o.provides

booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o.provides.build: booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o

# Object files for target test_aio_timer
test_aio_timer_OBJECTS = \
"CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o"

# External object files for target test_aio_timer
test_aio_timer_EXTERNAL_OBJECTS =

booster/test_aio_timer: booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o
booster/test_aio_timer: booster/CMakeFiles/test_aio_timer.dir/build.make
booster/test_aio_timer: booster/libbooster.0.0.2.dylib
booster/test_aio_timer: /usr/lib/libpthread.dylib
booster/test_aio_timer: /usr/local/lib/libpcre.dylib
booster/test_aio_timer: /opt/local/lib/libicuuc.dylib
booster/test_aio_timer: /opt/local/lib/libicui18n.dylib
booster/test_aio_timer: /opt/local/lib/libicudata.dylib
booster/test_aio_timer: /usr/lib/libiconv.dylib
booster/test_aio_timer: booster/CMakeFiles/test_aio_timer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable test_aio_timer"
	cd "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/build/booster" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_aio_timer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
booster/CMakeFiles/test_aio_timer.dir/build: booster/test_aio_timer
.PHONY : booster/CMakeFiles/test_aio_timer.dir/build

booster/CMakeFiles/test_aio_timer.dir/requires: booster/CMakeFiles/test_aio_timer.dir/lib/aio/test/test_timer.cpp.o.requires
.PHONY : booster/CMakeFiles/test_aio_timer.dir/requires

booster/CMakeFiles/test_aio_timer.dir/clean:
	cd "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/build/booster" && $(CMAKE_COMMAND) -P CMakeFiles/test_aio_timer.dir/cmake_clean.cmake
.PHONY : booster/CMakeFiles/test_aio_timer.dir/clean

booster/CMakeFiles/test_aio_timer.dir/depend:
	cd "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source" "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/booster" "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/build" "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/build/booster" "/Users/Abhi/Desktop/Github/Experimentation/Web Development/C++/cppcms_source/build/booster/CMakeFiles/test_aio_timer.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : booster/CMakeFiles/test_aio_timer.dir/depend
