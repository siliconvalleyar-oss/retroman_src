#pragma once

#include <vector>
#include "../cmp/entity.hpp"
#include "typealiases.hpp"

namespace ECS {

struct Entity_t;

/// Abstract base class providing a unified entity and component access interface.
/// All ECS systems receive a GameContext_t reference to read/write game data.
struct GameContext_t
{
    virtual ~GameContext_t() = default;

    /// Read-only entity vector access.
    virtual const Vect_t<Entity_t>& getEntities() const = 0;

    /// Mutable entity vector access.
    virtual Vect_t<Entity_t>& getEntities() = 0;

    /// Read-only physics component access.
    virtual const std::vector<PhysicsComponent_t>& getPhysicsComponent() const = 0;

    /// Mutable physics component access.
    virtual std::vector<PhysicsComponent_t>& getPhysicsComponent() = 0;
};

} // namespace ECS
