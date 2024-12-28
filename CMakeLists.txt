# Set the minimum required version of CMake to be 3.15
cmake_minimum_required(VERSION 3.15)

# Create a project named Tutorial and set the project version
project(Tutorial VERSION 1.0 LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/runtime")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

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

# Install Tutorial in the bin directory
install(TARGETS Tutorial DESTINATION bin)

# Install TutorialConfig.h to the include directory
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

# enable testing
include(CTest)

# does the application run
add_test(NAME Runs COMMAND Tutorial 25)

# does the usage message work?
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

# define a function to simplify adding tests
function(do_test target arg result)
    add_test(NAME Comp${arg} COMMAND ${target} ${arg})
    set_tests_properties(Comp${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction()

# do a bunch of result based tests
do_test(Tutorial 4 "4 is 2")
do_test(Tutorial 9 "9 is 3")
do_test(Tutorial 5 "5 is 2.236")
do_test(Tutorial 7 "7 is 2.645")
do_test(Tutorial 25 "25 is 5")
do_test(Tutorial -25 "-25 is (-nan|nan|0)")
do_test(Tutorial 0.0001 "0.0001 is 0.01")

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)

install(EXPORT MathFunctionsTargets
    FILE MathFunctionsTargets.cmake
    DESTINATION lib/cmake/MathFunctions
    )

include(CMakePackageConfigHelpers)
# generate the config file that includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake"
    INSTALL_DESTINATION "lib/cmake/MathFunctions"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
    )

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake"
    VERSION "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
  DESTINATION lib/cmake/MathFunctions
  )

export(EXPORT MathFunctionsTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsTargets.cmake"
)