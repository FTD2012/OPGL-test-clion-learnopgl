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
CMAKE_SOURCE_DIR = "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/build"

# Include any dependencies generated for this target.
include openl_lib/CMakeFiles/OPGL_test_clion.dir/depend.make

# Include the progress variables for this target.
include openl_lib/CMakeFiles/OPGL_test_clion.dir/progress.make

# Include the compile flags for this target's objects.
include openl_lib/CMakeFiles/OPGL_test_clion.dir/flags.make

openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o: openl_lib/CMakeFiles/OPGL_test_clion.dir/flags.make
openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o: ../openl_lib/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o"
	cd "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/build/openl_lib" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/OPGL_test_clion.dir/glad.c.o   -c "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/openl_lib/glad.c"

openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OPGL_test_clion.dir/glad.c.i"
	cd "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/build/openl_lib" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/openl_lib/glad.c" > CMakeFiles/OPGL_test_clion.dir/glad.c.i

openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OPGL_test_clion.dir/glad.c.s"
	cd "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/build/openl_lib" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/openl_lib/glad.c" -o CMakeFiles/OPGL_test_clion.dir/glad.c.s

openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o.requires:

.PHONY : openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o.requires

openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o.provides: openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o.requires
	$(MAKE) -f openl_lib/CMakeFiles/OPGL_test_clion.dir/build.make openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o.provides.build
.PHONY : openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o.provides

openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o.provides.build: openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o


# Object files for target OPGL_test_clion
OPGL_test_clion_OBJECTS = \
"CMakeFiles/OPGL_test_clion.dir/glad.c.o"

# External object files for target OPGL_test_clion
OPGL_test_clion_EXTERNAL_OBJECTS =

openl_lib/libOPGL_test_clion.dylib: openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o
openl_lib/libOPGL_test_clion.dylib: openl_lib/CMakeFiles/OPGL_test_clion.dir/build.make
openl_lib/libOPGL_test_clion.dylib: openl_lib/CMakeFiles/OPGL_test_clion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libOPGL_test_clion.dylib"
	cd "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/build/openl_lib" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OPGL_test_clion.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
openl_lib/CMakeFiles/OPGL_test_clion.dir/build: openl_lib/libOPGL_test_clion.dylib

.PHONY : openl_lib/CMakeFiles/OPGL_test_clion.dir/build

openl_lib/CMakeFiles/OPGL_test_clion.dir/requires: openl_lib/CMakeFiles/OPGL_test_clion.dir/glad.c.o.requires

.PHONY : openl_lib/CMakeFiles/OPGL_test_clion.dir/requires

openl_lib/CMakeFiles/OPGL_test_clion.dir/clean:
	cd "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/build/openl_lib" && $(CMAKE_COMMAND) -P CMakeFiles/OPGL_test_clion.dir/cmake_clean.cmake
.PHONY : openl_lib/CMakeFiles/OPGL_test_clion.dir/clean

openl_lib/CMakeFiles/OPGL_test_clion.dir/depend:
	cd "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion" "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/openl_lib" "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/build" "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/build/openl_lib" "/Users/lvjiaming/WorkSpace/untitled folder/OPGL-test-clion-learnopgl/OPGL-test-clion/build/openl_lib/CMakeFiles/OPGL_test_clion.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : openl_lib/CMakeFiles/OPGL_test_clion.dir/depend

