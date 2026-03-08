#include "game_state.h"

#include <iostream>

// ============================================================================
// Example Output (what you're building):
// ============================================================================
//
// ================================
//      SAVE/LOAD SYSTEM
// ================================
// Character State:
//   Name: Aldric
//   Class: Warrior
//   Level: 5
//   Gold: 150
//   Location: Ironforge
//   Inventory: Iron Sword, Health Potion, Shield
//
// Saving to file... Success!
//
// Loading from file... Success!
//
// Loaded Character State:
//   Name: Aldric
//   Class: Warrior
//   Level: 5
//   Gold: 150
//   Location: Ironforge
//   Inventory: Iron Sword, Health Potion, Shield
//
// Data verification: PASSED
// ================================
//
// ============================================================================

int main() {
    std::cout << "================================\n";
    std::cout << "     SAVE/LOAD SYSTEM\n";
    std::cout << "================================\n";

    // TODO: Create a GameState object

    // TODO: Set character data (name, class, level, gold, location)

    // TODO: Add items to inventory

    // TODO: Display current state

    // TODO: Save to file (saveToFile method)

    // TODO: Create new GameState and load from file (loadFromFile method)

    // TODO: Display loaded state

    // TODO: Verify data matches original

    std::cout << "================================\n";

    return 0;
}
