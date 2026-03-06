#include "game_state.h"

#include <iostream>

int main() {
    std::cout << "================================\n";
    std::cout << "     SAVE/LOAD SYSTEM\n";
    std::cout << "================================\n";

    // Create game state
    std::cout << "\nCreating new game state...\n";
    GameState state("Aldric the Brave", "Warrior", 5, 250, "Dark Forest");
    state.addItem("Iron Sword");
    state.addItem("Health Potion");
    state.addItem("Magic Ring");

    state.display();

    // Save to file
    std::cout << "\nSaving to file: savegame.txt\n";
    if (state.saveToFile("savegame.txt")) {
        std::cout << "✓ Game saved successfully!\n";
    } else {
        std::cout << "✗ Failed to save game\n";
        return 1;
    }

    // Load from file
    std::cout << "\nLoading from file: savegame.txt\n";
    GameState loadedState;
    if (loadedState.loadFromFile("savegame.txt")) {
        std::cout << "✓ Game loaded successfully!\n";
    } else {
        std::cout << "✗ Failed to load game\n";
        return 1;
    }

    std::cout << "\nLoaded state:";
    loadedState.display();

    // Verify data matches
    std::cout << "\nVerifying data...\n";
    bool matches =
        (state.getName() == loadedState.getName() && state.getClass() == loadedState.getClass() &&
         state.getLevel() == loadedState.getLevel() && state.getGold() == loadedState.getGold() &&
         state.getLocation() == loadedState.getLocation() &&
         state.getInventory().size() == loadedState.getInventory().size());

    if (matches) {
        std::cout << "✓ Data matches! Save/load working correctly.\n";
    } else {
        std::cout << "✗ Data mismatch!\n";
    }

    std::cout << "================================\n";

    return 0;
}
