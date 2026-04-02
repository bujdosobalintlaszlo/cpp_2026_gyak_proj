#pragma once
#include <memory>
#include <string>

// ============================================================================
// REQUIRED CLASS FOR TESTS
// ============================================================================

/**
 * GameEngine class - Uses Pimpl (Pointer to Implementation) idiom
 *
 * Requirements for tests:
 * - Constructor: GameEngine()
 * - Destructor (must be defined in .cpp file)
 * - Move-only (no copying)
 * - addPlayer(name) - adds a player
 * - addEnemy(name) - adds an enemy
 * - update() - updates game state
 * - displayStatus() - shows current state
 * - getPlayerCount() - returns number of players
 * - getEnemyCount() - returns number of enemies
 *
 * Tests verify:
 * - Adding players and enemies
 * - Counts are accurate
 * - Move operations work
 * - Copy operations are deleted
 * - Pimpl hides implementation details
 *
 * Hints:
 * - Forward declare Impl struct in header
 * - Define Impl struct in .cpp file
 * - Use unique_ptr<Impl> to store implementation
 * - Destructor must be defined in .cpp (where Impl is complete)
 * - Move operations must be defined in .cpp
 *
 * Resources:
 * - https://en.cppreference.com/w/cpp/language/pimpl
 * - https://en.cppreference.com/w/cpp/memory/unique_ptr
 */
class GameEngine {
   private:
    // TODO: Forward declare Impl struct
    // struct Impl;

    // TODO: Add unique_ptr<Impl> member
    // std::unique_ptr<Impl> pimpl_;

   public:
    // TODO: Constructor

    // TODO: Destructor (MUST be defined in .cpp!)
    // ~GameEngine();

    // TODO: Move constructor (define in .cpp)
    // GameEngine(GameEngine&&) noexcept;

    // TODO: Move assignment (define in .cpp)
    // GameEngine& operator=(GameEngine&&) noexcept;

    // TODO: Delete copy operations
    // GameEngine(const GameEngine&) = delete;
    // GameEngine& operator=(const GameEngine&) = delete;

    // TODO: Public methods
    // void addPlayer(const std::string& name);
    // void addEnemy(const std::string& name);
    // void update();
    // void displayStatus() const;
    // size_t getPlayerCount() const;
    // size_t getEnemyCount() const;
};
