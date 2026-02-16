#include "display.h"
const std::string FULL_BLOCK = "█";
const std::string EMPTY_BLOCK = "░";

void displayBar(int current, int max, int barWidth) {
    if (max == 0) {
        std::cout << "[";
        fillWith(EMPTY_BLOCK, barWidth);
        std::cout << "]";
    } else if (current >= max) {
        std::cout << "[";
        fillWith(FULL_BLOCK, barWidth);
        std::cout << "]";
    } else {
        int filled = (current * barWidth) / max;
        std::cout << "[";
        fillWith(FULL_BLOCK, filled);
        fillWith(EMPTY_BLOCK, barWidth - filled);
        std::cout << "]";
    }
    std::cout << '\n';
}

void fillWith(std::string c, int n) {
    for (int i{0}; i < n; ++i) {
        std::cout << c;
    }
}

void displayCharacter(const std::string& name, const std::string& charClass, int level, int health,
                      int maxHealth) {
    std::cout << std::setw(10) << std::left << name << " " << std::setw(10) << std::left
              << charClass << " " << std::setw(2) << level << " " << health << "/" << maxHealth
              << " " << '\n';
    // displayBar(health, maxHealth);
}
void displayInBases(int value) {
    // TODO: Implement base conversion display
    (void)value;
    std::cout << value;
    std::cout << std::dec << value << std::hex << value << std::oct << value << std::dec << '\n';
}
