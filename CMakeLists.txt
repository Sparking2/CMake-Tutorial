# Set the minimum required version of CMake to be 3.10
cmake_minimum_required(VERSION 3.10)

# Create a project named Tutorial and set the project version
project(Tutorial VERSION 1.0 LANGUAGES CXX)

# Set the variable CMAKE_CXX_STANDARD to 11
set(CMAKE_CXX_STANDARD 11)
# Set the variable CMAKE_CXX_STANDARD_REQUIRED to True
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Use configure_file to configure and copy TutorialConfig.h.in to TutorialConfig.h
configure_file(TutorialConfig.h.in TutorialConfig.h)

# TODO 2:   Use add_subdirectory() to add MathFunctions to this project

# Add an executable called Tutorial to the project
add_executable(Tutorial tutorial.cxx)

# TODO 3:   Use target_link_libraries to link the library to our executable

# TODO 4:   Add MathFunctions to Tutorial's target_include_directories()
# Hint:     ${PROJECT_SOURCE_DIR} is a path to the project source. AKA This folder!

# Use target_include_directories to include ${PROJECT_BINARY_DIR}
target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")