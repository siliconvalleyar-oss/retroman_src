
#pragma once
//#include "util/gamecontext.hpp"

namespace ECS {

 struct  GameContext_t;

 struct PhysicsSystem_t
 {
 private:
 
 public:
     explicit PhysicsSystem_t()=default;
     bool update (GameContext_t&)const;


 };


}