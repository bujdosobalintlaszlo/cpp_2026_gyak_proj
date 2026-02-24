#pragma once
#include <string>

// ============================================================================
// REQUIRED CLASSES FOR TESTS
// ============================================================================

/**
 * Item class - Represents a single inventory item
 *
 * Requirements for tests:
 * - Constructor: Item(const std::string& name, int value)
 * - getName() - Returns const std::string& (must be const method)
 * - getValue() - Returns int (must be const method)
 * - Private members: name (string), value (int)
 *
 * Tests verify:
 * - Constructor initializes name and value correctly
 * - Getters return correct values
 * - Works with zero value, high values, empty names
 */
class Item {
    // TODO: Add private members (name, value)

   public:
    // TODO: Constructor - Item(const std::string& name, int value)

    // TODO: const std::string& getName() const

    // TODO: int getValue() const
};

/**
 * Inventory class - Manages dynamic array of Item pointers
 *
 * Requirements for tests:
 * - Constructor: Inventory(int capacity) - Allocates Item** array
 * - Destructor: ~Inventory() - Deletes all items AND the array
 * - addItem(name, value) - Creates new Item, returns false if full
 * - removeItem(name) - Deletes item, shifts remaining, returns false if not found
 * - findItem(name) - Returns Item* or nullptr if not found
 * - getCount() - Returns current number of items
 * - getCapacity() - Returns maximum capacity
 *
 * Memory management requirements:
 * - Use Item** items_ (array of pointers)
 * - Initialize all pointers to nullptr in constructor
 * - Delete each Item* before deleting the array in destructor
 * - When removing, shift items to fill gap
 *
 * Tests verify:
 * - Adding items (single, multiple, full inventory)
 * - Finding items (returns correct pointer or nullptr)
 * - Removing items (shifts correctly, no memory leaks)
 * - Edge cases (empty inventory, full inventory, boundaries)
 * - Pointer safety (nullptr checks)
 *
 * Hints:
 * - Think about the order of operations in destructor
 * - Consider what happens when removing from middle of array
 * - Remember to update count_ when adding/removing
 *
 * Resources:
 * - https://en.cppreference.com/w/cpp/language/new
 * - https://en.cppreference.com/w/cpp/language/delete
 * - https://en.cppreference.com/w/cpp/language/destructor
 */
class Inventory {
    // TODO: Add private members
    // Item** items_;    // Array of Item pointers
    // int capacity_;    // Maximum number of items
    // int count_;       // Current number of items

   public:
    // TODO: Constructor - Inventory(int capacity)

    // TODO: Destructor - ~Inventory()

    // TODO: bool addItem(const std::string& name, int value)

    // TODO: bool removeItem(const std::string& name)

    // TODO: Item* findItem(const std::string& name)

    // TODO: void display() const (optional - not tested)

    // TODO: int getCount() const

    // TODO: int getCapacity() const
};
