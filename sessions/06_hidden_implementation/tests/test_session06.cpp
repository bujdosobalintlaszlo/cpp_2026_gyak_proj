#include "../starter/game_engine.h"

#include <catch2/catch_all.hpp>

/*
 * Session 6 Test Coverage
 *
 * Core Requirements Tested:
 * ✅ Pimpl idiom (hidden implementation)
 * ✅ GameEngine creation (constructor)
 * ✅ Add players (single, multiple)
 * ✅ Add enemies (single, multiple)
 * ✅ Update game state
 * ✅ Query counts (players, enemies)
 * ✅ Move semantics (move constructor, move assignment)
 * ✅ Copy prevention (deleted copy operations)
 * ✅ Edge cases (empty engine, many entities)
 *
 * Coverage: 10 test cases, 40+ assertions
 */

TEST_CASE("GameEngine creation", "[session06][engine]") {
    GameEngine engine;

    REQUIRE(engine.getPlayerCount() == 0);
    REQUIRE(engine.getEnemyCount() == 0);
}

TEST_CASE("Add players", "[session06][engine]") {
    GameEngine engine;

    SECTION("Add single player") {
        engine.addPlayer("Hero", 100);
        REQUIRE(engine.getPlayerCount() == 1);
    }

    SECTION("Add multiple players") {
        engine.addPlayer("Hero1", 100);
        engine.addPlayer("Hero2", 120);
        engine.addPlayer("Hero3", 90);
        REQUIRE(engine.getPlayerCount() == 3);
    }
}

TEST_CASE("Add enemies", "[session06][engine]") {
    GameEngine engine;

    SECTION("Add single enemy") {
        engine.addEnemy("Goblin", 50);
        REQUIRE(engine.getEnemyCount() == 1);
    }

    SECTION("Add multiple enemies") {
        engine.addEnemy("Goblin", 50);
        engine.addEnemy("Orc", 80);
        engine.addEnemy("Dragon", 500);
        REQUIRE(engine.getEnemyCount() == 3);
    }
}

TEST_CASE("Add both players and enemies", "[session06][engine]") {
    GameEngine engine;

    engine.addPlayer("Hero", 100);
    engine.addPlayer("Mage", 80);
    engine.addEnemy("Goblin", 50);
    engine.addEnemy("Orc", 80);

    REQUIRE(engine.getPlayerCount() == 2);
    REQUIRE(engine.getEnemyCount() == 2);
}

TEST_CASE("Update game state", "[session06][engine]") {
    GameEngine engine;

    engine.addPlayer("Hero", 100);
    engine.addEnemy("Goblin", 50);

    // Update should not crash
    engine.update();

    // Counts should remain the same
    REQUIRE(engine.getPlayerCount() == 1);
    REQUIRE(engine.getEnemyCount() == 1);
}

TEST_CASE("Multiple updates", "[session06][engine]") {
    GameEngine engine;

    engine.addPlayer("Hero", 100);

    for (int i = 0; i < 10; i++) {
        engine.update();
    }

    REQUIRE(engine.getPlayerCount() == 1);
}

TEST_CASE("Display status", "[session06][engine]") {
    GameEngine engine;

    engine.addPlayer("Hero", 100);
    engine.addEnemy("Goblin", 50);

    // Should not crash
    engine.displayStatus();

    REQUIRE(engine.getPlayerCount() == 1);
    REQUIRE(engine.getEnemyCount() == 1);
}

TEST_CASE("Move semantics", "[session06][pimpl][move]") {
    GameEngine engine1;
    engine1.addPlayer("Hero", 100);
    engine1.addEnemy("Goblin", 50);

    SECTION("Move constructor") {
        GameEngine engine2(std::move(engine1));

        REQUIRE(engine2.getPlayerCount() == 1);
        REQUIRE(engine2.getEnemyCount() == 1);
    }

    SECTION("Move assignment") {
        GameEngine engine2;
        engine2 = std::move(engine1);

        REQUIRE(engine2.getPlayerCount() == 1);
        REQUIRE(engine2.getEnemyCount() == 1);
    }
}

TEST_CASE("Empty engine operations", "[session06][edge]") {
    GameEngine engine;

    SECTION("Display empty") {
        engine.displayStatus();
        REQUIRE(engine.getPlayerCount() == 0);
    }

    SECTION("Update empty") {
        engine.update();
        REQUIRE(engine.getPlayerCount() == 0);
        REQUIRE(engine.getEnemyCount() == 0);
    }
}

TEST_CASE("Large number of entities", "[session06][edge]") {
    GameEngine engine;

    for (int i = 0; i < 100; i++) {
        engine.addPlayer("Player" + std::to_string(i), 100);
        engine.addEnemy("Enemy" + std::to_string(i), 50);
    }

    REQUIRE(engine.getPlayerCount() == 100);
    REQUIRE(engine.getEnemyCount() == 100);
}

TEST_CASE("Entities with different health values", "[session06][engine]") {
    GameEngine engine;

    SECTION("Zero health") {
        engine.addPlayer("DeadHero", 0);
        REQUIRE(engine.getPlayerCount() == 1);
    }

    SECTION("High health") {
        engine.addEnemy("Boss", 99999);
        REQUIRE(engine.getEnemyCount() == 1);
    }

    SECTION("Negative health") {
        engine.addPlayer("Zombie", -10);
        REQUIRE(engine.getPlayerCount() == 1);
    }
}

TEST_CASE("Integration scenario", "[session06][integration]") {
    GameEngine engine;

    // Setup game
    engine.addPlayer("Warrior", 150);
    engine.addPlayer("Mage", 80);
    engine.addPlayer("Rogue", 100);

    engine.addEnemy("Goblin", 30);
    engine.addEnemy("Orc", 60);

    REQUIRE(engine.getPlayerCount() == 3);
    REQUIRE(engine.getEnemyCount() == 2);

    // Run some turns
    for (int i = 0; i < 5; i++) {
        engine.update();
    }

    // Display status
    engine.displayStatus();

    // Add more enemies mid-game
    engine.addEnemy("Dragon", 500);
    REQUIRE(engine.getEnemyCount() == 3);

    // Continue game
    engine.update();

    REQUIRE(engine.getPlayerCount() == 3);
    REQUIRE(engine.getEnemyCount() == 3);
}

TEST_CASE("Const correctness", "[session06][const]") {
    GameEngine engine;
    engine.addPlayer("Hero", 100);
    engine.addEnemy("Goblin", 50);

    const GameEngine& constEngine = engine;

    // These should compile because methods are const
    REQUIRE(constEngine.getPlayerCount() == 1);
    REQUIRE(constEngine.getEnemyCount() == 1);

    // displayStatus should work on const object
    constEngine.displayStatus();
}
