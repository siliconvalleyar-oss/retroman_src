extern "C"{
	#include <tinyPTC/src/tinyptc.h>
}
#include <iostream>
#include <sys/render.hpp>
#include <../man/entitymanager.hpp>

namespace ECS{

	RenderSystem_t::RenderSystem_t(uint32_t w,uint32_t h,EntityManager_t& em )
	:  m_w { w }, m_h { h } 
	, m_framebuffer { std::make_unique<uint32_t[]>( m_w * m_h ) }
	, m_EntMan { em }
	{
		//std::cout<< "constructor render" <<std::endl;
		ptc_open("Program C++",w,h);
	}

	RenderSystem_t::~RenderSystem_t(){
		//std::cout<< "destructor render" <<std::endl;
		ptc_close();
	}

	void RenderSystem_t::drawAllEntities()const{

		}

	bool RenderSystem_t::update() const {
		auto screen = m_framebuffer.get();
		const auto size = m_w*m_h;
		std::fill(screen,screen + size , 0x0000FF00);
		//for(uint32_t i = 0 ;i< m_w * m_h ; ++i )screen[i]=kR;
		drawAllEntities();
		ptc_update(screen);
		return !ptc_process_events();
	}
}//namespace ECS
