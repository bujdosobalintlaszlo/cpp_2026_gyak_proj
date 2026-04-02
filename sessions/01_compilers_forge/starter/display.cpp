#include "display.h"
<<<<<<< HEAD
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
}

void fillWith(std::string c, int n) {
    for (int i{0}; i < n; ++i) {
        std::cout << c;
    }
=======

void displayBar(int current, int max, int barWidth) {
    // TODO: Implement progress bar
    (void)current;
    (void)max;
    (void)barWidth;  // Remove when implementing
>>>>>>> upstream/main
}

void displayCharacter(const std::string& name, const std::string& charClass, int level, int health,
                      int maxHealth) {
<<<<<<< HEAD
    std::cout << std::setw(10) << std::left << name << " " << std::setw(10) << std::left
              << charClass << " " << std::setw(2) << level << " " << health << "/" << maxHealth
              << " ";
    displayBar(health, maxHealth);
}
void displayInBases(int value) {
    // TODO: Implement base conversion display
    (void)value;
    std::cout << value;
    std::cout << std::dec << value << std::hex << value << std::oct << value << std::dec;
=======
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
>>>>>>> upstream/main
}
