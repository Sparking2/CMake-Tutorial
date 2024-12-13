# Add a library called MathFunctions with sources MathFunctions.cxx
#         and mysqrt.cxx
add_library(MathFunctions MathFunctions.cxx)

option(USE_MYMATH "Use my math library for sqrt" ON)

if (USE_MYMATH)
    target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")

    add_library(SqrtLibrary STATIC mysqrt.cxx)

    # TODO 6: Link Sqrtlibrary to tutorial_compiler_flags

    target_link_libraries(MathFunctions PRIVATE SqrtLibrary)

endif()