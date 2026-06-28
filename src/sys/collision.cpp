#include <iostream>
#include "collision.hpp"
#include "../util/gamecontext.hpp"
//#include "../cmp/entity.hpp"

namespace ECS{

    bool CollisionSystem_t::update (GameContext_t& g)const{
        for(auto& e :g.getEntities()){
            //if(e.phy!= nullptr)
            {
             //if(e.phy->x > 640 || e.phy->x + e.w > 640 ){
                  //e.x -=e.vx ; e.vx -=e.vx; //se remplaza por : 
                  //e.phy->x -=e.phy->vx ; e.phy->vx  = -e.phy->vx;}
             //if(e.phy->y > 360 || e.phy-> + e.h > 360 ){ 
                 //e.phy->y -=e.phy->vy ; e.phy->vy  = -e.phy->vy;
                 //e.y -=e.vy ; e.vy -=e.vy; }       
            }     
        }
        return true;
    }
}
