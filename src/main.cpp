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

/// Screen resolution constants.
constexpr uint32_t kSCRWIDTH  { 640 };
constexpr uint32_t kSCRHEIGHT { 360 };

/// Program entry point.
/// Creates an entity manager, renderer, physics and collision systems,
/// spawns test entities, then runs the main game loop.
int main(void)
{
    try
    {
        ECS::EntityManager_t entityMan;

        // Spawn test entities with PNG sprites
        entityMan.createEntity(20,  40, "png/ninja.png");
        entityMan.createEntity(80,  10, "png/ninja.png");
        entityMan.createEntity(200, 70, "png/ninja.png");

        // Create ECS systems
        const ECS::RenderSystem_t   render   { kSCRWIDTH, kSCRHEIGHT };
        ECS::PhysicsSystem_t        physics;
        ECS::CollisionSystem_t      collision;

        // Main game loop
        while (render.update(entityMan))
        {
            physics.update(entityMan);
            collision.update(entityMan);
        }
    }
    catch (std::exception const& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
