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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /afs/ir/users/r/b/rborker/CME212/Assignment6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /afs/ir/users/r/b/rborker/CME212/Assignment6/build

# Include any dependencies generated for this target.
include code/CMakeFiles/_pivcext.dir/depend.make

# Include the progress variables for this target.
include code/CMakeFiles/_pivcext.dir/progress.make

# Include the compile flags for this target's objects.
include code/CMakeFiles/_pivcext.dir/flags.make

code/pivcextPYTHON_wrap.c: ../code/pivcext.i
	$(CMAKE_COMMAND) -E cmake_progress_report /afs/ir/users/r/b/rborker/CME212/Assignment6/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Swig source"
	cd /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code && /usr/bin/cmake -E make_directory /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code
	cd /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code && /usr/bin/swig2.0 -python -outdir /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code -I/usr/include/python2.7 -I/afs/ir/users/r/b/rborker/CME212/Assignment6/code -o /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code/pivcextPYTHON_wrap.c /afs/ir/users/r/b/rborker/CME212/Assignment6/code/pivcext.i

code/pivcext.py: code/pivcextPYTHON_wrap.c

code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o: code/CMakeFiles/_pivcext.dir/flags.make
code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o: code/pivcextPYTHON_wrap.c
	$(CMAKE_COMMAND) -E cmake_progress_report /afs/ir/users/r/b/rborker/CME212/Assignment6/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o"
	cd /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o   -c /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code/pivcextPYTHON_wrap.c

code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.i"
	cd /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code/pivcextPYTHON_wrap.c > CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.i

code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.s"
	cd /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code/pivcextPYTHON_wrap.c -o CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.s

code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o.requires:
.PHONY : code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o.requires

code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o.provides: code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o.requires
	$(MAKE) -f code/CMakeFiles/_pivcext.dir/build.make code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o.provides.build
.PHONY : code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o.provides

code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o.provides.build: code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o

code/CMakeFiles/_pivcext.dir/pivcext.c.o: code/CMakeFiles/_pivcext.dir/flags.make
code/CMakeFiles/_pivcext.dir/pivcext.c.o: ../code/pivcext.c
	$(CMAKE_COMMAND) -E cmake_progress_report /afs/ir/users/r/b/rborker/CME212/Assignment6/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object code/CMakeFiles/_pivcext.dir/pivcext.c.o"
	cd /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/_pivcext.dir/pivcext.c.o   -c /afs/ir/users/r/b/rborker/CME212/Assignment6/code/pivcext.c

code/CMakeFiles/_pivcext.dir/pivcext.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/_pivcext.dir/pivcext.c.i"
	cd /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /afs/ir/users/r/b/rborker/CME212/Assignment6/code/pivcext.c > CMakeFiles/_pivcext.dir/pivcext.c.i

code/CMakeFiles/_pivcext.dir/pivcext.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/_pivcext.dir/pivcext.c.s"
	cd /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /afs/ir/users/r/b/rborker/CME212/Assignment6/code/pivcext.c -o CMakeFiles/_pivcext.dir/pivcext.c.s

code/CMakeFiles/_pivcext.dir/pivcext.c.o.requires:
.PHONY : code/CMakeFiles/_pivcext.dir/pivcext.c.o.requires

code/CMakeFiles/_pivcext.dir/pivcext.c.o.provides: code/CMakeFiles/_pivcext.dir/pivcext.c.o.requires
	$(MAKE) -f code/CMakeFiles/_pivcext.dir/build.make code/CMakeFiles/_pivcext.dir/pivcext.c.o.provides.build
.PHONY : code/CMakeFiles/_pivcext.dir/pivcext.c.o.provides

code/CMakeFiles/_pivcext.dir/pivcext.c.o.provides.build: code/CMakeFiles/_pivcext.dir/pivcext.c.o

# Object files for target _pivcext
_pivcext_OBJECTS = \
"CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o" \
"CMakeFiles/_pivcext.dir/pivcext.c.o"

# External object files for target _pivcext
_pivcext_EXTERNAL_OBJECTS =

code/_pivcext.so: code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o
code/_pivcext.so: code/CMakeFiles/_pivcext.dir/pivcext.c.o
code/_pivcext.so: code/CMakeFiles/_pivcext.dir/build.make
code/_pivcext.so: /usr/lib/x86_64-linux-gnu/libpython2.7.so
code/_pivcext.so: code/CMakeFiles/_pivcext.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared module _pivcext.so"
	cd /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_pivcext.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
code/CMakeFiles/_pivcext.dir/build: code/_pivcext.so
.PHONY : code/CMakeFiles/_pivcext.dir/build

code/CMakeFiles/_pivcext.dir/requires: code/CMakeFiles/_pivcext.dir/pivcextPYTHON_wrap.c.o.requires
code/CMakeFiles/_pivcext.dir/requires: code/CMakeFiles/_pivcext.dir/pivcext.c.o.requires
.PHONY : code/CMakeFiles/_pivcext.dir/requires

code/CMakeFiles/_pivcext.dir/clean:
	cd /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code && $(CMAKE_COMMAND) -P CMakeFiles/_pivcext.dir/cmake_clean.cmake
.PHONY : code/CMakeFiles/_pivcext.dir/clean

code/CMakeFiles/_pivcext.dir/depend: code/pivcextPYTHON_wrap.c
code/CMakeFiles/_pivcext.dir/depend: code/pivcext.py
	cd /afs/ir/users/r/b/rborker/CME212/Assignment6/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /afs/ir/users/r/b/rborker/CME212/Assignment6 /afs/ir/users/r/b/rborker/CME212/Assignment6/code /afs/ir/users/r/b/rborker/CME212/Assignment6/build /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code /afs/ir/users/r/b/rborker/CME212/Assignment6/build/code/CMakeFiles/_pivcext.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : code/CMakeFiles/_pivcext.dir/depend
