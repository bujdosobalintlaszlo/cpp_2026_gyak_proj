#include "inventory.h"

Inventory::Inventory(int capacity) : capacity(capacity),size(0) {
	 this->inv= new Item[capacity];
}

Inventory::~Inventory(){
	 delete[] inv;
}

//getters
Inventory::getCapacity(){ return this->capacity;}
Invenory::getCount(){ return this->capacity;}

void Inventory::addItem(Item i){
	 //resizing when we reach the capacity, standard *2
	 if(capacity == size){
		  resize(capacity == 0 ? 1 : capacity*2);
	 }
	 items[size++]=item;
}
