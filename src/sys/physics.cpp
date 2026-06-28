#include "physics.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

/// Update all entity positions by adding velocity each frame.
/// @param g  Game context providing mutable entity access
/// @return   true on success
bool PhysicsSystem_t::update(GameContext_t& g) const
{
    for (auto& e : g.getEntities())
    {
        // Apply velocity to position
        e.x += e.vx;
        e.y += e.vy;
    }
    return true;
}

} // namespace ECS
