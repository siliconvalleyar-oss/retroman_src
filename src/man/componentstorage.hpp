#pragma once
#include <vector>


namespace ECS {

struct PhysicsComponent_t;

    struct ComponentStorage_t
    {
    private:
    std::vector<PhysicsComponent_t> m_physicsComponents{};
    public:
        
        explicit ComponentStorage_t()=default;
        ComponentStorage_t(const ComponentStorage_t&) = delete;
        ComponentStorage_t(ComponentStorage_t&&) = delete;
        ComponentStorage_t operator&(const ComponentStorage_t&) = delete;
        ComponentStorage_t operator&&( ComponentStorage_t&&) = delete;
        PhysicsComponent_t& createPhysicsComponent();
       //RenderComponent_t& createRenderComponent();


        std::vector<PhysicsComponent_t>& getPhysicsComponent(){return m_physicsComponent;};
        const std::vector<PhysicsComponent_t>& getPhysicsComponent() const { return m_physicsComponent;};

    private:
        std::vector<PhysicsComponent_t> m_physicsComponent;

    };

}