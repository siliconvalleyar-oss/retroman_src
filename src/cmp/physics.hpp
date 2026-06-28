#pragma once

#include <cstdint>

namespace ECS {

struct GameContext_t;

/// Component that holds physics state for an entity.
/// Stores position and velocity used by PhysicsSystem_t.
struct PhysicsComponent_t
{
    /// Default constructor
    explicit PhysicsComponent_t() = default;

    /// Process physics for all entities in the given context.
    /// @param g  Game context providing entity access
    /// @return   true on success
    bool update(GameContext_t&) const;

    uint32_t x{0}, y{0};       ///< Position in pixels
    uint32_t vx{1}, vy{1};     ///< Velocity in pixels per frame
};

} // namespace ECS
