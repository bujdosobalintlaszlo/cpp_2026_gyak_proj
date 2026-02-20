#pragma once
#include "item.h"
#include <iostream>
class Inventory{
	 public:
		  Inventory(int capacity);
		  ~Inventory();
		  //copy constructor
		  Inventory(const Inventory & other);
		  //copy assignment
		  Inventory& operator=(const Inventory& other);

		  int getCapacity();
		  void addItem(Item i);
		  int getCount();
		  Item* findItem(std::string name);
		  void removeItem(std::string name);
	 private:
		  Item* inv;
		  int size;
		  int capacity;

		  void resize(int newCap);
		  void addMessage(Item &i);
};
