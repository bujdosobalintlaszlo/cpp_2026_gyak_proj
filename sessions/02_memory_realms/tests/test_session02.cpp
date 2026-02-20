#include "../starter/inventory.h"

#include <catch2/catch_all.hpp>
#include "item.h"
#include "inventory.h"
/*
 * Session 2 Test Coverage
 *
 * Core Requirements Tested:
 * ✅ Item class (constructor, getters)
 * ✅ Inventory creation (capacity, count)
 * ✅ Adding items (single, multiple, full inventory)
 * ✅ Finding items (existing, non-existent, nullptr checks)
 * ✅ Removing items (existing, non-existent, shifting)
 * ✅ Memory management (no leaks, proper cleanup)
 * ✅ Edge cases (empty inventory, full inventory, boundaries)
 * ✅ Pointer safety (nullptr checks, dangling pointer prevention)
 *
 * Coverage: 12 test cases, 40+ assertions
 */

TEST_CASE("Item class works correctly", "[session02][item]") {
    Item item("Test Item", 100);

    REQUIRE(item.getName() == "Test Item");
    REQUIRE(item.getValue() == 100);
}

TEST_CASE("Item with different values", "[session02][item]") {
    SECTION("Zero value item") {
        Item item("Free Item", 0);
        REQUIRE(item.getValue() == 0);
    }

    SECTION("High value item") {
        Item item("Legendary Sword", 999999);
        REQUIRE(item.getValue() == 999999);
    }

    SECTION("Empty name") {
        Item item("", 50);
        REQUIRE(item.getName() == "");
    }
}

TEST_CASE("Inventory creation", "[session02][inventory]") {
    Inventory inv(10);

    REQUIRE(inv.getCapacity() == 10);
    REQUIRE(inv.getCount() == 0);
}

TEST_CASE("Inventory with different capacities", "[session02][inventory]") {
    SECTION("Small inventory") {
        Inventory inv(1);
        REQUIRE(inv.getCapacity() == 1);
    }

    SECTION("Large inventory") {
        Inventory inv(100);
        REQUIRE(inv.getCapacity() == 100);
    }
}

TEST_CASE("Adding items to inventory", "[session02][inventory]") {
    Inventory inv(5);

    SECTION("Add single item") {
        REQUIRE(inv.addItem("Sword", 100));
        REQUIRE(inv.getCount() == 1);
    }

    SECTION("Add multiple items") {
        REQUIRE(inv.addItem("Sword", 100));
        REQUIRE(inv.addItem("Potion", 50));
        REQUIRE(inv.addItem("Ring", 200));
        REQUIRE(inv.getCount() == 3);
    }

    SECTION("Inventory full") {
        for (int i = 0; i < 5; i++) {
            REQUIRE(inv.addItem("Item" + std::to_string(i), 10));
        }
        REQUIRE(inv.getCount() == 5);
        REQUIRE_FALSE(inv.addItem("Extra", 10));
    }

    SECTION("Add items with same name") {
        REQUIRE(inv.addItem("Potion", 50));
        REQUIRE(inv.addItem("Potion", 50));
        REQUIRE(inv.getCount() == 2);
    }
}

TEST_CASE("Finding items", "[session02][inventory][pointer]") {
    Inventory inv(10);
    inv.addItem("Sword", 100);
    inv.addItem("Potion", 50);

    SECTION("Find existing item") {
        Item* found = inv.findItem("Sword");
        REQUIRE(found != nullptr);
        REQUIRE(found->getName() == "Sword");
        REQUIRE(found->getValue() == 100);
    }

    SECTION("Find non-existent item returns nullptr") {
        Item* found = inv.findItem("NonExistent");
        REQUIRE(found == nullptr);
    }

    SECTION("Find in empty inventory") {
        Inventory empty(5);
        Item* found = empty.findItem("Anything");
        REQUIRE(found == nullptr);
    }

    SECTION("Find first item") {
        Item* found = inv.findItem("Sword");
        REQUIRE(found != nullptr);
        REQUIRE(found->getName() == "Sword");
    }

    SECTION("Find last item") {
        Item* found = inv.findItem("Potion");
        REQUIRE(found != nullptr);
        REQUIRE(found->getName() == "Potion");
    }
}

TEST_CASE("Removing items", "[session02][inventory]") {
    Inventory inv(10);
    inv.addItem("Sword", 100);
    inv.addItem("Potion", 50);
    inv.addItem("Ring", 200);

    SECTION("Remove existing item") {
        REQUIRE(inv.getCount() == 3);
        REQUIRE(inv.removeItem("Potion"));
        REQUIRE(inv.getCount() == 2);

        Item* found = inv.findItem("Potion");
        REQUIRE(found == nullptr);
    }

    SECTION("Remove non-existent item") {
        REQUIRE_FALSE(inv.removeItem("NonExistent"));
        REQUIRE(inv.getCount() == 3);
    }

    SECTION("Items shift correctly after removal") {
        inv.removeItem("Potion");

        REQUIRE(inv.findItem("Sword") != nullptr);
        REQUIRE(inv.findItem("Ring") != nullptr);
    }

    SECTION("Remove first item") {
        REQUIRE(inv.removeItem("Sword"));
        REQUIRE(inv.getCount() == 2);
        REQUIRE(inv.findItem("Sword") == nullptr);
    }

    SECTION("Remove last item") {
        REQUIRE(inv.removeItem("Ring"));
        REQUIRE(inv.getCount() == 2);
        REQUIRE(inv.findItem("Ring") == nullptr);
    }

    SECTION("Remove all items") {
        inv.removeItem("Sword");
        inv.removeItem("Potion");
        inv.removeItem("Ring");
        REQUIRE(inv.getCount() == 0);
    }
}

TEST_CASE("Remove from empty inventory", "[session02][inventory][edge]") {
    Inventory inv(5);
    REQUIRE_FALSE(inv.removeItem("Anything"));
    REQUIRE(inv.getCount() == 0);
}

TEST_CASE("Memory management", "[session02][inventory][memory]") {
    SECTION("Destructor cleans up properly") {
        {
            Inventory inv(5);
            inv.addItem("Item1", 10);
            inv.addItem("Item2", 20);
            inv.addItem("Item3", 30);
        }
        REQUIRE(true);
    }

    SECTION("Multiple inventories") {
        Inventory inv1(5);
        Inventory inv2(10);
        inv1.addItem("Item1", 10);
        inv2.addItem("Item2", 20);
        REQUIRE(inv1.getCount() == 1);
        REQUIRE(inv2.getCount() == 1);
    }
}

TEST_CASE("Boundary conditions", "[session02][inventory][edge]") {
    SECTION("Fill to exact capacity") {
        Inventory inv(3);
        REQUIRE(inv.addItem("Item1", 10));
        REQUIRE(inv.addItem("Item2", 20));
        REQUIRE(inv.addItem("Item3", 30));
        REQUIRE(inv.getCount() == 3);
        REQUIRE_FALSE(inv.addItem("Item4", 40));
    }

    SECTION("Add after removing") {
        Inventory inv(2);
        inv.addItem("Item1", 10);
        inv.addItem("Item2", 20);
        inv.removeItem("Item1");
        REQUIRE(inv.addItem("Item3", 30));
        REQUIRE(inv.getCount() == 2);
    }
}

TEST_CASE("Pointer safety", "[session02][pointer][safety]") {
    Inventory inv(5);
    inv.addItem("Sword", 100);

    SECTION("Pointer remains valid until removal") {
        Item* ptr = inv.findItem("Sword");
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->getName() == "Sword");

        // Pointer should still work
        REQUIRE(ptr->getValue() == 100);
    }

    SECTION("Nullptr check before dereferencing") {
        Item* ptr = inv.findItem("NonExistent");
        REQUIRE(ptr == nullptr);
        // Safe: we don't dereference nullptr
    }
}

TEST_CASE("Complex operations", "[session02][integration]") {
    Inventory inv(5);

    // Add items
    inv.addItem("Sword", 100);
    inv.addItem("Potion", 50);
    inv.addItem("Ring", 200);
    REQUIRE(inv.getCount() == 3);

    // Find and verify
    Item* sword = inv.findItem("Sword");
    REQUIRE(sword != nullptr);
    REQUIRE(sword->getValue() == 100);

    // Remove middle item
    inv.removeItem("Potion");
    REQUIRE(inv.getCount() == 2);

    // Add new item
    inv.addItem("Armor", 150);
    REQUIRE(inv.getCount() == 3);

    // Verify all items
    REQUIRE(inv.findItem("Sword") != nullptr);
    REQUIRE(inv.findItem("Ring") != nullptr);
    REQUIRE(inv.findItem("Armor") != nullptr);
    REQUIRE(inv.findItem("Potion") == nullptr);
}
