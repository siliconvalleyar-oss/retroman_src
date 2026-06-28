/// @file physics.cpp
/// @brief Translation unit for PhysicsSystem_t.

#include "physics.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

/// Add velocity to the position of every physics component.
bool PhysicsSystem_t::update(GameContext_t& g) const
{
    for (auto& phy : g.getPhysicsComponent())
    {
        phy.x += phy.vx;
        phy.y += phy.vy;
    }
    return true;
}

} // namespace ECS
