extern "C" {
///    #include <tinyPTC/src/tinyptc.h>
    #include "../lib/tinyPTC/src/tinyptc.h"
  }
#include <cstdint>
#include <iostream>
#include <memory>
#include "sys/rendersystem.hpp"
#include "man/entitymanager.hpp"
#include "util/gamecontext.hpp"

constexpr uint32_t kSCRWIDTH { 480 };
constexpr uint32_t kSCRHEIGHT { 272 };

int main(void){
  
  try{
      ECS::EntityManager_t entityMan;
      entityMan.createEntity(20,40,16,16,0x00ffffff);
      const ECS::RenderSystem_t render{ kSCRWIDTH , kSCRHEIGHT};
      //const ECS::RenderSystem_t render{ kSCRWIDTH , kSCRHEIGHT , entityMan};
      while(render.update(entityMan));
  }
  catch(...){
    std::cout<< "break program"<<std::endl;
  }


  return 0;
}





