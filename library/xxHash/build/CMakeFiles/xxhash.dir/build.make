# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/tom/xxHash/cmake_unofficial

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tom/xxHash/build

# Include any dependencies generated for this target.
include CMakeFiles/xxhash.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/xxhash.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/xxhash.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/xxhash.dir/flags.make

CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.o: CMakeFiles/xxhash.dir/flags.make
CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.o: /home/tom/xxHash/xxhash.c
CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.o: CMakeFiles/xxhash.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tom/xxHash/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.o -MF CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.o.d -o CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.o -c /home/tom/xxHash/xxhash.c

CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom/xxHash/xxhash.c > CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.i

CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom/xxHash/xxhash.c -o CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.s

# Object files for target xxhash
xxhash_OBJECTS = \
"CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.o"

# External object files for target xxhash
xxhash_EXTERNAL_OBJECTS =

libxxhash.so.0.8.2: CMakeFiles/xxhash.dir/home/tom/xxHash/xxhash.c.o
libxxhash.so.0.8.2: CMakeFiles/xxhash.dir/build.make
libxxhash.so.0.8.2: CMakeFiles/xxhash.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/tom/xxHash/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libxxhash.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xxhash.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library libxxhash.so.0.8.2 libxxhash.so.0 libxxhash.so

libxxhash.so.0: libxxhash.so.0.8.2
	@$(CMAKE_COMMAND) -E touch_nocreate libxxhash.so.0

libxxhash.so: libxxhash.so.0.8.2
	@$(CMAKE_COMMAND) -E touch_nocreate libxxhash.so

# Rule to build all files generated by this target.
CMakeFiles/xxhash.dir/build: libxxhash.so
.PHONY : CMakeFiles/xxhash.dir/build

CMakeFiles/xxhash.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/xxhash.dir/cmake_clean.cmake
.PHONY : CMakeFiles/xxhash.dir/clean

CMakeFiles/xxhash.dir/depend:
	cd /home/tom/xxHash/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tom/xxHash/cmake_unofficial /home/tom/xxHash/cmake_unofficial /home/tom/xxHash/build /home/tom/xxHash/build /home/tom/xxHash/build/CMakeFiles/xxhash.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/xxhash.dir/depend
