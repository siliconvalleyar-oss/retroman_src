#include <iostream>
#include "entitymanager.hpp"
#include "../cmp/entity.hpp"

namespace ECS {

/// Constructor – pre-allocates entity storage.
EntityManager_t::EntityManager_t()
{
    m_Entity.reserve(kNUMINITIALENTITIES);
}

/// Create a new entity (WIP).
/// Currently a stub; future work will wire up physics components.
void EntityManager_t::createEntity(uint32_t x, uint32_t y,
                                   uint32_t i, uint32_t j,
                                   uint32_t color)
{
    // auto& e = m_Entity.emplace_back(filename);
    // auto& ph = m_components.createPhysicsComponent();
    // e.phy = &ph;
    // ph.x = x; ph.y = y;
}

} // namespace ECS
