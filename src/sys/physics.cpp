#include "physics.hpp"
//#include "../man/physics.hpp"
#include "../util/gamecontext.hpp"

namespace ECS{

    bool PhysicsSystem_t::update (GameContext_t& g)const{
        for(auto& phy :g.getEntities()){
           
             //if(e.x + e.w > 640 ){ e.x -=e.vx ; e.vx -=e.vx; }
             //if(e.y + e.h > 360 ){ e.y -=e.vy ; e.vy -=e.vy; }
            
            phy.x += phy.vx;
            phy.y += phy.vy;
             
        }
        return true;
    }
}