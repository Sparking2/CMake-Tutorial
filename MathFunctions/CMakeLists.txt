# Add a library called MathFunctions with sources MathFunctions.cxx
add_library(MathFunctions MathFunctions.cxx)

# State that anybody linking to MathFunctions needs to include the
# current source directory, while MathFunctions itself doesn't.
target_include_directories(MathFunctions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

option(USE_MYMATH "Use my math library for sqrt" ON)

if (USE_MYMATH)
    target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")

    add_library(SqrtLibrary STATIC mysqrt.cxx)

    # Link Sqrtlibrary to tutorial_compiler_flags
    target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)

    target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
endif()

# Link MathFunctions to tutorial_compiler_flags
target_link_libraries(MathFunctions PUBLIC tutorial_compiler_flags)