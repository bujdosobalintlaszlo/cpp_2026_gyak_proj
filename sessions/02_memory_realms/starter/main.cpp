#include "inventory.h"
#include<vector>
#include <iostream>
#include"item.h"
int main() {
    std::cout << "================================\n";
    std::cout << "     INVENTORY SYSTEM\n";
    std::cout << "================================\n";

    // TODO: Create an Inventory with capacity 10

	 // TODO: Add some items
	 
    // Example: inventory.addItem("Iron Sword", 100);
    // TODO: Display inventory

    // TODO: Find an item

    // TODO: Remove an item

    // TODO: Display inventory again
	 Item test("testItem",100);
	 std::cout << test.getName();
	 std::cout << test.getValue();
    std::cout << "================================\n";
    return 0;
}


