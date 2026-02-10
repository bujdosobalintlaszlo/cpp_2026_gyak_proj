#include "spell.h"

#include <iostream>

// ============================================================================
// Example Output (what you're building):
// ============================================================================
//
// ================================
//   CRAFTING CLASSES
// ================================
// Created spell: Fireball (DAMAGE, 50 mana, 100 power)
// Created spell: Heal (HEALING, 30 mana, 50 power)
// Created spell: Shield (BUFF, 40 mana, 75 power)
//
// SpellBook (3/5 spells):
//   - Fireball (DAMAGE): 50 mana, 100 power
//   - Heal (HEALING): 30 mana, 50 power
//   - Shield (BUFF): 40 mana, 75 power
//
// Casting Fireball with 60 mana available...
// ✓ Cast successful! Power: 100
//
// Trying to cast Fireball with 40 mana available...
// ✗ Not enough mana! (need 50, have 40)
// ================================
//
// ============================================================================

int main() {
    std::cout << "================================\n";
    std::cout << "  CRAFTING CLASSES\n";
    std::cout << "================================\n";

    // TODO: Create spells
    // - Fireball (DAMAGE, cost: 50, power: 100)
    // - Heal (HEALING, cost: 30, power: 50)
    // - Shield (BUFF, cost: 40, power: 75)

    // TODO: Create SpellBook with max 5 spells

    // TODO: Add spells to spellbook

    // TODO: List all spells

    // TODO: Find and cast a spell (check canCast first)

    // TODO: Try to cast spell without enough mana

    return 0;
}
