# Session 6: Hidden Implementation

## 🎯 Quest Overview

**Narrative:** *"True power lies in secrets well kept. Learn to hide complexity behind elegant interfaces."*

**Learning Objectives:**
- Understand the Pimpl (Pointer to Implementation) idiom
- Reduce compilation dependencies
- Separate interface from implementation
- Use forward declarations effectively
- Apply ABI stability principles

**Estimated Time:** 2.5 hours

---

## 📖 Background Story

Your spell system works, but every time you change internal implementation details, the entire codebase recompiles. This is the curse of exposed internals! 

The ancient masters discovered the **Pimpl idiom** - a technique to hide implementation details completely. By keeping secrets behind a veil, you achieve:
- **Faster compilation** (changes don't ripple through codebase)
- **ABI stability** (binary compatibility across versions)
- **Clean interfaces** (users see only what they need)

---

## 🎓 Concepts Covered

### 1. The Problem: Exposed Implementation

**Issue:** When implementation details are in the header:
- Every file including the header must compile all dependencies
- Changing private members forces recompilation of all users
- Implementation details are visible (breaks encapsulation)
- Compilation times increase

### 2. The Solution: Pimpl Idiom

**Pimpl (Pointer to Implementation):**
- Forward declare implementation struct in header
- Store pointer to implementation (unique_ptr<Impl>)
- Define implementation struct in .cpp file
- All implementation details hidden from users

**Benefits:**
- Faster compilation (fewer dependencies in header)
- True encapsulation (implementation completely hidden)
- Can change implementation without recompiling users
- Stable ABI (binary interface)

**Key requirements:**
- Destructor must be defined in .cpp (where Impl is complete)
- Move operations must be defined in .cpp
- Use std::make_unique to create Impl

**Resources:**
- [Pimpl idiom](https://en.cppreference.com/w/cpp/language/pimpl)

### 3. Forward Declarations

Forward declarations allow you to declare a type without defining it:
- Reduces header dependencies
- Faster compilation
- Only works with pointers/references (not complete types)

**Resources:**
- [Forward declaration](https://en.cppreference.com/w/cpp/language/class)
class Stats;

// Can use pointers/references to forward-declared types
class Character {
    std::unique_ptr<Inventory> inv_;  // OK
    Stats* stats_;                     // OK
    // Stats stats_;                   // Error: incomplete type
};
```

### 4. Rule of Five with Pimpl

```cpp
class Character {
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
    
public:
    Character();
    ~Character();  // Required in .cpp
    
    // Move operations (default in .cpp)
    Character(Character&&) noexcept;
    Character& operator=(Character&&) noexcept;
    
    // Copy operations (if needed, implement in .cpp)
    Character(const Character&);
    Character& operator=(const Character&);
};
```

---

## 🎮 Core Quest: Game Engine with Pimpl

### Requirements

Implement a game engine using the Pimpl idiom:

#### 1. `GameEngine` Class (Header)

**Public Interface:**
```cpp
class GameEngine {
private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
    
public:
    GameEngine();
    ~GameEngine();
    
    // Move-only
    GameEngine(GameEngine&&) noexcept;
    GameEngine& operator=(GameEngine&&) noexcept;
    
    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;
    
    void addPlayer(const std::string& name, int health);
    void addEnemy(const std::string& name, int health);
    void update();
    void displayStatus() const;
    int getPlayerCount() const;
    int getEnemyCount() const;
};
```

#### 2. Implementation (Source File)

**Hidden Implementation:**
```cpp
struct GameEngine::Impl {
    struct Entity {
        std::string name;
        int health;
    };
    
    std::vector<Entity> players;
    std::vector<Entity> enemies;
    int turnCount;
    
    Impl() : turnCount(0) {}
};
```

### Success Criteria

✅ Header includes only `<memory>` and `<string>`  
✅ All complex types hidden in .cpp  
✅ Destructor defined in .cpp  
✅ Move operations work correctly  
✅ All tests pass  
✅ Code compiles with `-Wall -Wextra -Werror`  

---

## 🧪 Testing Your Implementation

```bash
# Build and run tests
cd cpp-quest
cmake -B build
cmake --build build
./build/sessions/06_hidden_implementation/test_session06

# Run demo
./build/sessions/06_hidden_implementation/engine_demo
```

**Expected Output:**
```
================================
  HIDDEN IMPLEMENTATION
================================

Creating game engine...
✓ Engine created

Adding entities...
✓ Added player: Hero
✓ Added player: Mage
✓ Added enemy: Goblin
✓ Added enemy: Orc

Game Status:
Players: 2
  - Hero (HP: 100)
  - Mage (HP: 80)
Enemies: 2
  - Goblin (HP: 50)
  - Orc (HP: 75)
Turn: 0

Updating game...
✓ Turn 1 complete

Game Status:
Players: 2
Enemies: 2
Turn: 1
```

---

## 🌟 Side Quests (Optional)

### Side Quest 1: Copy Support
**XP:** +50

Implement deep copy for GameEngine:
```cpp
// In .cpp
GameEngine::GameEngine(const GameEngine& other)
    : pimpl_(std::make_unique<Impl>(*other.pimpl_)) {}
```

### Side Quest 2: Plugin System
**XP:** +50

Create abstract interface with Pimpl:
```cpp
class Plugin {
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
public:
    virtual ~Plugin() = default;
    virtual void execute() = 0;
};
```

### Side Quest 3: Compilation Benchmark
**XP:** +50

Measure compilation time:
- Before Pimpl (exposed implementation)
- After Pimpl (hidden implementation)
- Document the difference

### Side Quest 4: Memory Layout & Performance Analysis
**XP:** +50

Analyze Pimpl overhead:
```cpp
// Measure and compare:
// 1. sizeof() with and without Pimpl
// 2. Memory indirection cost (benchmark access times)
// 3. Cache implications of pointer indirection
// 4. Document trade-offs: compilation speed vs runtime performance

class DirectImpl {
    std::string data;
    int value;
    // sizeof(DirectImpl) = ?
};

class PimplImpl {
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
    // sizeof(PimplImpl) = sizeof(unique_ptr) = 8 bytes (64-bit)
};

// Benchmark access patterns:
// - Direct member access
// - Pimpl member access (extra indirection)
```

### Side Quest 5: ABI Stability Demonstration
**XP:** +50

Demonstrate binary compatibility:
```cpp
// Version 1 of library (libgame.so v1.0)
class GameEngine {
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
public:
    void update();
};

// Version 2: Add new members to Impl (NOT to GameEngine)
struct GameEngine::Impl {
    // v1.0 members
    int score;
    // v2.0 NEW members (binary compatible!)
    int highScore;
    std::string playerName;
};

// Client code compiled against v1.0 still works with v2.0!
// This is ABI stability.
```

---

## 💡 Key Takeaways

1. **Pimpl** = Hide implementation details in .cpp file
2. **Forward declarations** = Reduce header dependencies
3. **Compilation speed** = Fewer dependencies = faster builds
4. **ABI stability** = Implementation changes don't break binary compatibility
5. **Rule of Five** = Destructor must be in .cpp where Impl is complete

---

## 🔍 Common Pitfalls

### ❌ Destructor in header with incomplete type
```cpp
// header.h
class MyClass {
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
public:
    ~MyClass() = default;  // Error: Impl incomplete!
};
```

### ❌ Forgetting to define destructor in .cpp
```cpp
// source.cpp
// Missing: MyClass::~MyClass() = default;
// Results in linker error
```

### ❌ Using Impl before it's defined
```cpp
// header.h
class MyClass {
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
public:
    int getValue() const { return pimpl_->value; }  // Error!
};
```

### ❌ Including heavy headers in public header
```cpp
// header.h
#include <vector>  // OK if needed in interface
#include "internal_detail.h"  // Bad! Use forward declaration
```

---

## 📚 Resources

- [C++ Core Guidelines: I.27](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#i27-for-stable-library-abi-consider-the-pimpl-idiom)
- [Herb Sutter: GotW #100](https://herbsutter.com/gotw/_100/)
- [Pimpl Idiom](https://en.cppreference.com/w/cpp/language/pimpl)
- [ABI Stability](https://community.kde.org/Policies/Binary_Compatibility_Issues_With_C%2B%2B)
- [Data Structure Alignment](https://en.wikipedia.org/wiki/Data_structure_alignment)

---

## 📝 Homework Expectations

### In-Session Demo (What we'll build together)
- ✅ Basic Pimpl structure (forward declaration)
- ✅ unique_ptr to Impl
- ✅ Destructor in .cpp file
- ✅ Simple member function forwarding

### Your Homework (What you'll implement)
- 📝 Complete GameEngine with Pimpl
- 📝 Move operations (move constructor, move assignment)
- 📝 All member functions forwarding to pimpl_
- 📝 Compilation time measurement (Side Quest 3)
- 📝 Memory layout analysis (Side Quest 4)
- 📝 ABI stability demonstration (Side Quest 5)
- 📝 Copy support (Side Quest 1)
- 📝 Plugin system (Side Quest 2)

**Expected time:** 3-4 hours for core quest + 1 hour per side quest

**Key insight:** Pimpl trades runtime performance (pointer indirection) for compilation speed and ABI stability. Measure both!

---

## 🎯 Achievement Unlocked

Complete this quest to earn:
- **"Keeper of Secrets"** badge (100 XP)
- **"Compilation Master"** badge (+20 XP for clean headers)
- Progress toward **Adept** rank

---

## 🔮 What's Next?

In **Session 7: Bloodlines**, you'll learn inheritance - how to build class hierarchies and share functionality through parent-child relationships. Prepare to inherit power from your ancestors! 🧬

---

**Keep your secrets well hidden!** 🎭
