#pragma once
#include "item.h"
class Inventory{
	 public:
		  Inventory(int capacity);
		  ~Inventory();
		  //copy constructor
		  Inventory(const Inventory & other);
		  //copy assignment
		  Inventory& operator=(const Inventory& other);
	 private:
		  Item* inv;
		  int size;
		  int capacity;
};
