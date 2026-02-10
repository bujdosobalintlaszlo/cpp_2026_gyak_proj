#pragma once
#include <memory>
#include <string>

// ============================================================================
// REQUIRED CLASSES FOR TESTS
// ============================================================================

/**
 * Weapon class - RAII resource management with move semantics
 *
 * Requirements for tests:
 * - Constructor: Weapon(name, damage)
 * - Move-only (no copying allowed)
 * - Destructor prints message when destroyed
 * - getName() and getDamage() getters (const methods)
 * - attack() method (const)
 *
 * Tests verify:
 * - Move construction and assignment work
 * - Copy operations are deleted
 * - Destructor is called appropriately
 * - Getters return correct values
 *
 * Hints:
 * - Use = default for move operations
 * - Use = delete for copy operations
 * - Think about what "move-only" means for resource ownership
 *
 * Resources:
 * - https://en.cppreference.com/w/cpp/language/move_constructor
 * - https://en.cppreference.com/w/cpp/language/rule_of_three
 */
class Weapon {
   private:
    // TODO: Add private members (name, damage)

   public:
    // TODO: Constructor

    // TODO: Destructor (print destruction message)

    // TODO: Move constructor
    // Weapon(Weapon&& other) noexcept = default;

    // TODO: Move assignment
    // Weapon& operator=(Weapon&& other) noexcept = default;

    // TODO: Delete copy operations
    // Weapon(const Weapon&) = delete;
    // Weapon& operator=(const Weapon&) = delete;

    // TODO: Getters (const methods)

    // TODO: void attack() const
};

/**
 * WeaponManager class - Manages collection of weapons using smart pointers
 *
 * Requirements for tests:
 * - Store weapons in std::vector<std::unique_ptr<Weapon>>
 * - addWeapon(unique_ptr) - takes ownership via move
 * - removeWeapon(name) - returns unique_ptr, transfers ownership
 * - count() - returns number of weapons
 *
 * Tests verify:
 * - Adding weapons transfers ownership
 * - Removing weapons returns ownership
 * - Weapons are properly destroyed when manager is destroyed
 * - Count is accurate
 *
 * Hints:
 * - Use std::move() to transfer unique_ptr ownership
 * - Think about what happens when unique_ptr goes out of scope
 * - Consider how to search the vector
 *
 * Resources:
 * - https://en.cppreference.com/w/cpp/memory/unique_ptr
 * - https://en.cppreference.com/w/cpp/utility/move
 */
class WeaponManager {
   private:
    // TODO: std::vector<std::unique_ptr<Weapon>> weapons_;

   public:
    // TODO: void addWeapon(std::unique_ptr<Weapon> weapon)

    // TODO: std::unique_ptr<Weapon> removeWeapon(const std::string& name)

    // TODO: size_t count() const

    // TODO: void displayAll() const
};
