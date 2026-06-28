extern "C" {
    #include "../lib/tinyPTC/src/tinyptc.h"
}

#include <cstdint>
#include <iostream>
#include <memory>

#include "sys/rendersystem.hpp"
#include "sys/physics.hpp"
#include "sys/collision.hpp"
#include "man/entitymanager.hpp"
#include "util/gamecontext.hpp"

/// Screen resolution constants
constexpr uint32_t kSCRWIDTH  { 640 };
constexpr uint32_t kSCRHEIGHT { 360 };

/// Program entry point.
/// Creates the entity manager, renderer, physics, and collision systems,
/// then runs the main game loop.
int main(void)
{
    try
    {
        ECS::EntityManager_t  entityMan;
        entityMan.createEntity(20, 40, 16, 16, 0x00ffffff);

        const ECS::RenderSystem_t   render { kSCRWIDTH, kSCRHEIGHT };
        ECS::PhysicsSystem_t        physics;
        ECS::CollisionSystem_t      collision;

        // Main game loop
        while (render.update(entityMan))
        {
            physics.update(entityMan);
            collision.update(entityMan);
        }
    }
    catch (...)
    {
        std::cout << "break program" << std::endl;
    }

    return 0;
}
