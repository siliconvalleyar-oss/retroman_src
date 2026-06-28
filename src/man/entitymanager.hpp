#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "componentstorage.hpp"
#include "../util/typealiases.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

/// Manages the entity pool and component storage.
/// Inherits from GameContext_t to provide unified access to all systems.
struct EntityManager_t : public GameContext_t
{
    /// Number of entities to pre-allocate on construction.
    static constexpr std::size_t kNUMINITIALENTITIES{1000};

    /// Constructor – reserves space for the entity pool.
    explicit EntityManager_t()
    {
        m_Entity.reserve(kNUMINITIALENTITIES);
        m_Components.getPhysicsComponent().reserve(kNUMINITIALENTITIES);
    }

    /// Create an entity with dimensions and a fill colour (legacy).
    void createEntity(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);

    /// Create an entity from a PNG file, with an associated physics component.
    void createEntity(uint32_t x, uint32_t y, const std::string& filename);

    // -- GameContext_t interface --

    const Vect_t<Entity_t>& getEntities() const override { return m_Entity; }
          Vect_t<Entity_t>& getEntities()       override { return m_Entity; }

    const std::vector<PhysicsComponent_t>& getPhysicsComponent() const override
    {
        return m_Components.getPhysicsComponent();
    }
    std::vector<PhysicsComponent_t>& getPhysicsComponent() override
    {
        return m_Components.getPhysicsComponent();
    }

private:
    Vect_t<Entity_t>       m_Entity{};      ///< Entity storage
    ComponentStorage_t     m_Components{};  ///< Component storage
};

} // namespace ECS
