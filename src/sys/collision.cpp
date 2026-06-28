#include <iostream>
#include "collision.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

/// Detect screen-edge collisions and reverse velocity on contact.
/// @param g  Game context providing mutable entity access
/// @return   true on success
bool CollisionSystem_t::update(GameContext_t& g) const
{
    for (auto& e : g.getEntities())
    {
        if (e.phy != nullptr)
        {
            // Right / left edge collision
            if (e.phy->x > 640 || e.phy->x + e.w > 640)
            {
                e.phy->x -= e.phy->vx;
                e.phy->vx = -e.phy->vx;
            }

            // Bottom / top edge collision
            if (e.phy->y > 360 || e.phy->y + e.h > 360)
            {
                e.phy->y -= e.phy->vy;
                e.phy->vy = -e.phy->vy;
            }
        }
    }
    return true;
}

} // namespace ECS
