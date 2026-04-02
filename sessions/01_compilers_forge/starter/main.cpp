<<<<<<< HEAD
#include "display.h"

=======
>>>>>>> upstream/main
#include <iomanip>
#include <iostream>
#include <limits>  // For Side Quest 4
#include <string>
<<<<<<< HEAD
// TODO: Implement your character display system here!
=======

// ============================================================================
// Example Output (what you're building):
// ============================================================================
//
// Name:   Thorin Oakenshield
// Class:  Warrior
// Level:  12
// Health: [███████░░░] 70/100
// Mana:   [█████░░░░░] 50/100
//
// Character ID: 42
//   Decimal:     42
//   Hexadecimal: 2a
//   Octal:       52
//
// Type Information:
// Type: int
//   Size: 4 bytes
//   Min:  -2147483648
//   Max:  2147483647
//
// ============================================================================
//
// TODO: Implement your character display system!
>>>>>>> upstream/main
//
// Core Requirements (demonstrated in session):
// 1. Display character name, class, level
// 2. Display health with visual progress bar
// 3. Use proper formatting with iomanip (setw, setprecision)
// 4. Compile with zero warnings
//
// Homework Extensions (you implement):
// 5. Add MANA bar (same technique as health)
// 6. Display character ID in decimal, hex, and octal
// 7. Use std::setfill() for advanced formatting
// 8. Side Quest 4: Create type size explorer (sizeof, numeric_limits)
<<<<<<< HEAD

int main() {
    // TODO: Define character attributes
    // Hint: Use std::string for name/class, int for numbers
    std::string name = "test_char_1";
    std::string charClass = "wizard";
    int level = 1;
    int maxHealth = 100;
    int health = maxHealth;
    int maxMana = 100;
    int mana = 10;
    int characterId = 42;
    // TODO: Display formatted character sheet
    // Hint: Use std::setw() for alignment
    displayCharacter(name, charClass, level, health, maxHealth);
    // TODO: Create health progress bar (in-session demo)
    // Hint: Calculate filled = (current * barWidth) / max
    // displayBar(health,maxHealth,10);
    // TODO HOMEWORK: Create mana progress bar (same technique)
    displayBar(health, maxHealth, 10);
    displayBar(mana, maxMana, 10);
    // TODO HOMEWORK: Display character ID in different bases
    // Example:
    // int characterId = 42;
    // std::cout << "ID (dec): " << std::dec << characterId << "\n";
    // std::cout << "ID (hex): " << std::hex << characterId << "\n";
    // std::cout << "ID (oct): " << std::oct << characterId << "\n";
    displayInBases(characterId);
    // TODO HOMEWORK (Side Quest 4): Type size exploration
    // Example:
    // std::cout << "sizeof(int): " << sizeof(int) << " bytes\n";
    // std::cout << "int max: " << std::numeric_limits<int>::max() << "\n";
    // Do this for: char, short, int, long, float, double, bool
    std::cout << "sizeof (char): " << sizeof(char) << " " << "sizeof (short): " << sizeof(short)
              << " " << "sizeof (int): " << sizeof(int) << " " << "sizeof (long): " << sizeof(long)
              << " " << "sizeof (float): " << sizeof(float) << " "
              << "sizeof (double): " << sizeof(double) << " " << "sizeof (bool): " << sizeof(bool)
              << " " << '\n';
    // std::cout << "Character display not yet implemented!\n";
    // std::cout << "Open starter/main.cpp and complete the quest.\n";
=======
//
// Implementation Notes:
// - The tested functions are in display.h/display.cpp
// - This main.cpp is your playground to experiment
// - See display.h for function requirements and resources

int main() {
    // TODO: Define character attributes
    // Use std::string for name/class, int for numbers

    // TODO: Display formatted character sheet
    // Use std::setw() for alignment

    // TODO: Create health progress bar
    // Implement displayBar() in display.cpp

    // TODO HOMEWORK: Create mana progress bar

    // TODO HOMEWORK: Display character ID in different bases
    // Implement displayInBases() in display.cpp

    // TODO HOMEWORK (Side Quest 4): Type size exploration
    // Use sizeof() and std::numeric_limits
    // Explore: char, short, int, long, float, double, bool

    std::cout << "Character display not yet implemented!\n";
    std::cout << "Open starter/main.cpp and complete the quest.\n";
>>>>>>> upstream/main

    return 0;
}
