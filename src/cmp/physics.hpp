#pragma once
#include <cstdint>

namespace ECS{

struct GameContext_t;

    struct  PhysicsComponent_t
    {
    private:

    public:
        explicit PhysicsComponent_t() = default;
        //~ PhysicsComponent_t();
            bool update (GameContext_t&)const;

        uint32_t x {0} , y {0};
        uint32_t vx {1} , vy {1};
    };


}