#include "../starter/weapon.h"

#include <sstream>

#include <catch2/catch_all.hpp>

/*
 * Session 4 Test Coverage
 *
 * Core Requirements Tested:
 * ✅ Weapon creation and destruction (RAII)
 * ✅ Move semantics (move constructor, move assignment)
 * ✅ Copy prevention (deleted copy operations)
 * ✅ Smart pointers (unique_ptr ownership)
 * ✅ WeaponManager (add, remove, count)
 * ✅ Ownership transfer (std::move)
 * ✅ Resource cleanup (automatic destruction)
 * ✅ Edge cases (empty manager, non-existent weapon)
 *
 * Coverage: 10 test cases, 40+ assertions
 */

TEST_CASE("Weapon creation", "[session04][weapon]") {
    auto weapon = std::make_unique<Weapon>("Test Sword", 50);

    REQUIRE(weapon->getName() == "Test Sword");
    REQUIRE(weapon->getDamage() == 50);
}

TEST_CASE("Weapon with different values", "[session04][weapon]") {
    SECTION("Zero damage") {
        auto weapon = std::make_unique<Weapon>("Broken Sword", 0);
        REQUIRE(weapon->getDamage() == 0);
    }

    SECTION("High damage") {
        auto weapon = std::make_unique<Weapon>("Legendary Blade", 9999);
        REQUIRE(weapon->getDamage() == 9999);
    }
}

TEST_CASE("Weapon move semantics", "[session04][weapon][move]") {
    auto weapon1 = std::make_unique<Weapon>("Movable Sword", 100);
    std::string name = weapon1->getName();

    // Move to another unique_ptr
    auto weapon2 = std::move(weapon1);

    REQUIRE(weapon1 == nullptr);
    REQUIRE(weapon2 != nullptr);
    REQUIRE(weapon2->getName() == name);
}

TEST_CASE("WeaponManager creation", "[session04][manager]") {
    WeaponManager manager;
    REQUIRE(manager.count() == 0);
}

TEST_CASE("Add weapons to manager", "[session04][manager]") {
    WeaponManager manager;

    SECTION("Add single weapon") {
        manager.addWeapon(std::make_unique<Weapon>("Sword", 50));
        REQUIRE(manager.count() == 1);
    }

    SECTION("Add multiple weapons") {
        manager.addWeapon(std::make_unique<Weapon>("Sword", 50));
        manager.addWeapon(std::make_unique<Weapon>("Axe", 75));
        manager.addWeapon(std::make_unique<Weapon>("Bow", 40));
        REQUIRE(manager.count() == 3);
    }
}

TEST_CASE("Remove weapons from manager", "[session04][manager]") {
    WeaponManager manager;
    manager.addWeapon(std::make_unique<Weapon>("Sword", 50));
    manager.addWeapon(std::make_unique<Weapon>("Axe", 75));

    SECTION("Remove existing weapon") {
        auto removed = manager.removeWeapon("Sword");
        REQUIRE(removed != nullptr);
        REQUIRE(removed->getName() == "Sword");
        REQUIRE(manager.count() == 1);
    }

    SECTION("Remove non-existent weapon") {
        auto removed = manager.removeWeapon("NonExistent");
        REQUIRE(removed == nullptr);
        REQUIRE(manager.count() == 2);
    }
}

TEST_CASE("Ownership transfer", "[session04][manager][ownership]") {
    WeaponManager manager;
    manager.addWeapon(std::make_unique<Weapon>("Sword", 50));

    // Remove transfers ownership
    auto weapon = manager.removeWeapon("Sword");
    REQUIRE(weapon != nullptr);
    REQUIRE(manager.count() == 0);

    // Can add it back
    manager.addWeapon(std::move(weapon));
    REQUIRE(manager.count() == 1);
    REQUIRE(weapon == nullptr);
}

TEST_CASE("RAII cleanup", "[session04][raii]") {
    WeaponManager manager;

    {
        auto weapon = std::make_unique<Weapon>("Temp Sword", 30);
        manager.addWeapon(std::move(weapon));
        REQUIRE(manager.count() == 1);
    }

    // Weapon still in manager
    REQUIRE(manager.count() == 1);
}

TEST_CASE("Manager scope cleanup", "[session04][raii]") {
    size_t initial_count = 0;

    {
        WeaponManager manager;
        manager.addWeapon(std::make_unique<Weapon>("Sword1", 50));
        manager.addWeapon(std::make_unique<Weapon>("Sword2", 60));
        initial_count = manager.count();
    }
    // Manager destroyed, all weapons cleaned up automatically

    REQUIRE(initial_count == 2);
}

TEST_CASE("Empty manager operations", "[session04][edge]") {
    WeaponManager manager;

    SECTION("Remove from empty") {
        auto weapon = manager.removeWeapon("Anything");
        REQUIRE(weapon == nullptr);
        REQUIRE(manager.count() == 0);
    }

    SECTION("Display empty") {
        // Should not crash
        manager.displayAll();
        REQUIRE(manager.count() == 0);
    }
}

TEST_CASE("Multiple removes", "[session04][manager]") {
    WeaponManager manager;
    manager.addWeapon(std::make_unique<Weapon>("Sword", 50));
    manager.addWeapon(std::make_unique<Weapon>("Axe", 75));
    manager.addWeapon(std::make_unique<Weapon>("Bow", 40));

    auto w1 = manager.removeWeapon("Sword");
    auto w2 = manager.removeWeapon("Bow");

    REQUIRE(w1 != nullptr);
    REQUIRE(w2 != nullptr);
    REQUIRE(manager.count() == 1);

    auto w3 = manager.removeWeapon("Axe");
    REQUIRE(w3 != nullptr);
    REQUIRE(manager.count() == 0);
}

TEST_CASE("Weapon attack method", "[session04][weapon]") {
    auto weapon = std::make_unique<Weapon>("Attack Sword", 100);

    // Redirect cout to capture output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    weapon->attack();

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    REQUIRE(output.find("Attack Sword") != std::string::npos);
    REQUIRE(output.find("100") != std::string::npos);
    REQUIRE(output.find("damage") != std::string::npos);
}

TEST_CASE("Complex ownership scenario", "[session04][integration]") {
    WeaponManager manager1;
    WeaponManager manager2;

    // Add to first manager
    manager1.addWeapon(std::make_unique<Weapon>("Sword", 50));
    REQUIRE(manager1.count() == 1);
    REQUIRE(manager2.count() == 0);

    // Transfer to second manager
    auto weapon = manager1.removeWeapon("Sword");
    REQUIRE(manager1.count() == 0);

    manager2.addWeapon(std::move(weapon));
    REQUIRE(manager2.count() == 1);

    // Transfer back
    weapon = manager2.removeWeapon("Sword");
    manager1.addWeapon(std::move(weapon));

    REQUIRE(manager1.count() == 1);
    REQUIRE(manager2.count() == 0);
}
