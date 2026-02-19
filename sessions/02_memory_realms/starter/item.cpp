#include "item.h"

Item::Item(std::string itemName,int val){
	 this->itemName=itemName;
	 this->val =val;
}

std::string Item::getName(){
	 return itemName;;
}

int Item::getValue(){
	 return val;
}
