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
CMAKE_COMMAND = /snap/clion/103/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/103/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hama/work/cpp/Signer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hama/work/cpp/Signer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Signer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Signer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Signer.dir/flags.make

CMakeFiles/Signer.dir/main.cpp.o: CMakeFiles/Signer.dir/flags.make
CMakeFiles/Signer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hama/work/cpp/Signer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Signer.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Signer.dir/main.cpp.o -c /home/hama/work/cpp/Signer/main.cpp

CMakeFiles/Signer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Signer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hama/work/cpp/Signer/main.cpp > CMakeFiles/Signer.dir/main.cpp.i

CMakeFiles/Signer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Signer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hama/work/cpp/Signer/main.cpp -o CMakeFiles/Signer.dir/main.cpp.s

CMakeFiles/Signer.dir/signer.cpp.o: CMakeFiles/Signer.dir/flags.make
CMakeFiles/Signer.dir/signer.cpp.o: ../signer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hama/work/cpp/Signer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Signer.dir/signer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Signer.dir/signer.cpp.o -c /home/hama/work/cpp/Signer/signer.cpp

CMakeFiles/Signer.dir/signer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Signer.dir/signer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hama/work/cpp/Signer/signer.cpp > CMakeFiles/Signer.dir/signer.cpp.i

CMakeFiles/Signer.dir/signer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Signer.dir/signer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hama/work/cpp/Signer/signer.cpp -o CMakeFiles/Signer.dir/signer.cpp.s

CMakeFiles/Signer.dir/command.cpp.o: CMakeFiles/Signer.dir/flags.make
CMakeFiles/Signer.dir/command.cpp.o: ../command.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hama/work/cpp/Signer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Signer.dir/command.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Signer.dir/command.cpp.o -c /home/hama/work/cpp/Signer/command.cpp

CMakeFiles/Signer.dir/command.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Signer.dir/command.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hama/work/cpp/Signer/command.cpp > CMakeFiles/Signer.dir/command.cpp.i

CMakeFiles/Signer.dir/command.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Signer.dir/command.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hama/work/cpp/Signer/command.cpp -o CMakeFiles/Signer.dir/command.cpp.s

# Object files for target Signer
Signer_OBJECTS = \
"CMakeFiles/Signer.dir/main.cpp.o" \
"CMakeFiles/Signer.dir/signer.cpp.o" \
"CMakeFiles/Signer.dir/command.cpp.o"

# External object files for target Signer
Signer_EXTERNAL_OBJECTS =

Signer: CMakeFiles/Signer.dir/main.cpp.o
Signer: CMakeFiles/Signer.dir/signer.cpp.o
Signer: CMakeFiles/Signer.dir/command.cpp.o
Signer: CMakeFiles/Signer.dir/build.make
Signer: CMakeFiles/Signer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hama/work/cpp/Signer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Signer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Signer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Signer.dir/build: Signer

.PHONY : CMakeFiles/Signer.dir/build

CMakeFiles/Signer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Signer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Signer.dir/clean

CMakeFiles/Signer.dir/depend:
	cd /home/hama/work/cpp/Signer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hama/work/cpp/Signer /home/hama/work/cpp/Signer /home/hama/work/cpp/Signer/cmake-build-debug /home/hama/work/cpp/Signer/cmake-build-debug /home/hama/work/cpp/Signer/cmake-build-debug/CMakeFiles/Signer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Signer.dir/depend

