#pragma once
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

// ============================================================================
// REQUIRED FUNCTIONS FOR TESTS
// ============================================================================
// Implement these functions to pass the automated tests.

/**
 * Display a progress bar showing current/max ratio
 * 
 * Requirements for tests:
 * - Format: [filled_chars][empty_chars] with NO newline
 * - Use block characters: filled '█' (U+2588), empty '░' (U+2591)
 * - Handle edge cases: max==0, current > max
 * 
 * Hint: Calculate what proportion of the bar should be filled
 * Resources: https://en.cppreference.com/w/cpp/io/cout
 */
void displayBar(int current, int max, int barWidth = 10);

/**
 * Display character information with formatted output
 * 
 * Requirements for tests:
 * - Must include: name, class, level, and health values
 * - Must call displayBar() to show health visually
 * - Use proper alignment for readable output
 * - Tests check for presence of all values and progress bar characters
 *
 * Hint: See main.cpp for example output format
 * Resources: https://en.cppreference.com/w/cpp/io/manip/setw
 */
void displayCharacter(const std::string& name, const std::string& charClass, int level, int health,
                      int maxHealth);

/**
 * Display a number in different bases
 * 
 * Requirements for tests:
 * - Must output the value in decimal, hexadecimal, and octal
 * - Tests check for presence of all three representations
 * - Hex can be uppercase or lowercase
 * 
 * Hint: Stream manipulators can change number base output
 * Remember to reset the stream state after changing it
 * Resources: https://en.cppreference.com/w/cpp/io/manip/hex
 */
void displayInBases(int value);

/**
 * Display size and limits of a type
 * NOTE: This template is already implemented for you!
 * Just read and understand how it works - you'll write
 * your own templates in Session 10.
 *
 * Shows: type name, size in bytes, min value, max value
 */
template <typename T>
void displayTypeInfo(const std::string& typeName) {
    std::cout << "Type: " << typeName << "\n";
    std::cout << "  Size: " << sizeof(T) << " bytes\n";
    std::cout << "  Min:  " << std::numeric_limits<T>::min() << "\n";
    std::cout << "  Max:  " << std::numeric_limits<T>::max() << "\n";
}
