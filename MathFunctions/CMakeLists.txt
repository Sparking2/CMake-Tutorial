# Add a library called MathFunctions with sources MathFunctions.cxx
#         and mysqrt.cxx
add_library(MathFunctions MathFunctions.cxx)

# TODO 1: State that anybody linking to MathFunctions needs to include the
# current source directory, while MathFunctions itself doesn't.
# Hint: Use target_include_directories with the INTERFACE keyword

option(USE_MYMATH "Use my math library for sqrt" ON)

if (USE_MYMATH)
    target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")

    add_library(SqrtLibrary STATIC mysqrt.cxx)

    # TODO 6: Link Sqrtlibrary to tutorial_compiler_flags

    target_link_libraries(MathFunctions PRIVATE SqrtLibrary)

endif()

# TODO 7: Link MathFunctions to tutorial_compiler_flags