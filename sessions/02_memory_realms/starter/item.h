#pragma once
#include <string>
class Item {
   public:
    Item();
    Item(std::string itemName, int val);
    std::string getName();
    int getValue();

   private:
    std::string itemName;
    int val;
};
