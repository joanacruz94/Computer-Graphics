# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine/Build"

# Include any dependencies generated for this target.
include CMakeFiles/engine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/engine.dir/flags.make

CMakeFiles/engine.dir/engine.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/engine.cpp.o: ../engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/engine.dir/engine.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/engine.cpp.o -c "/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine/engine.cpp"

CMakeFiles/engine.dir/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/engine.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine/engine.cpp" > CMakeFiles/engine.dir/engine.cpp.i

CMakeFiles/engine.dir/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/engine.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine/engine.cpp" -o CMakeFiles/engine.dir/engine.cpp.s

CMakeFiles/engine.dir/engine.cpp.o.requires:

.PHONY : CMakeFiles/engine.dir/engine.cpp.o.requires

CMakeFiles/engine.dir/engine.cpp.o.provides: CMakeFiles/engine.dir/engine.cpp.o.requires
	$(MAKE) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/engine.cpp.o.provides.build
.PHONY : CMakeFiles/engine.dir/engine.cpp.o.provides

CMakeFiles/engine.dir/engine.cpp.o.provides.build: CMakeFiles/engine.dir/engine.cpp.o


# Object files for target engine
engine_OBJECTS = \
"CMakeFiles/engine.dir/engine.cpp.o"

# External object files for target engine
engine_EXTERNAL_OBJECTS =

engine: CMakeFiles/engine.dir/engine.cpp.o
engine: CMakeFiles/engine.dir/build.make
engine: /usr/local/lib/libtinyxml.dylib
engine: CMakeFiles/engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/engine.dir/build: engine

.PHONY : CMakeFiles/engine.dir/build

CMakeFiles/engine.dir/requires: CMakeFiles/engine.dir/engine.cpp.o.requires

.PHONY : CMakeFiles/engine.dir/requires

CMakeFiles/engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/engine.dir/clean

CMakeFiles/engine.dir/depend:
	cd "/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine/Build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine" "/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine" "/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine/Build" "/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine/Build" "/Users/etiennecosta/Desktop/Universidade/CG/Assessment/Projecto/Fase 1/Engine/Build/CMakeFiles/engine.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/engine.dir/depend

