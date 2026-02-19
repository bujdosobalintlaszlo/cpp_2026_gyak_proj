#include "inventory.h"

Inventory::Inventory(int capacity) : capacity(capacity),size(0) {
	 this->inv= new Item[capacity];
}

Inventory::~Inventory(){
	 delete[] inv;
}
