#include "inventory.h"
Inventory::Inventory(int capacity){
	 this->capacity=capacity;
	 this->inv=new Item[capacity];
}
