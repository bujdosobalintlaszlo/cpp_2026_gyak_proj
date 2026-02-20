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
        Item tempIt("item" + i, i + 1 * 100);
        inv.addItem(tempIt);
    }
    // Example: inventory.addItem("Iron Sword", 100);
    // TODO: Display inventory
    inv.displayInv();
    // TODO: Find an item
    Item* i = inv.findItem("item");
    std::cout << i->getName() << " " << i->getValue() << '\n';
    // TODO: Remove an item
    inv.removeItem("item");
    // TODO: Display inventory again
    inv.displayInv();
    std::cout << "================================\n";
    return 0;
}
