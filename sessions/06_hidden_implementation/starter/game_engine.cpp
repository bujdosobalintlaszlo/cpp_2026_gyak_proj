#include "game_engine.h"

#include <iostream>
#include <vector>

// ============================================================================
// IMPLEMENTATION FILE - Pimpl pattern
// ============================================================================

/**
 * GameEngine::Impl - Hidden implementation details
 *
 * This struct is only visible in the .cpp file, hiding implementation
 * details from users of the GameEngine class.
 *
 * Hints:
 * - Define Entity struct to hold name and health
 * - Use vectors to store players and enemies
 * - Track game state (turn count, etc.)
 * - All implementation details are private to this file
 */

// TODO: Define GameEngine::Impl struct
// struct GameEngine::Impl {
//     struct Entity { ... };
//     std::vector<Entity> players;
//     std::vector<Entity> enemies;
//     int turnCount = 0;
// };

// TODO: Implement GameEngine constructor
// GameEngine::GameEngine() : pimpl_(std::make_unique<Impl>()) {}

// TODO: Implement GameEngine destructor
// GameEngine::~GameEngine() = default;
// IMPORTANT: Must be defined here where Impl is complete!

// TODO: Implement move constructor
// GameEngine::GameEngine(GameEngine&&) noexcept = default;

// TODO: Implement move assignment
// GameEngine& GameEngine::operator=(GameEngine&&) noexcept = default;

// TODO: Implement public methods
// - addPlayer: add to pimpl_->players
// - addEnemy: add to pimpl_->enemies
// - update: increment pimpl_->turnCount
// - displayStatus: print game state
// - getPlayerCount: return pimpl_->players.size()
// - getEnemyCount: return pimpl_->enemies.size()
