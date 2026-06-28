#pragma once

#include "../cmp/entity.hpp"

namespace ECS {

struct Entity_t;

/// Abstract base class providing a common interface for entity access.
/// All ECS systems receive a GameContext_t reference to read/write entities.
struct GameContext_t
{
    /// Virtual destructor for polymorphic use
    virtual ~GameContext_t() = default;

    /// Read-only access to the entity vector.
    virtual const Vect_t<Entity_t>& getEntities() const = 0;

    /// Mutable access to the entity vector.
    virtual Vect_t<Entity_t>& getEntities() = 0;

    /// Read-only access to physics component vector (WIP).
    virtual const std::vector<PhysicsComponent_t>& getPhysicsComponent() const = 0;

    /// Mutable access to physics component vector (WIP).
    virtual std::vector<PhysicsComponent_t>& getPhysicsComponent() = 0;
};

} // namespace ECS
