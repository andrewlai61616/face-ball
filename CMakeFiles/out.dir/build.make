# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /home/pi/Desktop/Final_Project/face_ball

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Desktop/Final_Project/face_ball

# Include any dependencies generated for this target.
include CMakeFiles/out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/out.dir/flags.make

CMakeFiles/out.dir/track.cpp.o: CMakeFiles/out.dir/flags.make
CMakeFiles/out.dir/track.cpp.o: track.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/Final_Project/face_ball/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/out.dir/track.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/out.dir/track.cpp.o -c /home/pi/Desktop/Final_Project/face_ball/track.cpp

CMakeFiles/out.dir/track.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/out.dir/track.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/Final_Project/face_ball/track.cpp > CMakeFiles/out.dir/track.cpp.i

CMakeFiles/out.dir/track.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/out.dir/track.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/Final_Project/face_ball/track.cpp -o CMakeFiles/out.dir/track.cpp.s

CMakeFiles/out.dir/track.cpp.o.requires:

.PHONY : CMakeFiles/out.dir/track.cpp.o.requires

CMakeFiles/out.dir/track.cpp.o.provides: CMakeFiles/out.dir/track.cpp.o.requires
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/track.cpp.o.provides.build
.PHONY : CMakeFiles/out.dir/track.cpp.o.provides

CMakeFiles/out.dir/track.cpp.o.provides.build: CMakeFiles/out.dir/track.cpp.o


# Object files for target out
out_OBJECTS = \
"CMakeFiles/out.dir/track.cpp.o"

# External object files for target out
out_EXTERNAL_OBJECTS =

out: CMakeFiles/out.dir/track.cpp.o
out: CMakeFiles/out.dir/build.make
out: /usr/lib/arm-linux-gnueabihf/libopencv_videostab.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_ts.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_superres.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_stitching.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_ocl.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_gpu.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_contrib.so.2.4.9
out: /usr/local/lib/libwiringPi.so
out: /usr/lib/arm-linux-gnueabihf/libopencv_photo.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_legacy.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_video.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_objdetect.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_ml.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_calib3d.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_features2d.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_highgui.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_imgproc.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_flann.so.2.4.9
out: /usr/lib/arm-linux-gnueabihf/libopencv_core.so.2.4.9
out: CMakeFiles/out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/Final_Project/face_ball/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/out.dir/build: out

.PHONY : CMakeFiles/out.dir/build

CMakeFiles/out.dir/requires: CMakeFiles/out.dir/track.cpp.o.requires

.PHONY : CMakeFiles/out.dir/requires

CMakeFiles/out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/out.dir/clean

CMakeFiles/out.dir/depend:
	cd /home/pi/Desktop/Final_Project/face_ball && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/Final_Project/face_ball /home/pi/Desktop/Final_Project/face_ball /home/pi/Desktop/Final_Project/face_ball /home/pi/Desktop/Final_Project/face_ball /home/pi/Desktop/Final_Project/face_ball/CMakeFiles/out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/out.dir/depend
