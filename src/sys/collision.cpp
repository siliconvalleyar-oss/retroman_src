#include <iostream>
#include "collision.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

/// For each entity with a physics component, check screen boundaries
/// (640x360) and reverse velocity on contact, correcting position.
bool CollisionSystem_t::update(GameContext_t& g) const
{
    constexpr int32_t kSCRW{900};
    constexpr int32_t kSCRH{600};

    for (auto& e : g.getEntities())
    {
        if (!e.phy) continue;

        // Right edge
        if (e.phy->x + static_cast<int32_t>(e.w) > kSCRW)
        {
            e.phy->x  = kSCRW - static_cast<int32_t>(e.w);
            e.phy->vx  = -e.phy->vx;
        }

        // Left edge
        if (e.phy->x < 0)
        {
            e.phy->x  = 0;
            e.phy->vx  = -e.phy->vx;
        }

        // Bottom edge
        if (e.phy->y + static_cast<int32_t>(e.h) > kSCRH)
        {
            e.phy->y  = kSCRH - static_cast<int32_t>(e.h);
            e.phy->vy  = -e.phy->vy;
        }

        // Top edge
        if (e.phy->y < 0)
        {
            e.phy->y  = 0;
            e.phy->vy  = -e.phy->vy;
        }
    }
    return true;
}

} // namespace ECS
