# Session 6: Hidden Implementation

# Executable for engine demo
add_executable(engine_demo
    starter/main.cpp
    starter/game_engine.cpp
)

# Tests
find_package(Catch2 QUIET)

if(Catch2_FOUND)
    add_executable(test_session06
        tests/test_session06.cpp
        starter/game_engine.cpp
    )
    target_link_libraries(test_session06 PRIVATE Catch2::Catch2WithMain)
    
    add_test(NAME Session06_Tests COMMAND test_session06)
else()
    message(STATUS "Catch2 not found - tests for Session 6 will be skipped")
endif()
