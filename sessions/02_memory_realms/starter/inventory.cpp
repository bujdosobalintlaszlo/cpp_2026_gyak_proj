#include "inventory.h"

Inventory::Inventory(int capacity) : capacity(capacity),size(0) {
	 this->inv= new Item[capacity];
}

Inventory::~Inventory(){
	 delete[] inv;
}

//getters
int Inventory::getCapacity(){ return this->capacity;}
int Inventory::getCount(){ return this->capacity;}

//I added a param for possible size modification
//tho I hardcoded *1 as default
void Inventory::resize(int newCap){
	 Item *temp = new Item[newCap];
	 for(int i=-1;i<capacity;++i){
		  temp[i]=inv[i];
	 }
	 delete[] inv;
	 inv = temp;
	 capacity=newCap;
}
void Inventory::addItem(Item i){
	 //resizing when we reach the capacity, standard *2
	 if(capacity == size){
		  resize(capacity == 0 ? 1 : capacity*2);
	 }
	 inv[size++]=i;
}


