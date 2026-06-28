#include <iostream>
#include "componentstorage.hpp"

namespace ECS {

/// Create a new physics component (WIP).
/// @return Reference to the newly created component
PhysicsComponent_t& ComponentStorage_t::createPhysicsComponent()
{
    // auto& compo = m_physicsComponents.emplace_back();
    // return compo;
    return m_physicsComponent;  // stub
}

} // namespace ECS
