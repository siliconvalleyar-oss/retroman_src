extern "C" {
///    #include <tinyPTC/src/tinyptc.h>
#include "../lib/tinyPTC/src/tinyptc.h"
}
#include <cstdint>
#include <iostream>
#include <memory>
#include "sys/render.hpp"
#include "../man/entitymanager.hpp"

constexpr uint32_t kSCRWIDTH { 480 };
constexpr uint32_t kSCRHEIGHT { 272 };

//void function(void);
int main(void){
  
  try{
      ECS::EntityManager_t entityMan;
 
      entityMan.createEntity(20,40,16,16,0x00f1f1f1);
      const ECS::RenderSystem_t Render{ kSCRWIDTH , kSCRHEIGHT , entityMan};
	    //while(Render.update());
  }
  catch(...){
    std::cout<< "break program"<<std::endl;
  }

  return 0;
}





void function(void)
{/*
auto x_screen = std::make_unique<uint32_t[]>( kSCRWIDTH * kSCRHEIGHT) ;
ptc_open("wall",kSCRWIDTH,kSCRHEIGHT);
  while (!ptc_process_events())
  {
    for(uint32_t i=0 ; i < kSCRWIDTH * kSCRHEIGHT ; ++i) x_screen[i]=0x00FF0000;
    uint32_t *pscr = x_screen.get();
    
    const uint32_t *psp = sprite;

    for(uint32_t i=0 ;i<8;++i){
      for(uint32_t j=0 ;j<8;++j){
        *pscr = *psp;
        ++pscr;
        ++psp;
      }
      pscr += 640-8;
    }
    ptc_update(x_screen.get());
   
  }

  ptc_close();
  */
}
