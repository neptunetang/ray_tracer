# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/neptune/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6494.38/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/neptune/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6494.38/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/neptune/Documents/cg/ray_tracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/neptune/Documents/cg/ray_tracer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/basic_ray_tracer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/basic_ray_tracer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/basic_ray_tracer.dir/flags.make

CMakeFiles/basic_ray_tracer.dir/main.cpp.o: CMakeFiles/basic_ray_tracer.dir/flags.make
CMakeFiles/basic_ray_tracer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neptune/Documents/cg/ray_tracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/basic_ray_tracer.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_ray_tracer.dir/main.cpp.o -c /home/neptune/Documents/cg/ray_tracer/main.cpp

CMakeFiles/basic_ray_tracer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_ray_tracer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neptune/Documents/cg/ray_tracer/main.cpp > CMakeFiles/basic_ray_tracer.dir/main.cpp.i

CMakeFiles/basic_ray_tracer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_ray_tracer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neptune/Documents/cg/ray_tracer/main.cpp -o CMakeFiles/basic_ray_tracer.dir/main.cpp.s

CMakeFiles/basic_ray_tracer.dir/ray.cpp.o: CMakeFiles/basic_ray_tracer.dir/flags.make
CMakeFiles/basic_ray_tracer.dir/ray.cpp.o: ../ray.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neptune/Documents/cg/ray_tracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/basic_ray_tracer.dir/ray.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_ray_tracer.dir/ray.cpp.o -c /home/neptune/Documents/cg/ray_tracer/ray.cpp

CMakeFiles/basic_ray_tracer.dir/ray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_ray_tracer.dir/ray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neptune/Documents/cg/ray_tracer/ray.cpp > CMakeFiles/basic_ray_tracer.dir/ray.cpp.i

CMakeFiles/basic_ray_tracer.dir/ray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_ray_tracer.dir/ray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neptune/Documents/cg/ray_tracer/ray.cpp -o CMakeFiles/basic_ray_tracer.dir/ray.cpp.s

CMakeFiles/basic_ray_tracer.dir/vec3.cpp.o: CMakeFiles/basic_ray_tracer.dir/flags.make
CMakeFiles/basic_ray_tracer.dir/vec3.cpp.o: ../vec3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neptune/Documents/cg/ray_tracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/basic_ray_tracer.dir/vec3.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_ray_tracer.dir/vec3.cpp.o -c /home/neptune/Documents/cg/ray_tracer/vec3.cpp

CMakeFiles/basic_ray_tracer.dir/vec3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_ray_tracer.dir/vec3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neptune/Documents/cg/ray_tracer/vec3.cpp > CMakeFiles/basic_ray_tracer.dir/vec3.cpp.i

CMakeFiles/basic_ray_tracer.dir/vec3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_ray_tracer.dir/vec3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neptune/Documents/cg/ray_tracer/vec3.cpp -o CMakeFiles/basic_ray_tracer.dir/vec3.cpp.s

CMakeFiles/basic_ray_tracer.dir/hitable.cpp.o: CMakeFiles/basic_ray_tracer.dir/flags.make
CMakeFiles/basic_ray_tracer.dir/hitable.cpp.o: ../hitable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neptune/Documents/cg/ray_tracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/basic_ray_tracer.dir/hitable.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_ray_tracer.dir/hitable.cpp.o -c /home/neptune/Documents/cg/ray_tracer/hitable.cpp

CMakeFiles/basic_ray_tracer.dir/hitable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_ray_tracer.dir/hitable.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neptune/Documents/cg/ray_tracer/hitable.cpp > CMakeFiles/basic_ray_tracer.dir/hitable.cpp.i

CMakeFiles/basic_ray_tracer.dir/hitable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_ray_tracer.dir/hitable.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neptune/Documents/cg/ray_tracer/hitable.cpp -o CMakeFiles/basic_ray_tracer.dir/hitable.cpp.s

CMakeFiles/basic_ray_tracer.dir/sphere.cpp.o: CMakeFiles/basic_ray_tracer.dir/flags.make
CMakeFiles/basic_ray_tracer.dir/sphere.cpp.o: ../sphere.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neptune/Documents/cg/ray_tracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/basic_ray_tracer.dir/sphere.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_ray_tracer.dir/sphere.cpp.o -c /home/neptune/Documents/cg/ray_tracer/sphere.cpp

CMakeFiles/basic_ray_tracer.dir/sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_ray_tracer.dir/sphere.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neptune/Documents/cg/ray_tracer/sphere.cpp > CMakeFiles/basic_ray_tracer.dir/sphere.cpp.i

CMakeFiles/basic_ray_tracer.dir/sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_ray_tracer.dir/sphere.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neptune/Documents/cg/ray_tracer/sphere.cpp -o CMakeFiles/basic_ray_tracer.dir/sphere.cpp.s

CMakeFiles/basic_ray_tracer.dir/hitable_list.cpp.o: CMakeFiles/basic_ray_tracer.dir/flags.make
CMakeFiles/basic_ray_tracer.dir/hitable_list.cpp.o: ../hitable_list.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neptune/Documents/cg/ray_tracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/basic_ray_tracer.dir/hitable_list.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_ray_tracer.dir/hitable_list.cpp.o -c /home/neptune/Documents/cg/ray_tracer/hitable_list.cpp

CMakeFiles/basic_ray_tracer.dir/hitable_list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_ray_tracer.dir/hitable_list.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neptune/Documents/cg/ray_tracer/hitable_list.cpp > CMakeFiles/basic_ray_tracer.dir/hitable_list.cpp.i

CMakeFiles/basic_ray_tracer.dir/hitable_list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_ray_tracer.dir/hitable_list.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neptune/Documents/cg/ray_tracer/hitable_list.cpp -o CMakeFiles/basic_ray_tracer.dir/hitable_list.cpp.s

CMakeFiles/basic_ray_tracer.dir/camera.cpp.o: CMakeFiles/basic_ray_tracer.dir/flags.make
CMakeFiles/basic_ray_tracer.dir/camera.cpp.o: ../camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neptune/Documents/cg/ray_tracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/basic_ray_tracer.dir/camera.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_ray_tracer.dir/camera.cpp.o -c /home/neptune/Documents/cg/ray_tracer/camera.cpp

CMakeFiles/basic_ray_tracer.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_ray_tracer.dir/camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neptune/Documents/cg/ray_tracer/camera.cpp > CMakeFiles/basic_ray_tracer.dir/camera.cpp.i

CMakeFiles/basic_ray_tracer.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_ray_tracer.dir/camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neptune/Documents/cg/ray_tracer/camera.cpp -o CMakeFiles/basic_ray_tracer.dir/camera.cpp.s

CMakeFiles/basic_ray_tracer.dir/material.cpp.o: CMakeFiles/basic_ray_tracer.dir/flags.make
CMakeFiles/basic_ray_tracer.dir/material.cpp.o: ../material.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neptune/Documents/cg/ray_tracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/basic_ray_tracer.dir/material.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_ray_tracer.dir/material.cpp.o -c /home/neptune/Documents/cg/ray_tracer/material.cpp

CMakeFiles/basic_ray_tracer.dir/material.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_ray_tracer.dir/material.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neptune/Documents/cg/ray_tracer/material.cpp > CMakeFiles/basic_ray_tracer.dir/material.cpp.i

CMakeFiles/basic_ray_tracer.dir/material.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_ray_tracer.dir/material.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neptune/Documents/cg/ray_tracer/material.cpp -o CMakeFiles/basic_ray_tracer.dir/material.cpp.s

CMakeFiles/basic_ray_tracer.dir/diffuse.cpp.o: CMakeFiles/basic_ray_tracer.dir/flags.make
CMakeFiles/basic_ray_tracer.dir/diffuse.cpp.o: ../diffuse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neptune/Documents/cg/ray_tracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/basic_ray_tracer.dir/diffuse.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_ray_tracer.dir/diffuse.cpp.o -c /home/neptune/Documents/cg/ray_tracer/diffuse.cpp

CMakeFiles/basic_ray_tracer.dir/diffuse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_ray_tracer.dir/diffuse.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neptune/Documents/cg/ray_tracer/diffuse.cpp > CMakeFiles/basic_ray_tracer.dir/diffuse.cpp.i

CMakeFiles/basic_ray_tracer.dir/diffuse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_ray_tracer.dir/diffuse.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neptune/Documents/cg/ray_tracer/diffuse.cpp -o CMakeFiles/basic_ray_tracer.dir/diffuse.cpp.s

CMakeFiles/basic_ray_tracer.dir/metal.cpp.o: CMakeFiles/basic_ray_tracer.dir/flags.make
CMakeFiles/basic_ray_tracer.dir/metal.cpp.o: ../metal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neptune/Documents/cg/ray_tracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/basic_ray_tracer.dir/metal.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/basic_ray_tracer.dir/metal.cpp.o -c /home/neptune/Documents/cg/ray_tracer/metal.cpp

CMakeFiles/basic_ray_tracer.dir/metal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/basic_ray_tracer.dir/metal.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neptune/Documents/cg/ray_tracer/metal.cpp > CMakeFiles/basic_ray_tracer.dir/metal.cpp.i

CMakeFiles/basic_ray_tracer.dir/metal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/basic_ray_tracer.dir/metal.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neptune/Documents/cg/ray_tracer/metal.cpp -o CMakeFiles/basic_ray_tracer.dir/metal.cpp.s

# Object files for target basic_ray_tracer
basic_ray_tracer_OBJECTS = \
"CMakeFiles/basic_ray_tracer.dir/main.cpp.o" \
"CMakeFiles/basic_ray_tracer.dir/ray.cpp.o" \
"CMakeFiles/basic_ray_tracer.dir/vec3.cpp.o" \
"CMakeFiles/basic_ray_tracer.dir/hitable.cpp.o" \
"CMakeFiles/basic_ray_tracer.dir/sphere.cpp.o" \
"CMakeFiles/basic_ray_tracer.dir/hitable_list.cpp.o" \
"CMakeFiles/basic_ray_tracer.dir/camera.cpp.o" \
"CMakeFiles/basic_ray_tracer.dir/material.cpp.o" \
"CMakeFiles/basic_ray_tracer.dir/diffuse.cpp.o" \
"CMakeFiles/basic_ray_tracer.dir/metal.cpp.o"

# External object files for target basic_ray_tracer
basic_ray_tracer_EXTERNAL_OBJECTS =

basic_ray_tracer: CMakeFiles/basic_ray_tracer.dir/main.cpp.o
basic_ray_tracer: CMakeFiles/basic_ray_tracer.dir/ray.cpp.o
basic_ray_tracer: CMakeFiles/basic_ray_tracer.dir/vec3.cpp.o
basic_ray_tracer: CMakeFiles/basic_ray_tracer.dir/hitable.cpp.o
basic_ray_tracer: CMakeFiles/basic_ray_tracer.dir/sphere.cpp.o
basic_ray_tracer: CMakeFiles/basic_ray_tracer.dir/hitable_list.cpp.o
basic_ray_tracer: CMakeFiles/basic_ray_tracer.dir/camera.cpp.o
basic_ray_tracer: CMakeFiles/basic_ray_tracer.dir/material.cpp.o
basic_ray_tracer: CMakeFiles/basic_ray_tracer.dir/diffuse.cpp.o
basic_ray_tracer: CMakeFiles/basic_ray_tracer.dir/metal.cpp.o
basic_ray_tracer: CMakeFiles/basic_ray_tracer.dir/build.make
basic_ray_tracer: CMakeFiles/basic_ray_tracer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/neptune/Documents/cg/ray_tracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable basic_ray_tracer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/basic_ray_tracer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/basic_ray_tracer.dir/build: basic_ray_tracer

.PHONY : CMakeFiles/basic_ray_tracer.dir/build

CMakeFiles/basic_ray_tracer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/basic_ray_tracer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/basic_ray_tracer.dir/clean

CMakeFiles/basic_ray_tracer.dir/depend:
	cd /home/neptune/Documents/cg/ray_tracer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/neptune/Documents/cg/ray_tracer /home/neptune/Documents/cg/ray_tracer /home/neptune/Documents/cg/ray_tracer/cmake-build-debug /home/neptune/Documents/cg/ray_tracer/cmake-build-debug /home/neptune/Documents/cg/ray_tracer/cmake-build-debug/CMakeFiles/basic_ray_tracer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/basic_ray_tracer.dir/depend

