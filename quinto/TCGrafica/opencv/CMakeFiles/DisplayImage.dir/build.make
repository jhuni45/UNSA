# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv

# Include any dependencies generated for this target.
include CMakeFiles/DisplayImage.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DisplayImage.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DisplayImage.dir/flags.make

CMakeFiles/DisplayImage.dir/filtros.cpp.o: CMakeFiles/DisplayImage.dir/flags.make
CMakeFiles/DisplayImage.dir/filtros.cpp.o: filtros.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DisplayImage.dir/filtros.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DisplayImage.dir/filtros.cpp.o -c /home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv/filtros.cpp

CMakeFiles/DisplayImage.dir/filtros.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DisplayImage.dir/filtros.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv/filtros.cpp > CMakeFiles/DisplayImage.dir/filtros.cpp.i

CMakeFiles/DisplayImage.dir/filtros.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DisplayImage.dir/filtros.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv/filtros.cpp -o CMakeFiles/DisplayImage.dir/filtros.cpp.s

CMakeFiles/DisplayImage.dir/filtros.cpp.o.requires:

.PHONY : CMakeFiles/DisplayImage.dir/filtros.cpp.o.requires

CMakeFiles/DisplayImage.dir/filtros.cpp.o.provides: CMakeFiles/DisplayImage.dir/filtros.cpp.o.requires
	$(MAKE) -f CMakeFiles/DisplayImage.dir/build.make CMakeFiles/DisplayImage.dir/filtros.cpp.o.provides.build
.PHONY : CMakeFiles/DisplayImage.dir/filtros.cpp.o.provides

CMakeFiles/DisplayImage.dir/filtros.cpp.o.provides.build: CMakeFiles/DisplayImage.dir/filtros.cpp.o


# Object files for target DisplayImage
DisplayImage_OBJECTS = \
"CMakeFiles/DisplayImage.dir/filtros.cpp.o"

# External object files for target DisplayImage
DisplayImage_EXTERNAL_OBJECTS =

DisplayImage: CMakeFiles/DisplayImage.dir/filtros.cpp.o
DisplayImage: CMakeFiles/DisplayImage.dir/build.make
DisplayImage: /usr/local/lib/libopencv_dnn.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_gapi.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_highgui.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_ml.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_objdetect.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_photo.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_stitching.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_video.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_videoio.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_imgcodecs.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_calib3d.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_features2d.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_flann.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_imgproc.so.4.3.0
DisplayImage: /usr/local/lib/libopencv_core.so.4.3.0
DisplayImage: CMakeFiles/DisplayImage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DisplayImage"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DisplayImage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DisplayImage.dir/build: DisplayImage

.PHONY : CMakeFiles/DisplayImage.dir/build

CMakeFiles/DisplayImage.dir/requires: CMakeFiles/DisplayImage.dir/filtros.cpp.o.requires

.PHONY : CMakeFiles/DisplayImage.dir/requires

CMakeFiles/DisplayImage.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DisplayImage.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DisplayImage.dir/clean

CMakeFiles/DisplayImage.dir/depend:
	cd /home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv /home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv /home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv /home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv /home/jhunior/Documentos/UNSA/quinto/TCGrafica/opencv/CMakeFiles/DisplayImage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DisplayImage.dir/depend

