# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/pi/workspace/Larc2016/Vacas

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/workspace/Larc2016/Vacas

# Include any dependencies generated for this target.
include CMakeFiles/vacas.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vacas.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vacas.dir/flags.make

CMakeFiles/vacas.dir/vacas.cpp.o: CMakeFiles/vacas.dir/flags.make
CMakeFiles/vacas.dir/vacas.cpp.o: vacas.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/workspace/Larc2016/Vacas/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/vacas.dir/vacas.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/vacas.dir/vacas.cpp.o -c /home/pi/workspace/Larc2016/Vacas/vacas.cpp

CMakeFiles/vacas.dir/vacas.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vacas.dir/vacas.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/workspace/Larc2016/Vacas/vacas.cpp > CMakeFiles/vacas.dir/vacas.cpp.i

CMakeFiles/vacas.dir/vacas.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vacas.dir/vacas.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/workspace/Larc2016/Vacas/vacas.cpp -o CMakeFiles/vacas.dir/vacas.cpp.s

CMakeFiles/vacas.dir/vacas.cpp.o.requires:
.PHONY : CMakeFiles/vacas.dir/vacas.cpp.o.requires

CMakeFiles/vacas.dir/vacas.cpp.o.provides: CMakeFiles/vacas.dir/vacas.cpp.o.requires
	$(MAKE) -f CMakeFiles/vacas.dir/build.make CMakeFiles/vacas.dir/vacas.cpp.o.provides.build
.PHONY : CMakeFiles/vacas.dir/vacas.cpp.o.provides

CMakeFiles/vacas.dir/vacas.cpp.o.provides.build: CMakeFiles/vacas.dir/vacas.cpp.o

# Object files for target vacas
vacas_OBJECTS = \
"CMakeFiles/vacas.dir/vacas.cpp.o"

# External object files for target vacas
vacas_EXTERNAL_OBJECTS =

vacas: CMakeFiles/vacas.dir/vacas.cpp.o
vacas: CMakeFiles/vacas.dir/build.make
vacas: /opt/vc/lib/libmmal_core.so
vacas: /opt/vc/lib/libmmal_util.so
vacas: /opt/vc/lib/libmmal.so
vacas: /usr/local/lib/libopencv_xphoto.so.3.0.0
vacas: /usr/local/lib/libopencv_xobjdetect.so.3.0.0
vacas: /usr/local/lib/libopencv_ximgproc.so.3.0.0
vacas: /usr/local/lib/libopencv_xfeatures2d.so.3.0.0
vacas: /usr/local/lib/libopencv_tracking.so.3.0.0
vacas: /usr/local/lib/libopencv_text.so.3.0.0
vacas: /usr/local/lib/libopencv_surface_matching.so.3.0.0
vacas: /usr/local/lib/libopencv_saliency.so.3.0.0
vacas: /usr/local/lib/libopencv_rgbd.so.3.0.0
vacas: /usr/local/lib/libopencv_reg.so.3.0.0
vacas: /usr/local/lib/libopencv_optflow.so.3.0.0
vacas: /usr/local/lib/libopencv_line_descriptor.so.3.0.0
vacas: /usr/local/lib/libopencv_latentsvm.so.3.0.0
vacas: /usr/local/lib/libopencv_face.so.3.0.0
vacas: /usr/local/lib/libopencv_datasets.so.3.0.0
vacas: /usr/local/lib/libopencv_ccalib.so.3.0.0
vacas: /usr/local/lib/libopencv_bioinspired.so.3.0.0
vacas: /usr/local/lib/libopencv_bgsegm.so.3.0.0
vacas: /usr/local/lib/libopencv_adas.so.3.0.0
vacas: /usr/local/lib/libopencv_videostab.so.3.0.0
vacas: /usr/local/lib/libopencv_videoio.so.3.0.0
vacas: /usr/local/lib/libopencv_video.so.3.0.0
vacas: /usr/local/lib/libopencv_superres.so.3.0.0
vacas: /usr/local/lib/libopencv_stitching.so.3.0.0
vacas: /usr/local/lib/libopencv_shape.so.3.0.0
vacas: /usr/local/lib/libopencv_photo.so.3.0.0
vacas: /usr/local/lib/libopencv_objdetect.so.3.0.0
vacas: /usr/local/lib/libopencv_ml.so.3.0.0
vacas: /usr/local/lib/libopencv_imgproc.so.3.0.0
vacas: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
vacas: /usr/local/lib/libopencv_highgui.so.3.0.0
vacas: /usr/local/lib/libopencv_hal.a
vacas: /usr/local/lib/libopencv_flann.so.3.0.0
vacas: /usr/local/lib/libopencv_features2d.so.3.0.0
vacas: /usr/local/lib/libopencv_core.so.3.0.0
vacas: /usr/local/lib/libopencv_calib3d.so.3.0.0
vacas: /usr/local/lib/libopencv_text.so.3.0.0
vacas: /usr/local/lib/libopencv_face.so.3.0.0
vacas: /usr/local/lib/libopencv_xobjdetect.so.3.0.0
vacas: /usr/local/lib/libopencv_xfeatures2d.so.3.0.0
vacas: /usr/local/lib/libopencv_shape.so.3.0.0
vacas: /usr/local/lib/libopencv_video.so.3.0.0
vacas: /usr/local/lib/libopencv_calib3d.so.3.0.0
vacas: /usr/local/lib/libopencv_features2d.so.3.0.0
vacas: /usr/local/lib/libopencv_ml.so.3.0.0
vacas: /usr/local/lib/libopencv_highgui.so.3.0.0
vacas: /usr/local/lib/libopencv_videoio.so.3.0.0
vacas: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
vacas: /usr/local/lib/libopencv_imgproc.so.3.0.0
vacas: /usr/local/lib/libopencv_flann.so.3.0.0
vacas: /usr/local/lib/libopencv_core.so.3.0.0
vacas: /usr/local/lib/libopencv_hal.a
vacas: CMakeFiles/vacas.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable vacas"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vacas.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vacas.dir/build: vacas
.PHONY : CMakeFiles/vacas.dir/build

CMakeFiles/vacas.dir/requires: CMakeFiles/vacas.dir/vacas.cpp.o.requires
.PHONY : CMakeFiles/vacas.dir/requires

CMakeFiles/vacas.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vacas.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vacas.dir/clean

CMakeFiles/vacas.dir/depend:
	cd /home/pi/workspace/Larc2016/Vacas && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/workspace/Larc2016/Vacas /home/pi/workspace/Larc2016/Vacas /home/pi/workspace/Larc2016/Vacas /home/pi/workspace/Larc2016/Vacas /home/pi/workspace/Larc2016/Vacas/CMakeFiles/vacas.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vacas.dir/depend

