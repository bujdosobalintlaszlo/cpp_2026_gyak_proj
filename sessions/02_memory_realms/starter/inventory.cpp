#include "inventory.h"

Inventory::Inventory(int capacity) : capacity(capacity), size(0) {
    this->inv = new Item[capacity];
}

Inventory::~Inventory() {
    delete[] inv;
}

// getters
int Inventory::getCapacity() {
    return this->capacity;
}
int Inventory::getCount() {
    return this->size;
}

// I added a param for possible size modification
// tho I hardcoded *1 as default
void Inventory::resize(int newCap) {
    Item* temp = new Item[newCap];
    for (int i = 0; i < capacity; ++i) {
        temp[i] = inv[i];
    }
    delete[] inv;
    inv = temp;
    capacity = newCap;
}
void Inventory::addMessage(Item& i) {
    std::cout << "✓ Added: " << i.getName() << "(value: " << i.getValue() << ")" << '\n';
}
void Inventory::display() {
    std::cout << "Current inventory (" << size << '/' << capacity << " items):" << '\n';
    for (int i = 0; i < size; ++i) {
        std::cout << i + 1 << ". " << inv[i].getName() << " - " << inv[i].getValue() << " gold"
                  << '\n';
    }
}

Item* Inventory::findItem(const std::string& name) {
    for (int i = 0; i < size; ++i) {
        if (inv[i].getName() == name)
            return &inv[i];
    }
    return nullptr;
}

bool Inventory::addItem(std::string name, int val) {
    Item i(name, val);
    // resizing when we reach the capacity, standard *2
    if (capacity <= size) {
        // I took this out for tests
        // resize(capacity == 0 ? 1 : capacity * 2);
        return false;
    }
    inv[size++] = i;
    addMessage(i);
    return true;
}

bool Inventory::removeItem(std::string name) {
    Item* delItem = findItem(name);
    if (delItem == nullptr)
        return false;
    int newSize = size - 1;
    Item* newItems = new Item[newSize];
    int j = 0;
    for (int i{0}; i < size; ++i) {
        if (inv[i].getName() != name) {
            newItems[j++] = inv[i];
        }
    }
    delete[] inv;
    inv = newItems;
    size = newSize;
    return true;
}
