#pragma once

namespace ECS {

struct GameContext_t;

/// Screen-edge collision detection and response system.
/// Reverses velocity when an entity reaches the screen boundary.
struct CollisionSystem_t
{
    explicit CollisionSystem_t() = default;

    /// Detect boundary collisions and bounce entities back.
    /// @param g  Game context providing mutable entity and physics access
    /// @return   true on success
    bool update(GameContext_t& g) const;
};

} // namespace ECS
