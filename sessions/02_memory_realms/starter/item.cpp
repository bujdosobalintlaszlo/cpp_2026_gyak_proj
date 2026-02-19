#include "item.h"

Item::Item(std::string itemName,int val){
	 this.itemName=itemName;
	 this.val =val;
}

Item::getName(){
	 return itemName;;
}

Item::getValue(){
	 return val;
}
