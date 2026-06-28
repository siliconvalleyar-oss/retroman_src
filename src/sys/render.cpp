extern "C"{
	#include <tinyPTC/src/tinyptc.h>
}
#include <iostream>
#include <sys/render.hpp>

namespace ECS{
	RenderSystem_t::RenderSystem_t(uint32_t w,uint32_t h)
	:  m_w {w}, m_h{h} 
	{
		std::cout<< "constructor render" <<std::endl;
		ptc_open("Program C++",w,h);
	}
	RenderSystem_t::~RenderSystem_t(){
		std::cout<< "destructor render" <<std::endl;
		ptc_close();
	}

	bool RenderSystem_t::update() const {
		auto screen = m_framebuffer.get();
		for(uint32_t i = 0 ;i< m_w * m_h ; ++i )screen[i]=kR;
		ptc_update(screen);
		return !ptc_process_events();
	}
}//namespace ECS
