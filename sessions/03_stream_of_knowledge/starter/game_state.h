#pragma once
#include <ios>
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// REQUIRED CLASS FOR TESTS
// ============================================================================

/**
 * GameState class - Manages character state with file I/O
 *
 * Requirements for tests:
 * - Store: name, class, level, gold, location (strings and ints)
 * - Store: inventory (vector of item names)
 * - saveToFile(filename) - Write state to file, return success
 * - loadFromFile(filename) - Read state from file, return success
 * - Proper const correctness on getters
 * - Pass strings by const reference
 *
 * Tests verify:
 * - Saving and loading preserves all data
 * - File operations return correct success/failure
 * - Const correctness (getters are const)
 * - Parameter passing (const reference for strings)
 *
 * Hints:
 * - Use std::ofstream for writing, std::ifstream for reading
 * - Check is_open() before file operations
 * - Think about data format (how to separate fields?)
 * - Consider validation when loading (valid ranges)
 *
 * Resources:
 * - https://en.cppreference.com/w/cpp/io/basic_fstream
 * - https://en.cppreference.com/w/cpp/io/basic_ofstream
 * - https://en.cppreference.com/w/cpp/io/basic_ifstream
 */

// TODO HOMEWORK (Side Quest): StreamGuard class
// Saves and restores stream formatting state using RAII
class StreamGuard {
    // TODO: Store stream reference, flags, precision, fill character
    // TODO: Constructor saves state
    // TODO: Destructor restores state
};

class GameState {
   private:
    // TODO: Add private members
    // Character data: name, class, level, gold, location
    // Inventory: vector of item names

   public:
    // TODO: Constructor

    // TODO: Getters (must be const methods!)

    // TODO: Setters (pass strings by const reference!)

    // TODO: bool saveToFile(const std::string& filename) const
    // Write all data to file, return true on success

    // TODO: bool loadFromFile(const std::string& filename)
    // Read all data from file, return true on success
    // Consider: input validation (level range, gold >= 0, etc.)

    // TODO HOMEWORK (Side Quest 4): C-style I/O versions
    // bool saveToFileC(const char* filename) const;
    // bool loadFromFileC(const char* filename);
    // Use FILE*, fprintf, fscanf instead of streams

    // TODO: void display() const - show current state
};

// TODO HOMEWORK (Side Quest 4): C-style I/O versions
// bool saveToFileC(const char* filename) const;
// bool loadFromFileC(const char* filename);
// Use FILE*, fprintf, fscanf instead of streams

// TODO: void display() const - show current state
}
;
