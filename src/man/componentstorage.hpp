#pragma once

#include <vector>
#include "../cmp/physics.hpp"

namespace ECS {

/// Manages separate component storage for the ECS.
/// Provides RAII for physics component vectors with non-copyable semantics.
struct ComponentStorage_t
{
    explicit ComponentStorage_t() = default;

    /// Construct with pre-allocated capacity.
    explicit ComponentStorage_t(std::size_t initialSize)
    {
        m_physicsComponents.reserve(initialSize);
    }

    // Non-copyable
    ComponentStorage_t(const ComponentStorage_t&) = delete;
    ComponentStorage_t(ComponentStorage_t&&) = delete;
    ComponentStorage_t& operator=(const ComponentStorage_t&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t&&) = delete;

    /// Create a new physics component and return a reference to it.
    PhysicsComponent_t& createPhysicsComponent()
    {
        return m_physicsComponents.emplace_back();
    }

    /// Access the physics component vector (mutable).
    std::vector<PhysicsComponent_t>& getPhysicsComponent()
    {
        return m_physicsComponents;
    }

    /// Access the physics component vector (read-only).
    const std::vector<PhysicsComponent_t>& getPhysicsComponent() const
    {
        return m_physicsComponents;
    }

private:
    std::vector<PhysicsComponent_t> m_physicsComponents{};
};

} // namespace ECS
