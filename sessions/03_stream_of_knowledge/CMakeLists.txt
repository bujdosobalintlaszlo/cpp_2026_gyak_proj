# Session 3: Stream of Knowledge

# Executable for save/load demo
add_executable(save_load_demo
    starter/main.cpp
)

# Tests
find_package(Catch2 QUIET)

if(Catch2_FOUND)
    add_executable(test_session03
        tests/test_session03.cpp
    )
    target_link_libraries(test_session03 PRIVATE Catch2::Catch2WithMain)

    add_test(NAME Session03_Tests COMMAND test_session03)
else()
    message(STATUS "Catch2 not found - tests for Session 3 will be skipped")
endif()
