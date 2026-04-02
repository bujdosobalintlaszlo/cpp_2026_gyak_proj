# Session 5: Crafting Classes

## 🎯 Quest Overview

**Narrative:** *"Every mage must craft their own tools. Learn the art of encapsulation and the secrets of proper construction."*

**Learning Objectives:**
- Design classes with proper encapsulation
- Implement constructors (default, parameterized, delegating)
- Use member initializer lists
- Write const-correct member functions
- Understand public vs private interfaces

**Estimated Time:** 2.5 hours

---

## 📖 Background Story

You've mastered memory management with guardian spirits. Now it's time to craft your own magical tools - spells! But raw power without structure is chaos. You must learn the ancient art of **encapsulation**: hiding complexity behind elegant interfaces.

A well-crafted spell has:
- **Private internals** (implementation details)
- **Public interface** (how others use it)
- **Proper construction** (valid from creation)
- **Const correctness** (read-only operations marked)

---

## 🎓 Concepts Covered

### 1. Class Design & Encapsulation

**Key Principles:**
- Data members are private (implementation details hidden)
- Public methods provide controlled access (interface)
- Class maintains its own invariants
- Users interact through well-defined interface

Benefits:
- Can change implementation without affecting users
- Prevents invalid states
- Clear separation of interface and implementation

**Resources:**
- [Classes](https://en.cppreference.com/w/cpp/language/classes)
- [Access specifiers](https://en.cppreference.com/w/cpp/language/access)

### 2. Constructors

Types of constructors:
- **Default constructor**: No parameters, provides default values
- **Parameterized constructor**: Takes parameters to initialize members
- **Delegating constructor**: Calls another constructor

Constructors initialize objects and establish invariants.

**Resources:**
- [Constructors](https://en.cppreference.com/w/cpp/language/constructor)

### 3. Member Initializer Lists

**Why use initializer lists?**
- More efficient (direct initialization vs assignment)
- Required for const members
- Required for reference members
- Required for members without default constructors

Key principle: Initialize members in the initializer list, not in constructor body.

**Resources:**
- [Member initializer lists](https://en.cppreference.com/w/cpp/language/constructor)

### 4. Const Member Functions

**Const correctness:**
- Const methods promise not to modify the object
- Can be called on const objects
- Non-const methods cannot be called on const objects

When to use const:
- Getters should be const
- Any method that doesn't modify state should be const

**Resources:**
- [const member functions](https://en.cppreference.com/w/cpp/language/member_functions#const-_and_volatile-qualified_member_functions)

---

## 🎮 Core Quest: Spell System

### Requirements

Implement a spell system with two classes:

#### 1. `Spell` Class

**Private Members:**
- `std::string name_`
- `int manaCost_`
- `int power_`
- `SpellType type_` (enum: DAMAGE, HEALING, BUFF)

**Public Interface:**
```cpp
// Constructors
Spell(const std::string& name, int cost, int power, SpellType type);

// Const methods (don't modify spell)
const std::string& getName() const;
int getManaCost() const;
int getPower() const;
SpellType getType() const;
bool canCast(int availableMana) const;

// Non-const method (modifies spell)
int cast();  // Returns power, may have side effects
```

#### 2. `SpellBook` Class

**Private Members:**
- `std::vector<Spell> spells_`
- `int maxSpells_`

**Public Interface:**
```cpp
// Constructor
SpellBook(int maxSpells);

// Methods
bool addSpell(const Spell& spell);
const Spell* findSpell(const std::string& name) const;
int getSpellCount() const;
bool isFull() const;
void listSpells() const;
```

### Success Criteria

✅ All data members are private  
✅ Constructors use initializer lists  
✅ Const methods marked correctly  
✅ No memory leaks  
✅ All tests pass  
✅ Code compiles with `-Wall -Wextra -Werror`  

---

## 🧪 Testing Your Implementation

```bash
# Build and run tests
cd cpp-quest
cmake -B build
cmake --build build
./build/sessions/05_crafting_classes/test_session05

# Run demo
./build/sessions/05_crafting_classes/spell_demo
```

**Expected Output:**
```
================================
  CRAFTING CLASSES
================================

Creating spells...
✓ Created: Fireball (Cost: 50, Power: 100)
✓ Created: Heal (Cost: 30, Power: 50)
✓ Created: Shield (Cost: 40, Power: 75)

Adding to spellbook (max 5)...
✓ Added Fireball
✓ Added Heal
✓ Added Shield

Spellbook contains 3 spells:
  - Fireball (DAMAGE): 50 mana, 100 power
  - Heal (HEALING): 30 mana, 50 power
  - Shield (BUFF): 40 mana, 75 power

Casting spells...
✓ Cast Fireball for 100 damage!
✓ Cast Heal for 50 healing!
```

---

## 🌟 Side Quests (Optional)

### Side Quest 1: Spell Cooldowns
**XP:** +50

Add cooldown system:
```cpp
class Spell {
private:
    int cooldown_;
    int currentCooldown_;
public:
    bool isReady() const;
    void reduceCooldown();
};
```

### Side Quest 2: Spell Combinations
**XP:** +50

Implement spell combos:
```cpp
class SpellBook {
public:
    int castCombo(const std::string& spell1, const std::string& spell2);
    // Returns combined power with bonus
};
```

### Side Quest 3: Spell Upgrades
**XP:** +50

Add upgrade mechanics:
```cpp
class Spell {
private:
    int level_;
public:
    void upgrade();  // Increases power, may reduce cost
    int getLevel() const;
};
```

### Side Quest 4: Memory Layout Analysis
**XP:** +50

Analyze class memory layout:
- Use `sizeof()` to measure class sizes
- Add different member types and observe size changes
- Understand padding and alignment
- Compare struct vs class memory layout
- Create a report documenting:
  - Size of Spell class with different members
  - Effect of member order on size
  - Alignment requirements
  - Comparison with C struct

```cpp
// Example analysis
struct SpellData {
    char type;        // 1 byte
    int power;        // 4 bytes
    double multiplier; // 8 bytes
};
// What is sizeof(SpellData)? Why?
```

### Side Quest 5: Static Members & Registry
**XP:** +50

Implement static member tracking:
```cpp
class Spell {
private:
    static int totalSpellsCreated_;
    static std::vector<std::string> spellRegistry_;
    
public:
    Spell(const std::string& name, int cost, int power);
    
    static int getTotalSpells();
    static const std::vector<std::string>& getRegistry();
    static Spell* findByName(const std::string& name);
};

// In .cpp file:
int Spell::totalSpellsCreated_ = 0;
std::vector<std::string> Spell::spellRegistry_;
```

### Side Quest 6: Friend Functions
**XP:** +50

Implement operator overloading with friend functions:
```cpp
class Spell {
    friend std::ostream& operator<<(std::ostream& os, const Spell& spell);
    friend bool operator==(const Spell& lhs, const Spell& rhs);
    friend bool operator<(const Spell& lhs, const Spell& rhs);
    
private:
    std::string name_;
    int power_;
};

// Friend functions have access to private members
std::ostream& operator<<(std::ostream& os, const Spell& spell) {
    os << spell.name_ << " (Power: " << spell.power_ << ")";
    return os;
}
```

---

## 💡 Key Takeaways

1. **Encapsulation** = Hide implementation, expose interface
2. **Constructors** = Ensure valid object state from creation
3. **Initializer lists** = Efficient, required for some members
4. **Const correctness** = Document and enforce read-only operations
5. **Private data** = Maintain invariants, prevent misuse
6. **Memory layout** = Understanding sizeof() and alignment
7. **Static members** = Class-level data shared by all instances
8. **Friend functions** = Controlled access to private members

---

## 🔍 Common Pitfalls

### ❌ Forgetting const on getters
```cpp
int getPower() { return power_; }  // Should be const!
```

### ❌ Assignment instead of initialization
```cpp
Spell::Spell(const std::string& name) {
    name_ = name;  // Assignment, not initialization
}
```

### ❌ Public data members
```cpp
class Spell {
public:
    int power;  // Should be private!
};
```

### ❌ Not using initializer lists
```cpp
Spell::Spell(int cost) {
    manaCost_ = cost;  // Should use initializer list
}
```

### ❌ Forgetting static member definition
```cpp
// In header:
class Spell {
    static int count_;
};

// In .cpp: MUST define!
int Spell::count_ = 0;  // Don't forget this!
```

---

## 🧠 Advanced Concepts (Homework)

### Memory Layout & Padding

```cpp
#include <iostream>

struct Unoptimized {
    char a;      // 1 byte
    int b;       // 4 bytes (but needs 4-byte alignment)
    char c;      // 1 byte
    double d;    // 8 bytes (needs 8-byte alignment)
};

struct Optimized {
    double d;    // 8 bytes
    int b;       // 4 bytes
    char a;      // 1 byte
    char c;      // 1 byte
    // 2 bytes padding
};

int main() {
    std::cout << "Unoptimized: " << sizeof(Unoptimized) << " bytes\n";  // 24
    std::cout << "Optimized: " << sizeof(Optimized) << " bytes\n";      // 16
}
```

**Key insight:** Member order affects class size due to alignment requirements!

### Static Members vs Global Variables

```cpp
// ❌ Bad: Global variable
int g_spellCount = 0;

// ✅ Good: Static member
class Spell {
    static int count_;  // Encapsulated, belongs to class
};
```

**Benefits of static members:**
- Encapsulation (private if needed)
- Clear ownership (belongs to class)
- Namespace management (Spell::count_)

### Friend Functions for Operators

```cpp
class Spell {
    friend std::ostream& operator<<(std::ostream& os, const Spell& s);
private:
    std::string name_;
    int power_;
};

// Friend can access private members
std::ostream& operator<<(std::ostream& os, const Spell& s) {
    return os << s.name_ << " (" << s.power_ << ")";
}

// Usage:
Spell fireball("Fireball", 100);
std::cout << fireball;  // Fireball (100)
```

---

## 📚 Resources

- [C++ Core Guidelines: C.2](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c2-use-class-if-the-class-has-an-invariant-use-struct-if-the-data-members-can-vary-independently)
- [C++ Core Guidelines: C.40-52](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c40-define-a-constructor-if-a-class-has-an-invariant) (Constructors)
- [Const Correctness](https://isocpp.org/wiki/faq/const-correctness)
- [Data Structure Alignment](https://en.wikipedia.org/wiki/Data_structure_alignment)
- [Static Members](https://en.cppreference.com/w/cpp/language/static)
- [Friend Declaration](https://en.cppreference.com/w/cpp/language/friend)

---

## 📝 Homework Expectations

### In-Session Demo (What we'll build together)
- ✅ Basic Spell class with private members
- ✅ Constructor with initializer list
- ✅ Const getter methods
- ✅ Simple SpellBook class

### Your Homework (What you'll implement)
- 📝 Complete Spell and SpellBook classes
- 📝 All const correctness applied
- 📝 Delegating constructors
- 📝 Memory layout analysis (Side Quest 4)
- 📝 Static member registry (Side Quest 5)
- 📝 Friend function operators (Side Quest 6)
- 📝 Cooldowns, combos, upgrades (Side Quests 1-3)

**Expected time:** 3-4 hours for core quest + 1 hour per side quest

---

## 🎯 Achievement Unlocked

Complete this quest to earn:
- **"Master Craftsman"** badge (100 XP)
- **"Const Crusader"** badge (+20 XP for perfect const correctness)
- Progress toward **Adept** rank

---

## 🔮 What's Next?

In **Session 6: Hidden Implementation**, you'll learn the Pimpl idiom to completely separate interface from implementation, reducing compilation dependencies and hiding implementation details. Prepare to master the art of information hiding! 🎭

---

**May your classes be well-encapsulated!** ✨
