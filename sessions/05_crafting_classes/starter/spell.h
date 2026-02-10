#pragma once
#include <string>
#include <vector>

// ============================================================================
// REQUIRED TYPES AND CLASSES FOR TESTS
// ============================================================================

/**
 * SpellType enum - Categories of spells
 *
 * Requirements for tests:
 * - DAMAGE, HEALING, BUFF
 */
// TODO: Define SpellType enum

/**
 * Spell class - Represents a magical spell
 *
 * Requirements for tests:
 * - Constructor: Spell(name, manaCost, power, type)
 * - Use member initializer list
 * - Const getters: getName(), getManaCost(), getPower(), getType()
 * - canCast(availableMana) - returns bool
 * - cast() - returns power value
 *
 * Tests verify:
 * - Constructor initializes all members correctly
 * - Getters return correct values
 * - canCast checks mana correctly
 * - All getters are const methods
 *
 * Hints:
 * - Member initializer list is more efficient than assignment in body
 * - Const methods promise not to modify the object
 *
 * Resources:
 * - https://en.cppreference.com/w/cpp/language/constructor
 * - https://en.cppreference.com/w/cpp/language/const
 */
class Spell {
   private:
    // TODO: Add private members (name, manaCost, power, type)

   public:
    // TODO: Constructor with member initializer list

    // TODO: Const getters

    // TODO: bool canCast(int availableMana) const

    // TODO: int cast() const
};

/**
 * SpellBook class - Collection of spells with capacity limit
 *
 * Requirements for tests:
 * - Constructor: SpellBook(maxSpells)
 * - addSpell(spell) - returns bool (false if full)
 * - findSpell(name) - returns const Spell* (nullptr if not found)
 * - getSpellCount() - returns current count
 * - isFull() - returns bool
 *
 * Tests verify:
 * - Adding spells up to capacity
 * - Rejecting spells when full
 * - Finding spells by name
 * - Count is accurate
 *
 * Hints:
 * - Store spells in std::vector
 * - Think about how to search the vector
 * - Consider returning pointer vs reference for findSpell
 *
 * Resources:
 * - https://en.cppreference.com/w/cpp/container/vector
 * - https://en.cppreference.com/w/cpp/algorithm/find_if
 */
class SpellBook {
   private:
    // TODO: Add private members (spells vector, maxSpells)

   public:
    // TODO: Constructor

    // TODO: bool addSpell(const Spell& spell)

    // TODO: const Spell* findSpell(const std::string& name) const

    // TODO: size_t getSpellCount() const

    // TODO: bool isFull() const

    // TODO: void listSpells() const (optional - not tested)
};
