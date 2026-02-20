#include "inventory.h"
#include<vector>
#include <iostream>
#include"item.h"
int main() {
    std::cout << "================================\n";
    std::cout << "     INVENTORY SYSTEM\n";
    std::cout << "================================\n";

    // TODO: Create an Inventory with capacity 10
	 Inventory inv(10);
	 // TODO: Add some items
	 std::cout << "Adding items..."<<'\n';
	 for(int i=0;i<4;++i){
		  Item tempIt("item"+i,i+1*100);
		  inv.addItem(tempIt); 
	 } 
    // Example: inventory.addItem("Iron Sword", 100);
    // TODO: Display inventory
	 
    // TODO: Find an item

    // TODO: Remove an item

    // TODO: Display inventory again
    std::cout << "================================\n";
    return 0;
}


