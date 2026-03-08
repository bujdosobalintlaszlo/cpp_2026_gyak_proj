# Session 4: Guardian Spirits 🛡️

## Quest Narrative

*"Summon guardian spirits that protect your resources. They appear when needed and vanish when their duty is done, ensuring nothing is ever lost or forgotten."*

---

## Learning Objectives

By completing this quest, you will:
- Understand RAII (Resource Acquisition Is Initialization) principle
- Use smart pointers (`unique_ptr`, `shared_ptr`) for automatic memory management
- Recognize when to use move semantics
- Implement the Rule of Five correctly
- Eliminate manual memory management bugs

---

## Core Quest (100 XP)

### Requirements

Create a **Resource-Managed Weapon System** that:

1. **Uses RAII for all resources**:
   - No manual `new`/`delete`
   - Automatic cleanup on scope exit
   - Exception-safe resource management

2. **Implements smart pointers**:
   - `unique_ptr` for exclusive ownership
   - `shared_ptr` for shared ownership
   - Proper ownership semantics

3. **Supports move semantics**:
   - Move-only weapon types
   - Efficient transfer of ownership
   - No unnecessary copies

### Example Output

```
================================
  GUARDIAN SPIRITS (RAII)
================================

Creating weapons with smart pointers...
✓ Created: Excalibur (Legendary Sword)
✓ Created: Fireball Staff (Magic Staff)
✓ Created: Shadow Dagger (Rare Dagger)

Weapon Manager has 3 weapons

Transferring ownership...
✓ Moved Excalibur to hero
✓ Weapon Manager now has 2 weapons

Sharing weapon...
✓ Fireball Staff shared with party (2 references)

Weapons automatically destroyed when going out of scope...
🛡️ Guardian Spirit released: Shadow Dagger
🛡️ Guardian Spirit released: Fireball Staff
🛡️ Guardian Spirit released: Excalibur

✓ No memory leaks! All resources cleaned up automatically.
================================
```

### Starter Code

See `starter/weapon.h` and `starter/main.cpp`

### Testing

```bash
cd build
cmake ..
make
./sessions/04_guardian_spirits/starter/weapon_demo

# Run tests
ctest -R session04

# Verify no memory leaks
valgrind ./sessions/04_guardian_spirits/starter/weapon_demo
```

---

## Side Quests (50 XP each)

### Side Quest 1: Custom Deleter 🔧
Implement custom deleters for special cleanup:
- Log when weapon is destroyed
- Return weapon to pool
- Custom cleanup logic

### Side Quest 2: Weak Pointers 🔗
Use `weak_ptr` to avoid circular references:
- Weapon references owner
- Owner references weapon
- Break cycles with weak_ptr

### Side Quest 3: Make Unique/Shared 🏭
Implement your own `make_unique` and `make_shared`:
- Understand how they work
- Exception safety benefits
- Performance considerations

### Side Quest 4: Lifetime Tracing 🔍
Create a logging RAII wrapper to trace object lifetimes:
- Log constructor calls with timestamp
- Log destructor calls
- Log copy/move operations
- Visualize object lifetime in complex scenarios
- Compare copy vs move performance with timing

---

## Code Quality Bonus (+20 XP)

Earn bonus XP by:
- ✅ Zero compiler warnings
- ✅ Zero memory leaks (valgrind clean)
- ✅ No manual new/delete
- ✅ Proper move semantics
- ✅ Exception-safe code

---

## Key Concepts

### RAII Principle

**Resource Acquisition Is Initialization**
- Resources (memory, files, locks) are tied to object lifetime
- Constructor acquires resource
- Destructor releases resource
- Automatic cleanup, even with exceptions
- No manual memory management needed

Benefits:
- Exception-safe by default
- No memory leaks
- Clear ownership semantics

**Resources:**
- [RAII](https://en.cppreference.com/w/cpp/language/raii)

### Smart Pointers

Three types of smart pointers:

**std::unique_ptr**: Exclusive ownership
- Only one owner at a time
- Cannot be copied, only moved
- Zero overhead compared to raw pointer
- Use for exclusive resource ownership

**std::shared_ptr**: Shared ownership
- Multiple owners allowed
- Reference counted
- Deleted when last owner is destroyed
- Small overhead for reference counting

**std::weak_ptr**: Non-owning reference
- Doesn't affect reference count
- Must lock() to access
- Use to break circular references

**Resources:**
- [unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr)
- [shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)
- [make_unique](https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique)

### Move Semantics

Move semantics enable efficient transfer of resources:
- Move constructor: Transfer resources from temporary
- Move assignment: Transfer resources, release old ones
- Use std::move() to explicitly request move
- Moved-from objects are in valid but unspecified state

Key principle: Avoid expensive copies by transferring ownership.

**Resources:**
- [Move constructors](https://en.cppreference.com/w/cpp/language/move_constructor)
- [std::move](https://en.cppreference.com/w/cpp/utility/move)
        // other is left in valid but unspecified state
    }
    
    // Move assignment
    Weapon& operator=(Weapon&& other) noexcept {
        if (this != &other) {
            effect_ = std::move(other.effect_);
            name_ = std::move(other.name_);
        }
        return *this;
    }
    
    // Delete copy operations (move-only)
    Weapon(const Weapon&) = delete;
    Weapon& operator=(const Weapon&) = delete;
};

// Usage
Weapon w1("Sword");
Weapon w2 = std::move(w1);  // Move, not copy
```

### Rule of Five

```cpp
class Resource {
public:
    // 1. Destructor
    ~Resource() { /* cleanup */ }
    
    // 2. Copy constructor
    Resource(const Resource& other) { /* deep copy */ }
    
    // 3. Copy assignment
    Resource& operator=(const Resource& other) { /* deep copy */ return *this; }
    
    // 4. Move constructor
    Resource(Resource&& other) noexcept { /* transfer ownership */ }
    
    // 5. Move assignment
    Resource& operator=(Resource&& other) noexcept { /* transfer */ return *this; }
};

// Or use Rule of Zero: let compiler generate everything
class BetterResource {
    std::unique_ptr<Data> data_;  // Handles everything!
    // Compiler generates all 5 correctly
};
```

---

## Common Pitfalls

### ❌ Using Raw Pointers
Avoid manual new/delete. Use smart pointers for automatic memory management and exception safety.

### ❌ Forgetting to Move
unique_ptr cannot be copied. Use std::move() to transfer ownership explicitly.

### ❌ Using Moved-From Object
After moving from an object, it's in a valid but unspecified state. For unique_ptr, it becomes nullptr. Don't use it without checking.

### ❌ Circular References with shared_ptr
Two shared_ptrs pointing to each other create a reference cycle, causing memory leaks. Use weak_ptr to break cycles.

---

## Hints

### Weapon Class with RAII

Think about:
- What resources does the weapon own?
- When should resources be acquired? (constructor)
- When should resources be released? (destructor)
- Why should copying be disabled?
- How to implement move operations? (use = default)

**Resources:**
- [Rule of five](https://en.cppreference.com/w/cpp/language/rule_of_three)
- [Move constructor](https://en.cppreference.com/w/cpp/language/move_constructor)

### Weapon Manager

Think about:
- How to store unique_ptr in a vector?
- How to transfer ownership when adding? (std::move)
- How to transfer ownership when removing? (std::move from vector)
- How to search the vector for a weapon by name?
- What happens to weapons when manager is destroyed?

**Resources:**
- [std::vector](https://en.cppreference.com/w/cpp/container/vector)
- [std::find_if](https://en.cppreference.com/w/cpp/algorithm/find)

### Object Lifetime Visualization

For Side Quest 4, consider creating a wrapper class that:
- Prints messages in constructor, destructor, copy, and move operations
- Helps visualize when objects are created and destroyed
- Demonstrates RAII and scope-based lifetime

This is a powerful debugging and learning tool.

### Copy vs Move Performance Comparison

```cpp
#include <chrono>
#include <vector>

// Benchmark copy vs move
void benchmarkCopyVsMove() {
    const int N = 1000000;
    std::vector<std::string> data(N, "This is a long string to copy");
    
    // Copy benchmark
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> copied = data;  // Copy
    auto end = std::chrono::high_resolution_clock::now();
    auto copy_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Move benchmark
    start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> moved = std::move(data);  // Move
    end = std::chrono::high_resolution_clock::now();
    auto move_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Copy time: " << copy_time.count() << "ms\n";
    std::cout << "Move time: " << move_time.count() << "ms\n";
    std::cout << "Speedup: " << (copy_time.count() / (double)move_time.count()) << "x\n";
}
```

---

## Resources

- [C++ Smart Pointers](https://en.cppreference.com/w/cpp/memory)
- [RAII](https://en.cppreference.com/w/cpp/language/raii)
- [Move Semantics](https://en.cppreference.com/w/cpp/language/move_constructor)
- [Rule of Five](https://en.cppreference.com/w/cpp/language/rule_of_three)
- [std::chrono for timing](https://en.cppreference.com/w/cpp/chrono)

---

## Homework Expectations

### In-Session Demo (What we'll build together)
- ✅ Basic `unique_ptr` usage
- ✅ Simple RAII wrapper class
- ✅ Move constructor basics
- ✅ Destructor with logging

### Your Homework (What you'll implement)
- 📝 Complete weapon system with smart pointers
- 📝 Full Rule of Five implementation
- 📝 Move semantics with `noexcept`
- 📝 `shared_ptr` and `weak_ptr` usage (Side Quest 2)
- 📝 Lifetime tracing wrapper (Side Quest 4)
- 📝 Copy vs move performance benchmarking
- 📝 Custom deleters (Side Quest 1)
- 📝 Implement `make_unique`/`make_shared` (Side Quest 3)

**Expected time:** 3-4 hours for core quest + 1-2 hours per side quest

---

## Submission Checklist

Before creating your pull request:

- [ ] Code compiles without warnings
- [ ] All tests pass (`ctest -R session04`)
- [ ] **No memory leaks** (`valgrind` clean)
- [ ] **No manual new/delete** (use smart pointers)
- [ ] **Code is properly formatted** (`clang-format -i`)
- [ ] Move semantics implemented correctly
- [ ] Committed to `session-04` branch
- [ ] Pushed to your repository

---

## Next Quest Preview

In **Session 5: Crafting Classes**, you'll design a complete spell system with proper encapsulation, constructors, and const correctness. Prepare to craft your first true classes! ✨

---

**Ready to summon your guardian spirits?** Open `starter/weapon.h` and begin!

May your resources always be protected and your memory never leak! 🛡️✨
