#pragma once

#include <vector>

namespace ECS {

struct PhysicsComponent_t;

/// Manages separate component storage for ECS.
/// Provides RAII for component vectors and enforces non-copyable semantics.
struct ComponentStorage_t
{
    /// Default constructor
    explicit ComponentStorage_t() = default;

    // Non-copyable
    ComponentStorage_t(const ComponentStorage_t&) = delete;
    ComponentStorage_t(ComponentStorage_t&&) = delete;
    ComponentStorage_t operator&(const ComponentStorage_t&) = delete;
    ComponentStorage_t operator&&(ComponentStorage_t&&) = delete;

    /// Create a new physics component and return a reference to it.
    PhysicsComponent_t& createPhysicsComponent();

    /// Mutable access to the physics component vector.
    std::vector<PhysicsComponent_t>& getPhysicsComponent()
    {
        return m_physicsComponent;
    }

    /// Read-only access to the physics component vector.
    const std::vector<PhysicsComponent_t>& getPhysicsComponent() const
    {
        return m_physicsComponent;
    }

private:
    std::vector<PhysicsComponent_t> m_physicsComponent;  ///< Physics component pool
};

} // namespace ECS
