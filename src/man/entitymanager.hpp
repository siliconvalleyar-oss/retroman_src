#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

#include "componentstorage.hpp"
#include "../util/typealiases.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

struct GameContext_t;

/// Manages the entity pool.
/// Inherits from GameContext_t to provide entity access to all systems.
struct EntityManager_t : public GameContext_t
{
    /// Number of entities to pre-allocate on construction
    static constexpr std::size_t kNUMINITIALENTITIES{1000};

    /// Constructor – reserves space for kNUMINITIALENTITIES
    explicit EntityManager_t();

    /// Create a new entity (WIP, currently a stub).
    void createEntity(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

    /// Read-only access to the entity vector.
    const Vect_t<Entity_t>& getEntities() const override { return m_Entity; }

    /// Mutable access to the entity vector.
    Vect_t<Entity_t>& getEntities() override { return m_Entity; }

    /// Read-only access to physics components (WIP).
    const std::vector<PhysicsComponent_t>& getPhysicsComponent() const override {}

    /// Mutable access to physics components (WIP).
    std::vector<PhysicsComponent_t>& getPhysicsComponent() override {}

private:
    Vect_t<Entity_t> m_Entity{};          ///< Internal entity storage
    ComponentStorage_t m_components;      ///< Component storage manager
};

} // namespace ECS
