#pragma once
#include "item.h"

#include <iostream>
class Inventory {
   public:
    Inventory(int capacity);
    ~Inventory();
    // copy constructor
    Inventory(const Inventory& other);
    // copy assignment
    Inventory& operator=(const Inventory& other);

    int getCapacity();
    bool addItem(std::string, int val);
    int getCount();
    Item* findItem(const std::string& name);
    bool removeItem(std::string name);
    void display();

   private:
    Item* inv;
    int size;
    int capacity;

    void resize(int newCap);
    void addMessage(Item& i);
};
