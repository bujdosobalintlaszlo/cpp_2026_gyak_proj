#include "../starter/spell.h"

#include <catch2/catch_all.hpp>

/*
 * Session 5 Test Coverage
 *
 * Core Requirements Tested:
 * ✅ Spell creation (constructor, member initialization)
 * ✅ Getters (const correctness)
 * ✅ Spell types (enum class)
 * ✅ canCast logic (mana checking)
 * ✅ cast method (power return)
 * ✅ SpellBook creation (capacity)
 * ✅ Add spells (success, full book)
 * ✅ Find spells (existing, non-existent, const)
 * ✅ SpellBook queries (count, isFull)
 * ✅ Edge cases (empty book, exact capacity)
 *
 * Coverage: 12 test cases, 60+ assertions
 */

TEST_CASE("Spell creation", "[session05][spell]") {
    Spell spell("Fireball", 50, 100, SpellType::DAMAGE);

    REQUIRE(spell.getName() == "Fireball");
    REQUIRE(spell.getManaCost() == 50);
    REQUIRE(spell.getPower() == 100);
    REQUIRE(spell.getType() == SpellType::DAMAGE);
}

TEST_CASE("Spell types", "[session05][spell]") {
    SECTION("Damage spell") {
        Spell spell("Lightning", 30, 80, SpellType::DAMAGE);
        REQUIRE(spell.getType() == SpellType::DAMAGE);
    }

    SECTION("Healing spell") {
        Spell spell("Heal", 20, 50, SpellType::HEALING);
        REQUIRE(spell.getType() == SpellType::HEALING);
    }

    SECTION("Buff spell") {
        Spell spell("Shield", 40, 60, SpellType::BUFF);
        REQUIRE(spell.getType() == SpellType::BUFF);
    }
}

TEST_CASE("Spell canCast", "[session05][spell]") {
    Spell spell("Fireball", 50, 100, SpellType::DAMAGE);

    SECTION("Enough mana") {
        REQUIRE(spell.canCast(50));
        REQUIRE(spell.canCast(100));
    }

    SECTION("Not enough mana") {
        REQUIRE_FALSE(spell.canCast(49));
        REQUIRE_FALSE(spell.canCast(0));
    }

    SECTION("Exact mana") {
        REQUIRE(spell.canCast(50));
    }
}

TEST_CASE("Spell cast", "[session05][spell]") {
    Spell spell("Fireball", 50, 100, SpellType::DAMAGE);

    int power = spell.cast();
    REQUIRE(power == 100);
}

TEST_CASE("SpellBook creation", "[session05][spellbook]") {
    SpellBook book(10);

    REQUIRE(book.getSpellCount() == 0);
    REQUIRE_FALSE(book.isFull());
}

TEST_CASE("Add spells to SpellBook", "[session05][spellbook]") {
    SpellBook book(3);

    SECTION("Add single spell") {
        Spell spell("Fireball", 50, 100, SpellType::DAMAGE);
        REQUIRE(book.addSpell(spell));
        REQUIRE(book.getSpellCount() == 1);
    }

    SECTION("Add multiple spells") {
        REQUIRE(book.addSpell(Spell("Fireball", 50, 100, SpellType::DAMAGE)));
        REQUIRE(book.addSpell(Spell("Heal", 30, 50, SpellType::HEALING)));
        REQUIRE(book.getSpellCount() == 2);
    }

    SECTION("Fill to capacity") {
        REQUIRE(book.addSpell(Spell("Spell1", 10, 20, SpellType::DAMAGE)));
        REQUIRE(book.addSpell(Spell("Spell2", 10, 20, SpellType::DAMAGE)));
        REQUIRE(book.addSpell(Spell("Spell3", 10, 20, SpellType::DAMAGE)));
        REQUIRE(book.isFull());
        REQUIRE(book.getSpellCount() == 3);
    }

    SECTION("Cannot add when full") {
        book.addSpell(Spell("Spell1", 10, 20, SpellType::DAMAGE));
        book.addSpell(Spell("Spell2", 10, 20, SpellType::DAMAGE));
        book.addSpell(Spell("Spell3", 10, 20, SpellType::DAMAGE));

        REQUIRE_FALSE(book.addSpell(Spell("Spell4", 10, 20, SpellType::DAMAGE)));
        REQUIRE(book.getSpellCount() == 3);
    }
}

TEST_CASE("Find spells in SpellBook", "[session05][spellbook]") {
    SpellBook book(10);
    book.addSpell(Spell("Fireball", 50, 100, SpellType::DAMAGE));
    book.addSpell(Spell("Heal", 30, 50, SpellType::HEALING));

    SECTION("Find existing spell") {
        const Spell* spell = book.findSpell("Fireball");
        REQUIRE(spell != nullptr);
        REQUIRE(spell->getName() == "Fireball");
        REQUIRE(spell->getManaCost() == 50);
        REQUIRE(spell->getPower() == 100);
    }

    SECTION("Find non-existent spell") {
        const Spell* spell = book.findSpell("NonExistent");
        REQUIRE(spell == nullptr);
    }

    SECTION("Find in empty book") {
        SpellBook emptyBook(5);
        const Spell* spell = emptyBook.findSpell("Anything");
        REQUIRE(spell == nullptr);
    }
}

TEST_CASE("SpellBook isFull", "[session05][spellbook]") {
    SpellBook book(2);

    REQUIRE_FALSE(book.isFull());

    book.addSpell(Spell("Spell1", 10, 20, SpellType::DAMAGE));
    REQUIRE_FALSE(book.isFull());

    book.addSpell(Spell("Spell2", 10, 20, SpellType::DAMAGE));
    REQUIRE(book.isFull());
}

TEST_CASE("SpellBook with different capacities", "[session05][spellbook]") {
    SECTION("Small capacity") {
        SpellBook book(1);
        REQUIRE(book.addSpell(Spell("Spell1", 10, 20, SpellType::DAMAGE)));
        REQUIRE(book.isFull());
    }

    SECTION("Large capacity") {
        SpellBook book(100);
        for (int i = 0; i < 50; i++) {
            book.addSpell(Spell("Spell" + std::to_string(i), 10, 20, SpellType::DAMAGE));
        }
        REQUIRE(book.getSpellCount() == 50);
        REQUIRE_FALSE(book.isFull());
    }
}

TEST_CASE("Const correctness", "[session05][const]") {
    const Spell spell("Fireball", 50, 100, SpellType::DAMAGE);

    // These should compile because methods are const
    REQUIRE(spell.getName() == "Fireball");
    REQUIRE(spell.getManaCost() == 50);
    REQUIRE(spell.getPower() == 100);
    REQUIRE(spell.getType() == SpellType::DAMAGE);
    REQUIRE(spell.canCast(50));
}

TEST_CASE("SpellBook const methods", "[session05][const]") {
    SpellBook book(10);
    book.addSpell(Spell("Fireball", 50, 100, SpellType::DAMAGE));

    const SpellBook& constBook = book;

    // These should compile because methods are const
    REQUIRE(constBook.getSpellCount() == 1);
    REQUIRE(constBook.findSpell("Fireball") != nullptr);
    REQUIRE_FALSE(constBook.isFull());
}

TEST_CASE("Spell with edge values", "[session05][edge]") {
    SECTION("Zero mana cost") {
        Spell spell("Free Spell", 0, 10, SpellType::DAMAGE);
        REQUIRE(spell.canCast(0));
    }

    SECTION("Zero power") {
        Spell spell("Weak Spell", 10, 0, SpellType::DAMAGE);
        REQUIRE(spell.getPower() == 0);
    }

    SECTION("High values") {
        Spell spell("Ultimate", 9999, 9999, SpellType::DAMAGE);
        REQUIRE(spell.getManaCost() == 9999);
        REQUIRE(spell.getPower() == 9999);
    }
}

TEST_CASE("Integration scenario", "[session05][integration]") {
    SpellBook book(5);

    // Add various spells
    book.addSpell(Spell("Fireball", 50, 100, SpellType::DAMAGE));
    book.addSpell(Spell("Heal", 30, 50, SpellType::HEALING));
    book.addSpell(Spell("Shield", 40, 60, SpellType::BUFF));

    REQUIRE(book.getSpellCount() == 3);

    // Find and use a spell
    const Spell* fireball = book.findSpell("Fireball");
    REQUIRE(fireball != nullptr);

    int availableMana = 60;
    if (fireball->canCast(availableMana)) {
        int power = const_cast<Spell*>(fireball)->cast();
        REQUIRE(power == 100);
    }

    // Verify other spells still exist
    REQUIRE(book.findSpell("Heal") != nullptr);
    REQUIRE(book.findSpell("Shield") != nullptr);
}
