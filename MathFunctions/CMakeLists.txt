# Add a library called MathFunctions with sources MathFunctions.cxx
add_library(MathFunctions MathFunctions.cxx)

# State that anybody linking to MathFunctions needs to include the
# current source directory, while MathFunctions itself doesn't.
target_include_directories(MathFunctions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

option(USE_MYMATH "Use my math library for sqrt" ON)

if (USE_MYMATH)
    target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")

    add_library(SqrtLibrary STATIC mysqrt.cxx)

    # Link SqrtLibrary to tutorial_compiler_flags
    target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)

    # TODO 1: Include CheckCXXSourceCompiles

    # TODO 2: Use check_cxx_source_compiles with simple C++ code to verify
    # availability of:
    # * std::log
    # * std::exp
    # Store the results in HAVE_LOG and HAVE_EXP respectively.

    # Hint: Sample C++ code which uses log:
    # #include <cmath>
    # int main() {
    #   std::log(1.0);
    #   return 0;
    # }

    # TODO 3: Conditionally on HAVE_LOG and HAVE_EXP, add private compile
    # definitions "HAVE_LOG" and "HAVE_EXP" to the SqrtLibrary target.
    # Hint: Use target_compile_definitions()

    target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
endif()

# Link MathFunctions to tutorial_compiler_flags
target_link_libraries(MathFunctions PUBLIC tutorial_compiler_flags)

# Create a variable called installable_libs that is a list of all
# libraries we want to install (e.g. MathFunctions and tutorial_compiler_flags)
# Then install the installable libraries to the lib folder.
set(installable_libs MathFunctions tutorial_compiler_flags)
if(TARGET SqrtLibrary)
    list(APPEND installable_libs SqrtLibrary)
endif()
install(TARGETS ${installable_libs} DESTINATION lib)

# Install the library headers to the include folder.
install(FILES MathFunctions.h DESTINATION include)