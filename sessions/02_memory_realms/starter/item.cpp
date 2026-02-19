#include "item.h"

Item::Item(std::string itemName,int val) : itemName(itemName),val(val){}
Item::Item(){}
std::string Item::getName(){
	 return itemName;;
}

int Item::getValue(){
	 return val;
}
