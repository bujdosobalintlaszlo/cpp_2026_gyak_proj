#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Item {
private:
    std::string name_;
    int value_;

public:
    Item(const std::string& name, int value) : name_(name), value_(value) {}
    
    const std::string& getName() const { return name_; }
    int getValue() const { return value_; }
};

class Inventory {
private:
    Item** items_;
    int capacity_;
    int count_;

public:
    Inventory(int capacity) : capacity_(capacity), count_(0) {
        items_ = new Item*[capacity_];
        for (int i = 0; i < capacity_; i++) {
            items_[i] = nullptr;
        }
    }
    
    ~Inventory() {
        for (int i = 0; i < count_; i++) {
            delete items_[i];
        }
        delete[] items_;
    }
    
    bool addItem(const std::string& name, int value) {
        if (count_ >= capacity_) {
            std::cout << "✗ Inventory full! Cannot add: " << name << "\n";
            return false;
        }
        
        items_[count_] = new Item(name, value);
        count_++;
        std::cout << "✓ Added: " << name << " (value: " << value << ")\n";
        return true;
    }
    
    bool removeItem(const std::string& name) {
        for (int i = 0; i < count_; i++) {
            if (items_[i] != nullptr && items_[i]->getName() == name) {
                delete items_[i];
                
                // Shift remaining items
                for (int j = i; j < count_ - 1; j++) {
                    items_[j] = items_[j + 1];
                }
                items_[count_ - 1] = nullptr;
                count_--;
                
                std::cout << "✓ Removed: " << name << "\n";
                return true;
            }
        }
        
        std::cout << "✗ Item not found: " << name << "\n";
        return false;
    }
    
    Item* findItem(const std::string& name) {
        for (int i = 0; i < count_; i++) {
            if (items_[i] != nullptr && items_[i]->getName() == name) {
                return items_[i];
            }
        }
        return nullptr;
    }
    
    void display() const {
        std::cout << "\nCurrent inventory (" << count_ << "/" << capacity_ << " items):\n";
        if (count_ == 0) {
            std::cout << "  (empty)\n";
            return;
        }
        
        for (int i = 0; i < count_; i++) {
            if (items_[i] != nullptr) {
                std::cout << "  " << (i + 1) << ". " 
                          << std::left << std::setw(20) << items_[i]->getName()
                          << " - " << items_[i]->getValue() << " gold\n";
            }
        }
    }
    
    int getCount() const { return count_; }
    int getCapacity() const { return capacity_; }
};
