# Session 4: Guardian Spirits

# Executable for weapon demo
add_executable(weapon_demo
    starter/main.cpp
)

# Tests
find_package(Catch2 QUIET)

if(Catch2_FOUND)
    add_executable(test_session04
        tests/test_session04.cpp
    )
    target_link_libraries(test_session04 PRIVATE Catch2::Catch2WithMain)
    
    add_test(NAME Session04_Tests COMMAND test_session04)
else()
    message(STATUS "Catch2 not found - tests for Session 4 will be skipped")
endif()
