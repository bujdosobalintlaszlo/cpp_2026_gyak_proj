#include "inventory.h"
#include "item.h"

#include <iostream>
int main() {
    std::cout << "================================\n";
    std::cout << "     INVENTORY SYSTEM\n";
    std::cout << "================================\n";
    // TODO: Create an Inventory with capacity 10
    Inventory inv(10);
    // TODO: Add some items
    std::cout << "Adding items..." << '\n';
    for (int i = 0; i < 4; ++i) {
        inv.addItem("test_item" + std::to_string(i), i + 1 * 100);
    }
    // Example: inventory.addItem("Iron Sword", 100);
    // TODO: Display inventory
    inv.display();
    // TODO: Find an item
    Item* i = inv.findItem("test_item1");
    if (i != nullptr) {
        std::cout << i->getName() << " " << i->getValue() << '\n';
    } else {
        std::cout << "Item not found!\n";
    }
    // TODO: Remove an item
    inv.removeItem("test_item0");
    // TODO: Display inventory again
    inv.display();
    std::cout << "================================\n";
    return 0;
}
