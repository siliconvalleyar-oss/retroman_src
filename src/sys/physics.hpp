#pragma once

namespace ECS {

struct GameContext_t;

/// Velocity-based movement system.
/// Iterates all entities and updates their position each frame.
struct PhysicsSystem_t
{
    /// Default constructor
    explicit PhysicsSystem_t() = default;

    /// Update all entity positions.
    /// @param g  Game context providing mutable entity access
    /// @return   true on success
    bool update(GameContext_t& g) const;
};

} // namespace ECS
