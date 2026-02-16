#include "display.h"

void displayBar(int current, int max, int barWidth) {
    // TODO: Implement progress bar
    (void)current;
    (void)max;
    //(void)barWidth;  // Remove when implementing
	 if(max == 0){
		  std::cout << "[";
		  fillWidth('░',barWidth); 
		  std::cout << "]";
	 }else if (current>=max){
		  std::cout << "[";
		  fillwith('█',barWidth); 
		  std::cout << "]";
	 }else{
		  int filled= (current*barWidth)/max;
		  std::cout << "[";
		  fillWith('█',filled);
		  fillWith('░',barWidth-filled);
		  std::cout << "]"; 
	 }
}

void fillWith(char c,int n){
	 for(int i{0};i<n;++i){
		  std::cout << c;
	 }
}

void displayCharacter(const std::string& name, const std::string& charClass, int level, int health,
                      int maxHealth) {
    // TODO: Implement character display
    (void)name;
    (void)charClass;
    (void)level;
    (void)health;
    (void)maxHealth;
	 
}

void displayInBases(int value) {
    // TODO: Implement base conversion display
    (void)value;
}
