#pragma once

#include <cstdint>
#include "../util/typealiases.hpp"

namespace ECS
{

/// Base component class providing a unique per-instance ComponentID.
/// Links each component to its parent entity via entityID.
struct Component_t
{
    /// Construct a component bound to the given entity.
    explicit Component_t(EntityID_t eid)
        : entityID{eid}
    {}

    std::size_t ComponentID{++nextID};
    EntityID_t  entityID{0};

private:
    static std::size_t nextID;
};

} // namespace ECS

 