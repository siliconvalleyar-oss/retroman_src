#pragma once

namespace ECS {

struct GameContext_t;

/// Velocity-based movement system.
/// Updates entity physics component positions each frame.
struct PhysicsSystem_t
{
    explicit PhysicsSystem_t() = default;

    /// Apply velocity to all physics components.
    /// @param g  Game context providing mutable physics component access
    /// @return   true on success
    bool update(GameContext_t& g) const;
};

} // namespace ECS
