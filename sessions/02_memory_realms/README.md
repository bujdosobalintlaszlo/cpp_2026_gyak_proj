# Session 2: Memory Realms 🧭

## Quest Narrative

*"To manipulate reality, you must first understand the fabric of memory itself. Learn to navigate the realms of stack and heap, wielding pointers and references like a true mage."*

---

## Learning Objectives

By completing this quest, you will:
- Understand the difference between pointers and references
- Navigate memory addresses safely
- Use `nullptr` correctly
- Apply const correctness with pointers
- Implement dynamic memory management
- Recognize and avoid common pointer pitfalls

---

## Core Quest (100 XP)

### Requirements

Create a **Dynamic Inventory System** that:

1. **Manages items dynamically**:
   - Store items in a dynamically allocated array
   - Add items to inventory
   - Remove items from inventory
   - Find items by name

2. **Uses proper pointer management**:
   - Dynamic allocation with `new`
   - Proper deallocation with `delete`
   - Null pointer checks
   - No memory leaks

3. **Implements proper encapsulation**:
   - `Item` class with name and value
   - `Inventory` class managing Item pointers
   - Proper constructors and destructor

### Example Output

```
================================
     INVENTORY SYSTEM
================================
Adding items...
✓ Added: Iron Sword (value: 100)
✓ Added: Health Potion (value: 50)
✓ Added: Magic Ring (value: 200)

Current inventory (3/10 items):
  1. Iron Sword - 100 gold
  2. Health Potion - 50 gold
  3. Magic Ring - 200 gold

Finding item: Health Potion
✓ Found: Health Potion (value: 50)

Removing: Health Potion
✓ Removed successfully

Current inventory (2/10 items):
  1. Iron Sword - 100 gold
  2. Magic Ring - 200 gold
================================
```

### Starter Code

See `starter/inventory.h` and `starter/main.cpp`

### Testing

```bash
cd build
cmake ..
make
./sessions/02_memory_realms/starter/inventory_demo

# Run automated tests
ctest -R session02
```

---

## Side Quests (50 XP each)

### Side Quest 1: Smart Sorting 📊
Implement inventory sorting:
- Sort by name (alphabetical)
- Sort by value (highest first)
- Use pointer arithmetic

### Side Quest 2: Item Stacking 📦
Add item stacking for identical items:
- Track quantity for each item
- Combine identical items
- Split stacks

### Side Quest 3: Memory Profiling 🔍
Add memory tracking:
- Count total allocations
- Track current memory usage
- Report memory leaks

### Side Quest 4: Const Pointer Mastery 🎯
Create examples demonstrating all four const pointer variations:
- Mutable pointer to mutable data
- Mutable pointer to const data (`const int*`)
- Const pointer to mutable data (`int* const`)
- Const pointer to const data (`const int* const`)
- Document when to use each variation

---

## Code Quality Bonus (+20 XP)

Earn bonus XP by:
- ✅ Zero compiler warnings
- ✅ Zero memory leaks (check with valgrind)
- ✅ Proper const correctness
- ✅ Null pointer checks everywhere
- ✅ Clear comments explaining pointer usage

---

## Key Concepts

### Pointers vs References

```cpp
// Pointer: stores memory address
int value = 42;
int* ptr = &value;    // ptr holds address of value
*ptr = 43;            // dereference to modify

// Reference: alias to existing variable
int& ref = value;     // ref is another name for value
ref = 44;             // modifies value directly

// Key differences:
// - Pointers can be null, references cannot
// - Pointers can be reassigned, references cannot
// - Pointers require dereferencing (*), references don't
```

### Dynamic Memory

Key operations:
- Allocate single object with `new`
- Allocate array with `new[]`
- Deallocate with `delete` or `delete[]` (must match allocation type)
- Always check for nullptr before dereferencing

**Resources:**
- [new expression](https://en.cppreference.com/w/cpp/language/new)
- [delete expression](https://en.cppreference.com/w/cpp/language/delete)

### Const Correctness

Four combinations of pointer and const:
1. Mutable pointer to mutable data
2. Mutable pointer to const data (can't modify through pointer)
3. Const pointer to mutable data (can't reassign pointer)
4. Const pointer to const data (can't modify anything)

Think about what each combination allows and prevents.

**Resources:**
- [const qualifier](https://en.cppreference.com/w/cpp/language/cv)

### Stack vs Heap Memory

**Stack Memory (automatic):**
- Fast allocation/deallocation
- Limited size
- Automatic cleanup when scope ends
- Local variables live here

**Heap Memory (dynamic):**
- Slower allocation/deallocation
- Flexible size
- Manual cleanup required (delete)
- Objects created with `new` live here

Understanding when to use each is crucial for effective C++ programming.

---

## Common Pitfalls

### ❌ Memory Leaks
```cpp
// Bad: forgot to delete
int* ptr = new int(42);
// ... use ptr ...
// Forgot: delete ptr;  // Memory leak!
```

### ❌ Dangling Pointers
```cpp
// Bad: pointer to destroyed object
int* ptr;
{
    int local = 42;
    ptr = &local;
}  // local destroyed
// *ptr;  // Undefined behavior!
```

### ❌ Double Delete
```cpp
// Bad: deleting twice
int* ptr = new int(42);
delete ptr;
delete ptr;  // Crash!
```

### ❌ Using Deleted Memory
```cpp
// Bad: use after delete
int* ptr = new int(42);
delete ptr;
*ptr = 100;  // Undefined behavior!
```

### ❌ Array Delete Mismatch
```cpp
// Bad: wrong delete for array
int* arr = new int[10];
delete arr;  // Should be delete[]!
```

**Tip:** Use valgrind or address sanitizer to detect these issues during development.

---

## Hints

### Dynamic Memory Management

Key concepts to understand:
- Allocating single objects vs arrays (different syntax)
- Matching allocation with correct deallocation (delete vs delete[])
- Always check for nullptr before dereferencing
- Memory allocated with `new` must be freed with `delete`

**Resources:**
- [Dynamic memory management](https://en.cppreference.com/w/cpp/language/new)
- [delete expression](https://en.cppreference.com/w/cpp/language/delete)

### Const Correctness

Understand the four pointer/const combinations:
- Mutable pointer to mutable data
- Mutable pointer to const data
- Const pointer to mutable data  
- Const pointer to const data

Think about: What can be modified? What can be reassigned?

**Resources:**
- [const qualifier](https://en.cppreference.com/w/cpp/language/cv)

### Managing Dynamic Arrays

For the Inventory class, consider:
- How to allocate an array of pointers
- Initialization strategy (what should pointers start as?)
- Destructor order: delete items first, then the array
- Shifting elements when removing from middle

### Finding and Removing Items

Think about:
- How to search through the array efficiently
- What to return when item not found
- How to maintain array continuity after removal
- When to update the count

**Resources:**
- [Destructors](https://en.cppreference.com/w/cpp/language/destructor)

---

## Resources

- [C++ Pointers](https://en.cppreference.com/w/cpp/language/pointer)
- [C++ References](https://en.cppreference.com/w/cpp/language/reference)
- [Dynamic Memory](https://en.cppreference.com/w/cpp/memory/new/operator_new)
- [Valgrind Tutorial](https://valgrind.org/docs/manual/quick-start.html)
- [Const Correctness](https://isocpp.org/wiki/faq/const-correctness)

---

## Homework Expectations

### In-Session Demo (What we'll build together)
- ✅ Basic pointer and reference usage
- ✅ Simple dynamic allocation (single object)
- ✅ Stack frame visualization (whiteboard)
- ✅ Pointer to const vs const pointer (two variations)

### Your Homework (What you'll implement)
- 📝 Complete inventory system with dynamic array
- 📝 All four const pointer variations (Side Quest 4)
- 📝 Memory leak detection with valgrind
- 📝 Proper null pointer checks everywhere
- 📝 Item sorting and stacking (Side Quests 1-2)
- 📝 Memory profiling (Side Quest 3)

**Expected time:** 3-4 hours for core quest + 1-2 hours per side quest

---

## Submission Checklist

Before creating your pull request:

- [ ] Code compiles without warnings
- [ ] All tests pass (`ctest -R session02`)
- [ ] **No memory leaks** (`valgrind ./inventory_demo`)
- [ ] **Code is properly formatted** (`clang-format -i starter/*.cpp starter/*.h`)
- [ ] Proper null pointer checks
- [ ] Committed to `session-02` branch
- [ ] Pushed to your repository

**Note:** GitHub Actions will check formatting, warnings, tests, AND memory leaks!

---

## Next Quest Preview

In **Session 3: The Stream of Knowledge**, you'll master input/output and argument passing as you implement a save/load system for your game. Prepare to channel the currents of data! 💾

---

**Ready to navigate the Memory Realms?** Open `starter/inventory.h` and begin!

May your pointers never dangle and your memory never leak! 🧭✨
