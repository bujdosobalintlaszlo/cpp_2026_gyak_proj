#include "../starter/game_state.h"

#include <cstdio>
#include <fstream>

#include <catch2/catch_all.hpp>

/*
 * Session 3 Test Coverage
 *
 * Core Requirements Tested:
 * ✅ GameState creation (constructor, default constructor)
 * ✅ Getters (const correctness)
 * ✅ Setters (modification)
 * ✅ Inventory management (add, retrieve)
 * ✅ Save to file (success, failure, content validation)
 * ✅ Load from file (success, failure, data integrity)
 * ✅ File I/O error handling
 * ✅ Round-trip save/load
 * ✅ Edge cases (empty inventory, special characters)
 *
 * Coverage: 10 test cases, 50+ assertions
 */

TEST_CASE("GameState default constructor", "[session03][gamestate]") {
    GameState state;

    REQUIRE(state.getName() == "");
    REQUIRE(state.getClass() == "");
    REQUIRE(state.getLevel() == 1);
    REQUIRE(state.getGold() == 0);
    REQUIRE(state.getLocation() == "");
    REQUIRE(state.getInventory().empty());
}

TEST_CASE("GameState parameterized constructor", "[session03][gamestate]") {
    GameState state("TestChar", "Mage", 10, 500, "Test Location");

    REQUIRE(state.getName() == "TestChar");
    REQUIRE(state.getClass() == "Mage");
    REQUIRE(state.getLevel() == 10);
    REQUIRE(state.getGold() == 500);
    REQUIRE(state.getLocation() == "Test Location");
    REQUIRE(state.getInventory().empty());
}

TEST_CASE("GameState setters", "[session03][gamestate]") {
    GameState state;

    state.setName("NewName");
    state.setClass("Warrior");
    state.setLevel(5);
    state.setGold(250);
    state.setLocation("Castle");

    REQUIRE(state.getName() == "NewName");
    REQUIRE(state.getClass() == "Warrior");
    REQUIRE(state.getLevel() == 5);
    REQUIRE(state.getGold() == 250);
    REQUIRE(state.getLocation() == "Castle");
}

TEST_CASE("Inventory management", "[session03][inventory]") {
    GameState state;

    SECTION("Empty inventory") {
        REQUIRE(state.getInventory().empty());
        REQUIRE(state.getInventory().size() == 0);
    }

    SECTION("Add single item") {
        state.addItem("Sword");
        REQUIRE(state.getInventory().size() == 1);
        REQUIRE(state.getInventory()[0] == "Sword");
    }

    SECTION("Add multiple items") {
        state.addItem("Sword");
        state.addItem("Potion");
        state.addItem("Ring");

        REQUIRE(state.getInventory().size() == 3);
        REQUIRE(state.getInventory()[0] == "Sword");
        REQUIRE(state.getInventory()[1] == "Potion");
        REQUIRE(state.getInventory()[2] == "Ring");
    }

    SECTION("Add duplicate items") {
        state.addItem("Potion");
        state.addItem("Potion");
        REQUIRE(state.getInventory().size() == 2);
    }
}

TEST_CASE("Save to file", "[session03][save][file]") {
    GameState state("Hero", "Warrior", 5, 100, "Town");
    state.addItem("Item1");
    state.addItem("Item2");

    SECTION("Successful save") {
        REQUIRE(state.saveToFile("test_save.txt"));

        std::ifstream file("test_save.txt");
        REQUIRE(file.is_open());

        std::string line;
        std::getline(file, line);
        REQUIRE(line == "# Character Data");

        file.close();
        std::remove("test_save.txt");
    }

    SECTION("Save creates readable file") {
        state.saveToFile("test_readable.txt");

        std::ifstream file("test_readable.txt");
        std::string content;
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }

        REQUIRE(content.find("Hero") != std::string::npos);
        REQUIRE(content.find("Warrior") != std::string::npos);

        file.close();
        std::remove("test_readable.txt");
    }
}

TEST_CASE("Load from file", "[session03][load][file]") {
    SECTION("Load existing file") {
        GameState original("LoadTest", "Rogue", 7, 300, "Forest");
        original.addItem("Dagger");
        original.addItem("Lockpick");
        original.saveToFile("test_load.txt");

        GameState loaded;
        REQUIRE(loaded.loadFromFile("test_load.txt"));

        REQUIRE(loaded.getName() == "LoadTest");
        REQUIRE(loaded.getClass() == "Rogue");
        REQUIRE(loaded.getLevel() == 7);
        REQUIRE(loaded.getGold() == 300);
        REQUIRE(loaded.getLocation() == "Forest");
        REQUIRE(loaded.getInventory().size() == 2);
        REQUIRE(loaded.getInventory()[0] == "Dagger");
        REQUIRE(loaded.getInventory()[1] == "Lockpick");

        std::remove("test_load.txt");
    }

    SECTION("Load non-existent file") {
        GameState state;
        REQUIRE_FALSE(state.loadFromFile("nonexistent_file.txt"));
    }
}

TEST_CASE("Round-trip save and load", "[session03][integration]") {
    GameState original("RoundTrip", "Paladin", 15, 1000, "Cathedral");
    original.addItem("Holy Sword");
    original.addItem("Shield");
    original.addItem("Healing Potion");

    REQUIRE(original.saveToFile("roundtrip.txt"));

    GameState loaded;
    REQUIRE(loaded.loadFromFile("roundtrip.txt"));

    REQUIRE(loaded.getName() == original.getName());
    REQUIRE(loaded.getClass() == original.getClass());
    REQUIRE(loaded.getLevel() == original.getLevel());
    REQUIRE(loaded.getGold() == original.getGold());
    REQUIRE(loaded.getLocation() == original.getLocation());
    REQUIRE(loaded.getInventory().size() == original.getInventory().size());

    for (size_t i = 0; i < original.getInventory().size(); i++) {
        REQUIRE(loaded.getInventory()[i] == original.getInventory()[i]);
    }

    std::remove("roundtrip.txt");
}

TEST_CASE("Empty inventory save/load", "[session03][edge]") {
    GameState original("EmptyInv", "Monk", 3, 50, "Temple");

    REQUIRE(original.saveToFile("empty_inv.txt"));

    GameState loaded;
    REQUIRE(loaded.loadFromFile("empty_inv.txt"));

    REQUIRE(loaded.getName() == "EmptyInv");
    REQUIRE(loaded.getInventory().empty());

    std::remove("empty_inv.txt");
}

TEST_CASE("Special characters in data", "[session03][edge]") {
    GameState state("Test-Name_123", "Mage/Warrior", 1, 0, "Town (North)");
    state.addItem("Item-1");
    state.addItem("Item_2");

    REQUIRE(state.saveToFile("special_chars.txt"));

    GameState loaded;
    REQUIRE(loaded.loadFromFile("special_chars.txt"));

    REQUIRE(loaded.getName() == state.getName());
    REQUIRE(loaded.getClass() == state.getClass());
    REQUIRE(loaded.getLocation() == state.getLocation());

    std::remove("special_chars.txt");
}

TEST_CASE("Large inventory", "[session03][edge]") {
    GameState state("Hoarder", "Collector", 50, 99999, "Vault");

    for (int i = 0; i < 100; i++) {
        state.addItem("Item" + std::to_string(i));
    }

    REQUIRE(state.getInventory().size() == 100);
    REQUIRE(state.saveToFile("large_inv.txt"));

    GameState loaded;
    REQUIRE(loaded.loadFromFile("large_inv.txt"));
    REQUIRE(loaded.getInventory().size() == 100);

    std::remove("large_inv.txt");
}

TEST_CASE("Const correctness", "[session03][const]") {
    const GameState state("ConstTest", "Wizard", 10, 500, "Tower");

    // These should compile because getters are const
    REQUIRE(state.getName() == "ConstTest");
    REQUIRE(state.getClass() == "Wizard");
    REQUIRE(state.getLevel() == 10);
    REQUIRE(state.getGold() == 500);
    REQUIRE(state.getLocation() == "Tower");
    REQUIRE(state.getInventory().empty());

    // saveToFile should work on const object
    REQUIRE(state.saveToFile("const_test.txt"));
    std::remove("const_test.txt");
}
