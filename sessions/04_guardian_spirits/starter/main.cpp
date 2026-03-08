#include "weapon.h"

#include <iostream>

// ============================================================================
// Example Output (what you're building):
// ============================================================================
//
// ================================
//   GUARDIAN SPIRITS (RAII)
// ================================
// Created: Iron Sword (50 damage)
// Created: Magic Staff (80 damage)
// Created: Steel Axe (65 damage)
//
// Weapons in armory: 3
//   - Iron Sword (50 damage)
//   - Magic Staff (80 damage)
//   - Steel Axe (65 damage)
//
// Removing Iron Sword...
// Iron Sword attacks for 50 damage!
// Destroying weapon: Iron Sword
//
// Weapons remaining: 2
//   - Magic Staff (80 damage)
//   - Steel Axe (65 damage)
//
// Destroying weapon: Magic Staff
// Destroying weapon: Steel Axe
//
// ✓ No memory leaks! All resources cleaned up automatically.
// ================================
//
// ============================================================================

int main() {
    std::cout << "================================\n";
    std::cout << "  GUARDIAN SPIRITS (RAII)\n";
    std::cout << "================================\n";

    // TODO: Create WeaponManager

    // TODO: Create weapons using std::make_unique

    // TODO: Add weapons to manager (use std::move)

    // TODO: Display weapons

    // TODO: Remove a weapon (transfers ownership back)

    // TODO: Use the removed weapon, then let it go out of scope

    // TODO: Show remaining weapons

    std::cout << "\n✓ No memory leaks! All resources cleaned up automatically.\n";
    std::cout << "================================\n";

    return 0;
}
