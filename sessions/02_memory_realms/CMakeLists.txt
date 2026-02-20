# Session 2: Memory Realms

# Executable for inventory demo
add_executable(inventory_demo
    starter/main.cpp
)

# Tests
find_package(Catch2 QUIET)

if(Catch2_FOUND)
    add_executable(test_session02
        tests/test_session02.cpp
		  starter/Inventory.cpp
		  starter/Item.cpp
    )
    target_link_libraries(test_session02 PRIVATE Catch2::Catch2WithMain)
    
    add_test(NAME Session02_Tests COMMAND test_session02)
else()
    message(STATUS "Catch2 not found - tests for Session 2 will be skipped")
endif()
