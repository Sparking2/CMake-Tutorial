# Set the minimum required version of CMake to be 3.15
cmake_minimum_required(VERSION 3.15)

# Create a project named Tutorial and set the project version
project(Tutorial VERSION 1.0 LANGUAGES CXX)

# Creating an interface library called tutorial_compiler_flags
add_library(tutorial_compiler_flags INTERFACE)
# Add compiler feature cxx_std_11 to tutorial_compiler_flags
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)

# Create helper variables to determine which compiler we are using:
# * Create a new variable gcc_like_cxx that is true if we are using CXX and
#   any of the following compilers: ARMClang, AppleClang, Clang, GNU, LCC
# * Create a new variable msvc_cxx that is true if we are using CXX and MSVC
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

# Add warning flag compile options to the interface library tutorial_compiler_flags.
# * For gcc_like_cxx, add flags -Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused
# * For msvc_cxx, add flags -W3
target_compile_options(
    tutorial_compiler_flags INTERFACE
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
    "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# Use configure_file to configure and copy TutorialConfig.h.in to TutorialConfig.h
configure_file(TutorialConfig.h.in TutorialConfig.h)

# Use add_subdirectory() to add MathFunctions to this project
add_subdirectory(MathFunctions)

# Add an executable called Tutorial to the project
add_executable(Tutorial tutorial.cxx)

# Use target_link_libraries to link the library to our executable
# Link Tutorial to tutorial_compiler_flags
target_link_libraries(Tutorial PUBLIC MathFunctions tutorial_compiler_flags)

# Use target_include_directories to include ${PROJECT_BINARY_DIR}
# Add MathFunctions to Tutorial's target_include_directories()
target_include_directories(
    Tutorial PUBLIC 
    "${PROJECT_BINARY_DIR}" 
)