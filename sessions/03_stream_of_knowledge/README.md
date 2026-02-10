# Session 3: Stream of Knowledge 💾

## Quest Narrative

*"Information flows like water through streams. Master the currents of input and output to communicate with the world beyond your program."*

---

## Learning Objectives

By completing this quest, you will:
- Understand different argument passing methods (value, reference, const reference)
- Use file streams (`ifstream`, `ofstream`) for persistent storage
- Handle stream errors and validate input
- Implement save/load functionality for game state
- Apply proper const correctness in function parameters

---

## Core Quest (100 XP)

### Requirements

Create a **Save/Load System** that:

1. **Manages game state**:
   - Character information (name, class, level)
   - Inventory items
   - Gold amount
   - Current location

2. **Implements file I/O**:
   - `saveToFile()` - Write state to file
   - `loadFromFile()` - Read state from file
   - Error handling for file operations
   - Data validation on load

3. **Uses proper parameter passing**:
   - Pass by const reference for read-only
   - Pass by reference for modification
   - Pass by value for small types

### Example Output

```
================================
     SAVE/LOAD SYSTEM
================================

Creating new game state...
Character: Aldric the Brave
Class: Warrior
Level: 5
Gold: 250
Location: Dark Forest
Inventory: Iron Sword, Health Potion, Magic Ring

Saving to file: savegame.txt
✓ Game saved successfully!

Loading from file: savegame.txt
✓ Game loaded successfully!

Loaded character: Aldric the Brave
Class: Warrior
Level: 5
Gold: 250
Location: Dark Forest
Inventory: Iron Sword, Health Potion, Magic Ring

✓ Data matches! Save/load working correctly.
================================
```

### Save File Format

```
# Character Data
Aldric the Brave
Warrior
5
250
Dark Forest
# Inventory
3
Iron Sword
Health Potion
Magic Ring
```

### Starter Code

See `starter/game_state.h` and `starter/main.cpp`

### Testing

```bash
cd build
cmake ..
make
./sessions/03_stream_of_knowledge/starter/save_load_demo

# Run automated tests
ctest -R session03
```

---

## Side Quests (50 XP each)

### Side Quest 1: Binary Save Format 📦
Implement binary save/load:
- Use `ofstream` with `ios::binary`
- Faster and more compact
- Compare file sizes

### Side Quest 2: Auto-Save 💾
Add auto-save functionality:
- Save every N actions
- Save on exit
- Backup previous save

### Side Quest 3: Save File Encryption 🔐
Add basic encryption:
- XOR cipher for save files
- Prevent easy cheating
- Decrypt on load

### Side Quest 4: C vs C++ I/O Comparison 🔬
Compare C and C++ I/O approaches:
- Implement save/load using `printf`/`scanf` (C-style)
- Implement same using streams (C++-style)
- Benchmark performance differences
- Document type safety differences
- Create comparison report

---

## Code Quality Bonus (+20 XP)

Earn bonus XP by:
- ✅ Zero compiler warnings
- ✅ Proper error handling (check file operations)
- ✅ Const correctness on all parameters
- ✅ Input validation (reject invalid data)
- ✅ Clear error messages

---

## Key Concepts

### Argument Passing

Three main approaches:
- **Pass by value**: Copies the argument. Use for small types (int, char, bool)
- **Pass by reference**: Operates on original. Use for large objects you want to modify
- **Pass by const reference**: Efficient and read-only. Use for large objects you only read (most common!)

Key principle: Avoid unnecessary copies of large objects.

**Resources:**
- [References](https://en.cppreference.com/w/cpp/language/reference)
- [const qualifier](https://en.cppreference.com/w/cpp/language/cv)

### File Streams

File I/O uses stream classes:
- **std::ofstream**: Output file stream (writing)
- **std::ifstream**: Input file stream (reading)
- **std::fstream**: Both input and output

Key operations:
- Check if file opened: `is_open()`
- Write data: `file << data`
- Read data: `file >> variable` or `std::getline(file, line)`
- Files close automatically when stream goes out of scope

**Resources:**
- [File I/O](https://en.cppreference.com/w/cpp/io/basic_fstream)
void loadData(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for reading\n";
        return;
    }
    
    std::string line;
    int number;
    double decimal;
    
    std::getline(file, line);
    file >> number;
    file >> decimal;
    
    std::cout << "Read: " << line << ", " << number << ", " << decimal << "\n";
}
```

### Stream States

Streams maintain state flags:
- **good()**: No errors
- **eof()**: End of file reached
- **fail()**: Logical error (e.g., wrong type read)
- **bad()**: Read/write error

Key operations:
- Check state before/after operations
- Use `clear()` to reset error flags
- Check `is_open()` for file streams

**Resources:**
- [Stream state](https://en.cppreference.com/w/cpp/io/ios_base/iostate)

### Stream State Guards (RAII Pattern)

RAII (Resource Acquisition Is Initialization) pattern:
- Constructor acquires resource (saves stream state)
- Destructor releases resource (restores stream state)
- Automatic cleanup, exception-safe

Useful for temporarily changing stream formatting without affecting caller's state.

**Resources:**
- [RAII](https://en.cppreference.com/w/cpp/language/raii)

### C vs C++ I/O Comparison

**C-style (stdio.h):**
- Functions: fopen, fprintf, fscanf, fclose
- Manual resource management
- Type-unsafe (format strings)
- Faster in some cases

**C++-style (fstream):**
- Classes: ofstream, ifstream, fstream
- Automatic resource management (RAII)
- Type-safe (operator overloading)
- Better integration with C++ types

**Resources:**
- [C file I/O](https://en.cppreference.com/w/c/io)

void saveCpp(const std::string& filename, int level, double health) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }
    file << level << "\n" << health << "\n";
    // Automatically closed by destructor (RAII)
}

// Key differences:
// C-style:  Fast, manual resource management, no type safety
// C++-style: Type-safe, RAII, easier to use, slightly slower
```

---

## Common Pitfalls

### ❌ Not Checking File Operations
Always check if file opened successfully before reading/writing. File operations can fail for many reasons (permissions, disk full, file doesn't exist).

### ❌ Passing Large Objects by Value
Passing strings, vectors, or custom objects by value creates expensive copies. Use const reference for read-only access.

### ❌ Modifying Const Reference
Const references cannot be modified. If you need to modify a parameter, use non-const reference.

### ❌ Not Validating Input
Always validate data read from files. Files can be corrupted, manually edited, or contain unexpected values. Check types, ranges, and formats.

---

## Hints

## Hints

### Saving Game State

Think about:
- Opening file for writing (std::ofstream)
- Checking if file opened successfully
- Writing data in a structured format
- How to separate different fields
- Returning success/failure status

**Resources:**
- [ofstream reference](https://en.cppreference.com/w/cpp/io/basic_ofstream)

### Loading Game State

Think about:
- Opening file for reading (std::ifstream)
- Checking if file opened successfully
- Reading data in the same order it was written
- Validating data as you read (ranges, types)
- Handling read failures gracefully
- Clearing/resetting state before loading

**Resources:**
- [ifstream reference](https://en.cppreference.com/w/cpp/io/basic_ifstream)
- [getline reference](https://en.cppreference.com/w/cpp/string/basic_string/getline)

### Parameter Passing

Consider when to use:
- Pass by value: Small types (int, char, bool)
- Pass by const reference: Large read-only objects (strings, vectors)
- Pass by reference: Objects you need to modify

**Resources:**
- [References](https://en.cppreference.com/w/cpp/language/reference)

---

## Resources

- [C++ File I/O](https://en.cppreference.com/w/cpp/io/basic_fstream)
- [Stream States](https://en.cppreference.com/w/cpp/io/ios_base/iostate)
- [Parameter Passing](https://isocpp.org/wiki/faq/references)
- [C stdio reference](https://en.cppreference.com/w/c/io)
- [Stream manipulators](https://en.cppreference.com/w/cpp/io/manip)

---

## Homework Expectations

### In-Session Demo (What we'll build together)
- ✅ Basic file writing with `ofstream`
- ✅ Basic file reading with `ifstream`
- ✅ Simple error checking (`is_open()`)
- ✅ Pass by value vs pass by reference (simple example)

### Your Homework (What you'll implement)
- 📝 Complete save/load system for game state
- 📝 Comprehensive input validation
- 📝 Pass by const reference for all large objects
- 📝 StreamGuard class for state management (mentioned in session)
- 📝 C vs C++ I/O comparison (Side Quest 4)
- 📝 Binary format, auto-save, encryption (Side Quests 1-3)

**Expected time:** 3-4 hours for core quest + 1-2 hours per side quest

---

## Submission Checklist

Before creating your pull request:

- [ ] Code compiles without warnings
- [ ] All tests pass (`ctest -R session03`)
- [ ] **File operations checked** (all `is_open()` calls)
- [ ] **Input validated** (reject invalid data)
- [ ] **Code is properly formatted** (`clang-format -i starter/*.cpp starter/*.h`)
- [ ] Const correctness applied
- [ ] Committed to `session-03` branch
- [ ] Pushed to your repository

**Note:** GitHub Actions will check formatting, warnings, tests, and error handling!

---

## Next Quest Preview

In **Session 4: Guardian Spirits**, you'll learn RAII and smart pointers as you implement automatic resource management for weapons and effects. Prepare to summon guardians that protect your resources! 🛡️

---

**Ready to master the streams?** Open `starter/game_state.h` and begin!

May your files always open and your data always validate! 💾✨
