#include "display#include " display.h "

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
}

void fillWith(char c, int n) {
    for (int i{0}; i < n; ++i) {
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
