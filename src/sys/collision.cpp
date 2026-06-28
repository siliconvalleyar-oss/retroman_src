#include <iostream>
#include "collision.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

/// For each entity with a physics component, check screen boundaries
/// (640x360) and reverse velocity on contact, correcting position.
bool CollisionSystem_t::update(GameContext_t& g) const
{
    for (auto& e : g.getEntities())
    {
        if (!e.phy) continue;

        // Right / left edge
        if (e.phy->x > 640 || e.phy->x + e.w > 640)
        {
            e.phy->x -= e.phy->vx;
            e.phy->vx  = -e.phy->vx;
        }

        // Bottom / top edge
        if (e.phy->y > 360 || e.phy->y + e.h > 360)
        {
            e.phy->y -= e.phy->vy;
            e.phy->vy  = -e.phy->vy;
        }
    }
    return true;
}

} // namespace ECS
