#include "inventory.h"

#include <iostream>

int main() {
    std::cout << "================================\n";
    std::cout << "     INVENTORY SYSTEM\n";
    std::cout << "================================\n";

    // Create inventory with capacity 10
    Inventory inventory(10);

    std::cout << "\nAdding items...\n";
    inventory.addItem("Iron Sword", 100);
    inventory.addItem("Health Potion", 50);
    inventory.addItem("Magic Ring", 200);
    inventory.addItem("Leather Armor", 75);

    // Display inventory
    inventory.display();

    // Find an item
    std::cout << "\nFinding item: Health Potion\n";
    Item* found = inventory.findItem("Health Potion");
    if (found != nullptr) {
        std::cout << "✓ Found: " << found->getName() << " (value: " << found->getValue() << ")\n";
    }

    // Remove an item
    std::cout << "\nRemoving: Health Potion\n";
    inventory.removeItem("Health Potion");

    // Display again
    inventory.display();

    // Try to find removed item
    std::cout << "\nFinding removed item: Health Potion\n";
    found = inventory.findItem("Health Potion");
    if (found == nullptr) {
        std::cout << "✓ Item not in inventory (correctly removed)\n";
    }

    std::cout << "\n================================\n";

    return 0;
}
