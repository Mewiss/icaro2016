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
CMAKE_SOURCE_DIR = /home/pi/codes/icaro2016/Larc2016/logos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/codes/icaro2016/Larc2016/logos

# Include any dependencies generated for this target.
include CMakeFiles/template.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/template.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/template.dir/flags.make

CMakeFiles/template.dir/match.cpp.o: CMakeFiles/template.dir/flags.make
CMakeFiles/template.dir/match.cpp.o: match.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/codes/icaro2016/Larc2016/logos/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/template.dir/match.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/template.dir/match.cpp.o -c /home/pi/codes/icaro2016/Larc2016/logos/match.cpp

CMakeFiles/template.dir/match.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/template.dir/match.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/codes/icaro2016/Larc2016/logos/match.cpp > CMakeFiles/template.dir/match.cpp.i

CMakeFiles/template.dir/match.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/template.dir/match.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/codes/icaro2016/Larc2016/logos/match.cpp -o CMakeFiles/template.dir/match.cpp.s

CMakeFiles/template.dir/match.cpp.o.requires:
.PHONY : CMakeFiles/template.dir/match.cpp.o.requires

CMakeFiles/template.dir/match.cpp.o.provides: CMakeFiles/template.dir/match.cpp.o.requires
	$(MAKE) -f CMakeFiles/template.dir/build.make CMakeFiles/template.dir/match.cpp.o.provides.build
.PHONY : CMakeFiles/template.dir/match.cpp.o.provides

CMakeFiles/template.dir/match.cpp.o.provides.build: CMakeFiles/template.dir/match.cpp.o

# Object files for target template
template_OBJECTS = \
"CMakeFiles/template.dir/match.cpp.o"

# External object files for target template
template_EXTERNAL_OBJECTS =

template: CMakeFiles/template.dir/match.cpp.o
template: CMakeFiles/template.dir/build.make
template: /opt/vc/lib/libmmal_core.so
template: /opt/vc/lib/libmmal_util.so
template: /opt/vc/lib/libmmal.so
template: /usr/local/lib/libopencv_calib3d.so.3.1.0
template: /usr/local/lib/libopencv_core.so.3.1.0
template: /usr/local/lib/libopencv_features2d.so.3.1.0
template: /usr/local/lib/libopencv_flann.so.3.1.0
template: /usr/local/lib/libopencv_highgui.so.3.1.0
template: /usr/local/lib/libopencv_imgcodecs.so.3.1.0
template: /usr/local/lib/libopencv_imgproc.so.3.1.0
template: /usr/local/lib/libopencv_ml.so.3.1.0
template: /usr/local/lib/libopencv_objdetect.so.3.1.0
template: /usr/local/lib/libopencv_photo.so.3.1.0
template: /usr/local/lib/libopencv_shape.so.3.1.0
template: /usr/local/lib/libopencv_stitching.so.3.1.0
template: /usr/local/lib/libopencv_superres.so.3.1.0
template: /usr/local/lib/libopencv_video.so.3.1.0
template: /usr/local/lib/libopencv_videoio.so.3.1.0
template: /usr/local/lib/libopencv_videostab.so.3.1.0
template: /usr/local/lib/libopencv_objdetect.so.3.1.0
template: /usr/local/lib/libopencv_calib3d.so.3.1.0
template: /usr/local/lib/libopencv_features2d.so.3.1.0
template: /usr/local/lib/libopencv_flann.so.3.1.0
template: /usr/local/lib/libopencv_highgui.so.3.1.0
template: /usr/local/lib/libopencv_ml.so.3.1.0
template: /usr/local/lib/libopencv_photo.so.3.1.0
template: /usr/local/lib/libopencv_video.so.3.1.0
template: /usr/local/lib/libopencv_videoio.so.3.1.0
template: /usr/local/lib/libopencv_imgcodecs.so.3.1.0
template: /usr/local/lib/libopencv_imgproc.so.3.1.0
template: /usr/local/lib/libopencv_core.so.3.1.0
template: CMakeFiles/template.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable template"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/template.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/template.dir/build: template
.PHONY : CMakeFiles/template.dir/build

CMakeFiles/template.dir/requires: CMakeFiles/template.dir/match.cpp.o.requires
.PHONY : CMakeFiles/template.dir/requires

CMakeFiles/template.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/template.dir/cmake_clean.cmake
.PHONY : CMakeFiles/template.dir/clean

CMakeFiles/template.dir/depend:
	cd /home/pi/codes/icaro2016/Larc2016/logos && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/codes/icaro2016/Larc2016/logos /home/pi/codes/icaro2016/Larc2016/logos /home/pi/codes/icaro2016/Larc2016/logos /home/pi/codes/icaro2016/Larc2016/logos /home/pi/codes/icaro2016/Larc2016/logos/CMakeFiles/template.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/template.dir/depend

