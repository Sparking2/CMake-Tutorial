include(MakeTable.cmake)

# Add a library called MathFunctions with sources MathFunctions.cxx
add_library(MathFunctions MathFunctions.cxx)

set_property(TARGET MathFunctions PROPERTY VERSION "1.0.0")
set_property(TARGET MathFunctions PROPERTY SOVERSION "1")

# State that anybody linking to MathFunctions needs to include the
# current source directory, while MathFunctions itself doesn't.
target_include_directories( MathFunctions
                            INTERFACE
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                            $<INSTALL_INTERFACE:include>
                            )

option(USE_MYMATH "Use my math library for sqrt" ON)

if(USE_MYMATH)
    target_compile_definitions(MathFunctions PRIVATE "EXPORTING_MYMATH")

    add_library(SqrtLibrary STATIC mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h)

    target_include_directories(SqrtLibrary PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

    set_target_properties(SqrtLibrary PROPERTIES POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

    # Link SqrtLibrary to tutorial_compiler_flags
    target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)

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
install(TARGETS ${installable_libs} 
        EXPORT MathFunctionsTargets
        DESTINATION lib)
# Install the library headers to the include folder.
install(FILES MathFunctions.h DESTINATION include)