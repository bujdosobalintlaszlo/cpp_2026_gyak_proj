#include "display.h"

void displayBar(int current, int max, int barWidth) {
    if (max == 0) {
        std::cout << "[";
        fillWith('░', barWidth);
        std::cout << "]";
    } else if (current >= max) {
        std::cout << "[";
        fillWith('█', barWidth);  // Fixed the lowercase 'w' here
        std::cout << "]";
    } else {
        int filled = (current * barWidth) / max;
        std::cout << "[";
        fillWith('█', filled);
        fillWith('░', barWidth - filled);
        std::cout << "]";
    }
	 std::cout << '\n';
}

void fillWith(char c, int n) {
    for (int i{0}; i < n; ++i) {
        std::cout << c;
    }
}

void displayCharacter(const std::string& name, const std::string& charClass, int level, int health,
                      int maxHealth) {
    std::cout << std::setw(10) << std::left << name 
              << " " << std::setw(10) << std::left << charClass 
              << " " << std::setw(2) << level 
              << " " << health << "/" << maxHealth << " ";
    displayBar(health, maxHealth);
    std::cout << '\n';
}
void displayInBases(int value) {
    // TODO: Implement base conversion display
    (void)value;
	 std::cout << value;
    std::cout 
		  << std::dec value 
		  << std::hex << value
		  << std::oct << value
		  << std::dec << '\n';
}
