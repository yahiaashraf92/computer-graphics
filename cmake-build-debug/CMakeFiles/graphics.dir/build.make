# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Users\lenovo\Desktop\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Users\lenovo\Desktop\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\lenovo\Desktop\complete graphics"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\lenovo\Desktop\complete graphics\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/graphics.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/graphics.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/graphics.dir/flags.make

CMakeFiles/graphics.dir/Computer-Graphics/main.cpp.obj: CMakeFiles/graphics.dir/flags.make
CMakeFiles/graphics.dir/Computer-Graphics/main.cpp.obj: CMakeFiles/graphics.dir/includes_CXX.rsp
CMakeFiles/graphics.dir/Computer-Graphics/main.cpp.obj: ../Computer-Graphics/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\lenovo\Desktop\complete graphics\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/graphics.dir/Computer-Graphics/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\graphics.dir\Computer-Graphics\main.cpp.obj -c "C:\Users\lenovo\Desktop\complete graphics\Computer-Graphics\main.cpp"

CMakeFiles/graphics.dir/Computer-Graphics/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphics.dir/Computer-Graphics/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\lenovo\Desktop\complete graphics\Computer-Graphics\main.cpp" > CMakeFiles\graphics.dir\Computer-Graphics\main.cpp.i

CMakeFiles/graphics.dir/Computer-Graphics/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphics.dir/Computer-Graphics/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\lenovo\Desktop\complete graphics\Computer-Graphics\main.cpp" -o CMakeFiles\graphics.dir\Computer-Graphics\main.cpp.s

# Object files for target graphics
graphics_OBJECTS = \
"CMakeFiles/graphics.dir/Computer-Graphics/main.cpp.obj"

# External object files for target graphics
graphics_EXTERNAL_OBJECTS =

graphics.exe: CMakeFiles/graphics.dir/Computer-Graphics/main.cpp.obj
graphics.exe: CMakeFiles/graphics.dir/build.make
graphics.exe: CMakeFiles/graphics.dir/linklibs.rsp
graphics.exe: CMakeFiles/graphics.dir/objects1.rsp
graphics.exe: CMakeFiles/graphics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\lenovo\Desktop\complete graphics\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable graphics.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\graphics.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/graphics.dir/build: graphics.exe
.PHONY : CMakeFiles/graphics.dir/build

CMakeFiles/graphics.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\graphics.dir\cmake_clean.cmake
.PHONY : CMakeFiles/graphics.dir/clean

CMakeFiles/graphics.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\lenovo\Desktop\complete graphics" "C:\Users\lenovo\Desktop\complete graphics" "C:\Users\lenovo\Desktop\complete graphics\cmake-build-debug" "C:\Users\lenovo\Desktop\complete graphics\cmake-build-debug" "C:\Users\lenovo\Desktop\complete graphics\cmake-build-debug\CMakeFiles\graphics.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/graphics.dir/depend

