# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ilavaleev/Dev/TeacherBot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ilavaleev/Dev/TeacherBot/build

# Include any dependencies generated for this target.
include botstaff/CMakeFiles/func.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include botstaff/CMakeFiles/func.dir/compiler_depend.make

# Include the progress variables for this target.
include botstaff/CMakeFiles/func.dir/progress.make

# Include the compile flags for this target's objects.
include botstaff/CMakeFiles/func.dir/flags.make

botstaff/CMakeFiles/func.dir/src/handlers/handlers.cpp.o: botstaff/CMakeFiles/func.dir/flags.make
botstaff/CMakeFiles/func.dir/src/handlers/handlers.cpp.o: /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/handlers.cpp
botstaff/CMakeFiles/func.dir/src/handlers/handlers.cpp.o: botstaff/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object botstaff/CMakeFiles/func.dir/src/handlers/handlers.cpp.o"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT botstaff/CMakeFiles/func.dir/src/handlers/handlers.cpp.o -MF CMakeFiles/func.dir/src/handlers/handlers.cpp.o.d -o CMakeFiles/func.dir/src/handlers/handlers.cpp.o -c /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/handlers.cpp

botstaff/CMakeFiles/func.dir/src/handlers/handlers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/func.dir/src/handlers/handlers.cpp.i"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/handlers.cpp > CMakeFiles/func.dir/src/handlers/handlers.cpp.i

botstaff/CMakeFiles/func.dir/src/handlers/handlers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/func.dir/src/handlers/handlers.cpp.s"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/handlers.cpp -o CMakeFiles/func.dir/src/handlers/handlers.cpp.s

botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.o: botstaff/CMakeFiles/func.dir/flags.make
botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.o: /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/user_handlers/userHandlers.cpp
botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.o: botstaff/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.o"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.o -MF CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.o.d -o CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.o -c /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/user_handlers/userHandlers.cpp

botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.i"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/user_handlers/userHandlers.cpp > CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.i

botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.s"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/user_handlers/userHandlers.cpp -o CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.s

botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.o: botstaff/CMakeFiles/func.dir/flags.make
botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.o: /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/teacher_handlers/teacherHandlers.cpp
botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.o: botstaff/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.o"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.o -MF CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.o.d -o CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.o -c /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/teacher_handlers/teacherHandlers.cpp

botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.i"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/teacher_handlers/teacherHandlers.cpp > CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.i

botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.s"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/teacher_handlers/teacherHandlers.cpp -o CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.s

botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.o: botstaff/CMakeFiles/func.dir/flags.make
botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.o: /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/teacher_handlers/createLessonHandlers.cpp
botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.o: botstaff/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.o"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.o -MF CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.o.d -o CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.o -c /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/teacher_handlers/createLessonHandlers.cpp

botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.i"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/teacher_handlers/createLessonHandlers.cpp > CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.i

botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.s"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/teacher_handlers/createLessonHandlers.cpp -o CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.s

botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.o: botstaff/CMakeFiles/func.dir/flags.make
botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.o: /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/user_handlers/userRegistration.cpp
botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.o: botstaff/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.o"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.o -MF CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.o.d -o CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.o -c /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/user_handlers/userRegistration.cpp

botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.i"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/user_handlers/userRegistration.cpp > CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.i

botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.s"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilavaleev/Dev/TeacherBot/botstaff/src/handlers/user_handlers/userRegistration.cpp -o CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.s

botstaff/CMakeFiles/func.dir/src/commands.cpp.o: botstaff/CMakeFiles/func.dir/flags.make
botstaff/CMakeFiles/func.dir/src/commands.cpp.o: /Users/ilavaleev/Dev/TeacherBot/botstaff/src/commands.cpp
botstaff/CMakeFiles/func.dir/src/commands.cpp.o: botstaff/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object botstaff/CMakeFiles/func.dir/src/commands.cpp.o"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT botstaff/CMakeFiles/func.dir/src/commands.cpp.o -MF CMakeFiles/func.dir/src/commands.cpp.o.d -o CMakeFiles/func.dir/src/commands.cpp.o -c /Users/ilavaleev/Dev/TeacherBot/botstaff/src/commands.cpp

botstaff/CMakeFiles/func.dir/src/commands.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/func.dir/src/commands.cpp.i"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilavaleev/Dev/TeacherBot/botstaff/src/commands.cpp > CMakeFiles/func.dir/src/commands.cpp.i

botstaff/CMakeFiles/func.dir/src/commands.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/func.dir/src/commands.cpp.s"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilavaleev/Dev/TeacherBot/botstaff/src/commands.cpp -o CMakeFiles/func.dir/src/commands.cpp.s

botstaff/CMakeFiles/func.dir/src/database/psql.cpp.o: botstaff/CMakeFiles/func.dir/flags.make
botstaff/CMakeFiles/func.dir/src/database/psql.cpp.o: /Users/ilavaleev/Dev/TeacherBot/botstaff/src/database/psql.cpp
botstaff/CMakeFiles/func.dir/src/database/psql.cpp.o: botstaff/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object botstaff/CMakeFiles/func.dir/src/database/psql.cpp.o"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT botstaff/CMakeFiles/func.dir/src/database/psql.cpp.o -MF CMakeFiles/func.dir/src/database/psql.cpp.o.d -o CMakeFiles/func.dir/src/database/psql.cpp.o -c /Users/ilavaleev/Dev/TeacherBot/botstaff/src/database/psql.cpp

botstaff/CMakeFiles/func.dir/src/database/psql.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/func.dir/src/database/psql.cpp.i"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilavaleev/Dev/TeacherBot/botstaff/src/database/psql.cpp > CMakeFiles/func.dir/src/database/psql.cpp.i

botstaff/CMakeFiles/func.dir/src/database/psql.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/func.dir/src/database/psql.cpp.s"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilavaleev/Dev/TeacherBot/botstaff/src/database/psql.cpp -o CMakeFiles/func.dir/src/database/psql.cpp.s

botstaff/CMakeFiles/func.dir/src/keyboards/keyboards.cpp.o: botstaff/CMakeFiles/func.dir/flags.make
botstaff/CMakeFiles/func.dir/src/keyboards/keyboards.cpp.o: /Users/ilavaleev/Dev/TeacherBot/botstaff/src/keyboards/keyboards.cpp
botstaff/CMakeFiles/func.dir/src/keyboards/keyboards.cpp.o: botstaff/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object botstaff/CMakeFiles/func.dir/src/keyboards/keyboards.cpp.o"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT botstaff/CMakeFiles/func.dir/src/keyboards/keyboards.cpp.o -MF CMakeFiles/func.dir/src/keyboards/keyboards.cpp.o.d -o CMakeFiles/func.dir/src/keyboards/keyboards.cpp.o -c /Users/ilavaleev/Dev/TeacherBot/botstaff/src/keyboards/keyboards.cpp

botstaff/CMakeFiles/func.dir/src/keyboards/keyboards.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/func.dir/src/keyboards/keyboards.cpp.i"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilavaleev/Dev/TeacherBot/botstaff/src/keyboards/keyboards.cpp > CMakeFiles/func.dir/src/keyboards/keyboards.cpp.i

botstaff/CMakeFiles/func.dir/src/keyboards/keyboards.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/func.dir/src/keyboards/keyboards.cpp.s"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilavaleev/Dev/TeacherBot/botstaff/src/keyboards/keyboards.cpp -o CMakeFiles/func.dir/src/keyboards/keyboards.cpp.s

botstaff/CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.o: botstaff/CMakeFiles/func.dir/flags.make
botstaff/CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.o: /Users/ilavaleev/Dev/TeacherBot/botstaff/src/keyboards/teacher_keyboards/teacherKeyboards.cpp
botstaff/CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.o: botstaff/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object botstaff/CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.o"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT botstaff/CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.o -MF CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.o.d -o CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.o -c /Users/ilavaleev/Dev/TeacherBot/botstaff/src/keyboards/teacher_keyboards/teacherKeyboards.cpp

botstaff/CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.i"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilavaleev/Dev/TeacherBot/botstaff/src/keyboards/teacher_keyboards/teacherKeyboards.cpp > CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.i

botstaff/CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.s"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilavaleev/Dev/TeacherBot/botstaff/src/keyboards/teacher_keyboards/teacherKeyboards.cpp -o CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.s

botstaff/CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.o: botstaff/CMakeFiles/func.dir/flags.make
botstaff/CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.o: /Users/ilavaleev/Dev/TeacherBot/botstaff/src/keyboards/user_keyboards/userKeyboards.cpp
botstaff/CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.o: botstaff/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object botstaff/CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.o"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT botstaff/CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.o -MF CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.o.d -o CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.o -c /Users/ilavaleev/Dev/TeacherBot/botstaff/src/keyboards/user_keyboards/userKeyboards.cpp

botstaff/CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.i"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilavaleev/Dev/TeacherBot/botstaff/src/keyboards/user_keyboards/userKeyboards.cpp > CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.i

botstaff/CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.s"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilavaleev/Dev/TeacherBot/botstaff/src/keyboards/user_keyboards/userKeyboards.cpp -o CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.s

botstaff/CMakeFiles/func.dir/src/utils.cpp.o: botstaff/CMakeFiles/func.dir/flags.make
botstaff/CMakeFiles/func.dir/src/utils.cpp.o: /Users/ilavaleev/Dev/TeacherBot/botstaff/src/utils.cpp
botstaff/CMakeFiles/func.dir/src/utils.cpp.o: botstaff/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object botstaff/CMakeFiles/func.dir/src/utils.cpp.o"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT botstaff/CMakeFiles/func.dir/src/utils.cpp.o -MF CMakeFiles/func.dir/src/utils.cpp.o.d -o CMakeFiles/func.dir/src/utils.cpp.o -c /Users/ilavaleev/Dev/TeacherBot/botstaff/src/utils.cpp

botstaff/CMakeFiles/func.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/func.dir/src/utils.cpp.i"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilavaleev/Dev/TeacherBot/botstaff/src/utils.cpp > CMakeFiles/func.dir/src/utils.cpp.i

botstaff/CMakeFiles/func.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/func.dir/src/utils.cpp.s"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilavaleev/Dev/TeacherBot/botstaff/src/utils.cpp -o CMakeFiles/func.dir/src/utils.cpp.s

botstaff/CMakeFiles/func.dir/src/database/CRUD.cpp.o: botstaff/CMakeFiles/func.dir/flags.make
botstaff/CMakeFiles/func.dir/src/database/CRUD.cpp.o: /Users/ilavaleev/Dev/TeacherBot/botstaff/src/database/CRUD.cpp
botstaff/CMakeFiles/func.dir/src/database/CRUD.cpp.o: botstaff/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object botstaff/CMakeFiles/func.dir/src/database/CRUD.cpp.o"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT botstaff/CMakeFiles/func.dir/src/database/CRUD.cpp.o -MF CMakeFiles/func.dir/src/database/CRUD.cpp.o.d -o CMakeFiles/func.dir/src/database/CRUD.cpp.o -c /Users/ilavaleev/Dev/TeacherBot/botstaff/src/database/CRUD.cpp

botstaff/CMakeFiles/func.dir/src/database/CRUD.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/func.dir/src/database/CRUD.cpp.i"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ilavaleev/Dev/TeacherBot/botstaff/src/database/CRUD.cpp > CMakeFiles/func.dir/src/database/CRUD.cpp.i

botstaff/CMakeFiles/func.dir/src/database/CRUD.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/func.dir/src/database/CRUD.cpp.s"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && /usr/bin/clang $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ilavaleev/Dev/TeacherBot/botstaff/src/database/CRUD.cpp -o CMakeFiles/func.dir/src/database/CRUD.cpp.s

# Object files for target func
func_OBJECTS = \
"CMakeFiles/func.dir/src/handlers/handlers.cpp.o" \
"CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.o" \
"CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.o" \
"CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.o" \
"CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.o" \
"CMakeFiles/func.dir/src/commands.cpp.o" \
"CMakeFiles/func.dir/src/database/psql.cpp.o" \
"CMakeFiles/func.dir/src/keyboards/keyboards.cpp.o" \
"CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.o" \
"CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.o" \
"CMakeFiles/func.dir/src/utils.cpp.o" \
"CMakeFiles/func.dir/src/database/CRUD.cpp.o"

# External object files for target func
func_EXTERNAL_OBJECTS =

botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/src/handlers/handlers.cpp.o
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userHandlers.cpp.o
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/teacherHandlers.cpp.o
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/src/handlers/teacher_handlers/createLessonHandlers.cpp.o
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/src/handlers/user_handlers/userRegistration.cpp.o
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/src/commands.cpp.o
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/src/database/psql.cpp.o
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/src/keyboards/keyboards.cpp.o
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/src/keyboards/teacher_keyboards/teacherKeyboards.cpp.o
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/src/keyboards/user_keyboards/userKeyboards.cpp.o
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/src/utils.cpp.o
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/src/database/CRUD.cpp.o
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/build.make
botstaff/libfunc.a: botstaff/CMakeFiles/func.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/ilavaleev/Dev/TeacherBot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX static library libfunc.a"
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && $(CMAKE_COMMAND) -P CMakeFiles/func.dir/cmake_clean_target.cmake
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/func.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
botstaff/CMakeFiles/func.dir/build: botstaff/libfunc.a
.PHONY : botstaff/CMakeFiles/func.dir/build

botstaff/CMakeFiles/func.dir/clean:
	cd /Users/ilavaleev/Dev/TeacherBot/build/botstaff && $(CMAKE_COMMAND) -P CMakeFiles/func.dir/cmake_clean.cmake
.PHONY : botstaff/CMakeFiles/func.dir/clean

botstaff/CMakeFiles/func.dir/depend:
	cd /Users/ilavaleev/Dev/TeacherBot/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ilavaleev/Dev/TeacherBot /Users/ilavaleev/Dev/TeacherBot/botstaff /Users/ilavaleev/Dev/TeacherBot/build /Users/ilavaleev/Dev/TeacherBot/build/botstaff /Users/ilavaleev/Dev/TeacherBot/build/botstaff/CMakeFiles/func.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : botstaff/CMakeFiles/func.dir/depend

