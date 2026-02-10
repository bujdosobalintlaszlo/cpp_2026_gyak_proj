# Session 5: Crafting Classes

# Executable for spell demo
add_executable(spell_demo
    starter/main.cpp
)

# Tests
find_package(Catch2 QUIET)

if(Catch2_FOUND)
    add_executable(test_session05
        tests/test_session05.cpp
    )
    target_link_libraries(test_session05 PRIVATE Catch2::Catch2WithMain)
    
    add_test(NAME Session05_Tests COMMAND test_session05)
else()
    message(STATUS "Catch2 not found - tests for Session 5 will be skipped")
endif()
