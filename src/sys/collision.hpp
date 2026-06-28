#pragma once

namespace ECS {

struct GameContext_t;

/// Screen-edge collision detection and response system.
/// Detects when entities exceed screen boundaries and reverses velocity.
class CollisionSystem_t
{
public:
    /// Default constructor
    explicit CollisionSystem_t() = default;

    /// Detect and resolve screen-edge collisions.
    /// @param g  Game context providing mutable entity access
    /// @return   true on success
    bool update(GameContext_t& g) const;
};

} // namespace ECS
