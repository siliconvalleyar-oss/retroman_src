extern "C"{
	#include "../../lib/tinyPTC/src/tinyptc.h"
}

#include "../sys/render.hpp"
#include "../man/entitymanager.hpp"

namespace ECS
{

	RenderSystem_t::RenderSystem_t(uint32_t w , uint32_t h , EntityManager_t& em )
	:  m_w { w }, m_h { h } 
	, m_framebuffer { std::make_unique<uint32_t[]>( m_w * m_h ) }
	, m_EntMan { em }
	//,screen {m_framebuffer.get()}
	{
		// std::cout<< "constructor render" <<std::endl;
		ptc_open("Program C++",w,h);
	}

	RenderSystem_t::~RenderSystem_t(){
		//std::cout<< "destructor render" <<std::endl;
		ptc_close();
		//delete m_EntMan;
	}



	void RenderSystem_t::drawEnitity(const Entity_t& e)
	{
		auto screen = m_framebuffer.get();

		screen += e.y*m_w + e.x;
		auto sprite_it = begin(e.sprite);

		for(uint32_t j=0 ;j<e.h; ++j)
		{
				std::copy (sprite_it, sprite_it + e.w , screen);
				sprite_it += e.w;
				screen += m_w;

		}

	
	}


	void RenderSystem_t::drawAllEntities()const
	{	
		auto& entities { m_EntMan.getEntities()}; //corregir 

		std::for_each(begin(entities) , end(entities) , drawEnitity);
	}

	bool RenderSystem_t::update() const 
	{
		auto screen = m_framebuffer.get();
		const auto size = m_w*m_h;
		std::fill(screen,screen + size , 0x0000FFF0);
		//for(uint32_t i = 0 ;i< m_w * m_h ; ++i )screen[i]=kR;
		drawAllEntities();
		ptc_update(screen);
		return !ptc_process_events();
	}
}//namespace ECS
