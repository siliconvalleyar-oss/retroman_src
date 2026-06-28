#include <iostream>
#include "componentstorage.hpp"

namespace ECS{


     PhysicsComponent_t& ComponentStorage_t::createPhysicsComponent(){

    //     auto& compo =  m_physicsComponents;//.emplace_back(); 

    //     return compo.emplace_back(); 
    return m_physicsComponent;
     }

}