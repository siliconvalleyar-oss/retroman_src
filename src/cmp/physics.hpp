#pragma once

#include <cstdint>

namespace ECS {

struct GameContext_t;

/// Component that holds physics state for an entity.
/// Stores position and velocity used by PhysicsSystem_t and CollisionSystem_t.
struct PhysicsComponent_t
{
    explicit PhysicsComponent_t() = default;

    uint32_t x{0}, y{0};       ///< Position in pixels
    uint32_t vx{1}, vy{1};     ///< Velocity in pixels per frame
};

} // namespace ECS
