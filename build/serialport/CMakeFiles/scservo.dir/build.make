# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/sanghongrui/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sanghongrui/catkin_ws/build

# Include any dependencies generated for this target.
include serialport/CMakeFiles/scservo.dir/depend.make

# Include the progress variables for this target.
include serialport/CMakeFiles/scservo.dir/progress.make

# Include the compile flags for this target's objects.
include serialport/CMakeFiles/scservo.dir/flags.make

serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o: serialport/CMakeFiles/scservo.dir/flags.make
serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o: /home/sanghongrui/catkin_ws/src/serialport/src/SCS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sanghongrui/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o"
	cd /home/sanghongrui/catkin_ws/build/serialport && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/scservo.dir/src/SCS.cpp.o -c /home/sanghongrui/catkin_ws/src/serialport/src/SCS.cpp

serialport/CMakeFiles/scservo.dir/src/SCS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scservo.dir/src/SCS.cpp.i"
	cd /home/sanghongrui/catkin_ws/build/serialport && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sanghongrui/catkin_ws/src/serialport/src/SCS.cpp > CMakeFiles/scservo.dir/src/SCS.cpp.i

serialport/CMakeFiles/scservo.dir/src/SCS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scservo.dir/src/SCS.cpp.s"
	cd /home/sanghongrui/catkin_ws/build/serialport && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sanghongrui/catkin_ws/src/serialport/src/SCS.cpp -o CMakeFiles/scservo.dir/src/SCS.cpp.s

serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o.requires:

.PHONY : serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o.requires

serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o.provides: serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o.requires
	$(MAKE) -f serialport/CMakeFiles/scservo.dir/build.make serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o.provides.build
.PHONY : serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o.provides

serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o.provides.build: serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o


serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o: serialport/CMakeFiles/scservo.dir/flags.make
serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o: /home/sanghongrui/catkin_ws/src/serialport/src/SCSCL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sanghongrui/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o"
	cd /home/sanghongrui/catkin_ws/build/serialport && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/scservo.dir/src/SCSCL.cpp.o -c /home/sanghongrui/catkin_ws/src/serialport/src/SCSCL.cpp

serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scservo.dir/src/SCSCL.cpp.i"
	cd /home/sanghongrui/catkin_ws/build/serialport && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sanghongrui/catkin_ws/src/serialport/src/SCSCL.cpp > CMakeFiles/scservo.dir/src/SCSCL.cpp.i

serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scservo.dir/src/SCSCL.cpp.s"
	cd /home/sanghongrui/catkin_ws/build/serialport && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sanghongrui/catkin_ws/src/serialport/src/SCSCL.cpp -o CMakeFiles/scservo.dir/src/SCSCL.cpp.s

serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o.requires:

.PHONY : serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o.requires

serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o.provides: serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o.requires
	$(MAKE) -f serialport/CMakeFiles/scservo.dir/build.make serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o.provides.build
.PHONY : serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o.provides

serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o.provides.build: serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o


serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o: serialport/CMakeFiles/scservo.dir/flags.make
serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o: /home/sanghongrui/catkin_ws/src/serialport/src/SCSerail.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sanghongrui/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o"
	cd /home/sanghongrui/catkin_ws/build/serialport && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/scservo.dir/src/SCSerail.cpp.o -c /home/sanghongrui/catkin_ws/src/serialport/src/SCSerail.cpp

serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/scservo.dir/src/SCSerail.cpp.i"
	cd /home/sanghongrui/catkin_ws/build/serialport && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sanghongrui/catkin_ws/src/serialport/src/SCSerail.cpp > CMakeFiles/scservo.dir/src/SCSerail.cpp.i

serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/scservo.dir/src/SCSerail.cpp.s"
	cd /home/sanghongrui/catkin_ws/build/serialport && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sanghongrui/catkin_ws/src/serialport/src/SCSerail.cpp -o CMakeFiles/scservo.dir/src/SCSerail.cpp.s

serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o.requires:

.PHONY : serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o.requires

serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o.provides: serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o.requires
	$(MAKE) -f serialport/CMakeFiles/scservo.dir/build.make serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o.provides.build
.PHONY : serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o.provides

serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o.provides.build: serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o


# Object files for target scservo
scservo_OBJECTS = \
"CMakeFiles/scservo.dir/src/SCS.cpp.o" \
"CMakeFiles/scservo.dir/src/SCSCL.cpp.o" \
"CMakeFiles/scservo.dir/src/SCSerail.cpp.o"

# External object files for target scservo
scservo_EXTERNAL_OBJECTS =

/home/sanghongrui/catkin_ws/devel/lib/libscservo.so: serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o
/home/sanghongrui/catkin_ws/devel/lib/libscservo.so: serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o
/home/sanghongrui/catkin_ws/devel/lib/libscservo.so: serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o
/home/sanghongrui/catkin_ws/devel/lib/libscservo.so: serialport/CMakeFiles/scservo.dir/build.make
/home/sanghongrui/catkin_ws/devel/lib/libscservo.so: serialport/CMakeFiles/scservo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sanghongrui/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library /home/sanghongrui/catkin_ws/devel/lib/libscservo.so"
	cd /home/sanghongrui/catkin_ws/build/serialport && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/scservo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
serialport/CMakeFiles/scservo.dir/build: /home/sanghongrui/catkin_ws/devel/lib/libscservo.so

.PHONY : serialport/CMakeFiles/scservo.dir/build

serialport/CMakeFiles/scservo.dir/requires: serialport/CMakeFiles/scservo.dir/src/SCS.cpp.o.requires
serialport/CMakeFiles/scservo.dir/requires: serialport/CMakeFiles/scservo.dir/src/SCSCL.cpp.o.requires
serialport/CMakeFiles/scservo.dir/requires: serialport/CMakeFiles/scservo.dir/src/SCSerail.cpp.o.requires

.PHONY : serialport/CMakeFiles/scservo.dir/requires

serialport/CMakeFiles/scservo.dir/clean:
	cd /home/sanghongrui/catkin_ws/build/serialport && $(CMAKE_COMMAND) -P CMakeFiles/scservo.dir/cmake_clean.cmake
.PHONY : serialport/CMakeFiles/scservo.dir/clean

serialport/CMakeFiles/scservo.dir/depend:
	cd /home/sanghongrui/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sanghongrui/catkin_ws/src /home/sanghongrui/catkin_ws/src/serialport /home/sanghongrui/catkin_ws/build /home/sanghongrui/catkin_ws/build/serialport /home/sanghongrui/catkin_ws/build/serialport/CMakeFiles/scservo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : serialport/CMakeFiles/scservo.dir/depend

