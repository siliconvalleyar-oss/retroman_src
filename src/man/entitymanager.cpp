#include <iostream>
#include <memory>
#include "entitymanager.hpp"

namespace ECS {

/// Create an entity with a solid-colour sprite.
void EntityManager_t::createEntity(uint32_t x, uint32_t y,
                                   uint32_t w, uint32_t h,
                                   uint32_t color)
{
    auto& e = m_Entity.emplace_back(w, h);
    auto& ph = m_Components.createPhysicsComponent();
    e.x = x;  e.y = y;
    ph.x = x; ph.y = y;
    e.phy = &ph;
    std::fill(e.sprite.begin(), e.sprite.end(), color);
}

/// Create an entity from a PNG sprite file with an associated physics component.
void EntityManager_t::createEntity(uint32_t x, uint32_t y,
                                   const std::string& filename)
{
    auto& e = m_Entity.emplace_back(filename);
    auto& ph = m_Components.createPhysicsComponent();
    e.x = x;  e.y = y;
    ph.x = x; ph.y = y;
    e.phy = &ph;
}

} // namespace ECS
