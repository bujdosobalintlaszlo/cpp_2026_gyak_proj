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

```cpp
// Allocate single object
int* ptr = new int(42);
delete ptr;  // Must delete!

// Allocate array
int* arr = new int[10];
delete[] arr;  // Use delete[] for arrays!

// Always check for null
int* ptr = new int(42);
if (ptr != nullptr) {
    *ptr = 100;
    delete ptr;
}
```

### Const Correctness

```cpp
// Pointer to const data
const int* ptr1 = &value;  // Can't modify *ptr1
// *ptr1 = 10;  // Error!
ptr1 = &other;  // OK: can reassign pointer

// Const pointer
int* const ptr2 = &value;  // Can't reassign ptr2
*ptr2 = 10;     // OK: can modify data
// ptr2 = &other;  // Error!

// Const pointer to const data
const int* const ptr3 = &value;  // Can't modify anything

// All four variations (homework: implement examples for each):
int value = 42;
int other = 100;

int* ptr;                    // 1. Mutable pointer to mutable data
const int* ptr_to_const;     // 2. Mutable pointer to const data
int* const const_ptr;        // 3. Const pointer to mutable data
const int* const const_both; // 4. Const pointer to const data
```

### Stack vs Heap Memory

```
Stack Memory (automatic):          Heap Memory (dynamic):
┌─────────────────┐               ┌─────────────────┐
│  main()         │               │                 │
│  ┌───────────┐  │               │  new int(42)    │
│  │ int x=10  │  │               │  ↑              │
│  │ int* ptr──┼──┼───────────────┼──┘              │
│  └───────────┘  │               │                 │
│                 │               │  new int[10]    │
│  func()         │               │  ↑              │
│  ┌───────────┐  │               │  │              │
│  │ int y=20  │  │               │  └──────────────│
│  │ int* arr──┼──┼───────────────┼─────────────────┘
│  └───────────┘  │               │                 │
└─────────────────┘               └─────────────────┘
   Fast, limited                    Slower, flexible
   Auto cleanup                     Manual cleanup (delete)
```

### Stack Frame Visualization

```
Function call stack grows downward:

Before func() call:          After func() call:
┌──────────────┐            ┌──────────────┐
│ main()       │            │ main()       │
│ int x = 10   │            │ int x = 10   │
│ int* ptr     │            │ int* ptr     │
└──────────────┘            ├──────────────┤
                            │ func()       │  ← New frame
                            │ int y = 20   │
                            │ int* local   │
                            └──────────────┘

After func() returns:
┌──────────────┐
│ main()       │
│ int x = 10   │  ← y and local destroyed!
│ int* ptr     │
└──────────────┘
```

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

---

## Hints

### Managing Dynamic Array

```cpp
class Inventory {
    Item** items;  // Array of Item pointers
    int capacity;
    int count;
    
public:
    Inventory(int cap) : capacity(cap), count(0) {
        items = new Item*[capacity];
        // Initialize to nullptr
        for (int i = 0; i < capacity; i++) {
            items[i] = nullptr;
        }
    }
    
    ~Inventory() {
        // Delete all items
        for (int i = 0; i < count; i++) {
            delete items[i];
        }
        // Delete array
        delete[] items;
    }
};
```

### Finding Items

```cpp
Item* findItem(const std::string& name) {
    for (int i = 0; i < count; i++) {
        if (items[i] != nullptr && items[i]->getName() == name) {
            return items[i];  // Return pointer to found item
        }
    }
    return nullptr;  // Not found
}
```

### Removing Items

```cpp
bool removeItem(const std::string& name) {
    for (int i = 0; i < count; i++) {
        if (items[i] != nullptr && items[i]->getName() == name) {
            delete items[i];  // Free memory
            // Shift remaining items
            for (int j = i; j < count - 1; j++) {
                items[j] = items[j + 1];
            }
            items[count - 1] = nullptr;
            count--;
            return true;
        }
    }
    return false;
}
```

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

## Grading Rubric

| Criterion | Points | Description |
|-----------|--------|-------------|
| Correctness | 40 | All tests pass, no crashes |
| Memory Safety | 30 | No leaks, proper delete, null checks |
| Design | 20 | Good class structure, encapsulation |
| Creativity | 10 | Side quests, extra features |

---

## Next Quest Preview

In **Session 3: The Stream of Knowledge**, you'll master input/output and argument passing as you implement a save/load system for your game. Prepare to channel the currents of data! 💾

---

**Ready to navigate the Memory Realms?** Open `starter/inventory.h` and begin!

May your pointers never dangle and your memory never leak! 🧭✨
