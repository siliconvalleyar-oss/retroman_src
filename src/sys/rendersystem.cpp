extern "C"{
	#include "../../lib/tinyPTC/src/tinyptc.h"
}
#include <iostream>
#include "rendersystem.hpp"
#include "../man/entitymanager.hpp"

namespace ECS
{

	RenderSystem_t::RenderSystem_t(uint32_t w , uint32_t h )
	:  m_w { w }, m_h { h } 
	, m_framebuffer{ std::make_unique<uint32_t[]>( m_w * m_h ) }
	{
		ptc_open("Program C++",w,h);
	}

	RenderSystem_t::~RenderSystem_t(){
		ptc_close();
	}


	void RenderSystem_t::drawAllEntities(const Vect_t<Entity_t>& entities )const
	{	
		auto screen = m_framebuffer.get();

		auto getScreenXY = [&] (uint32_t x, uint32_t  y){
			return screen + y*m_w + x ;
		};

		auto drwEntity = [&](const Entity_t& e){

			//if(e.phy != nullptr)
			{
//				auto screen = getScreenXY(e.phy->x ,e.phy->y);
				auto sprite_it = begin(e.sprite);
				for(uint32_t y=0 ; y < e.h ; ++y ){
//					std::copy(sprite_it , sprite_it +e.w ,screen);
					sprite_it += e.w;
					screen += m_w;
				}
			}		
		};

		std::for_each(begin(entities) , end(entities) , drwEntity);
	}





	bool RenderSystem_t::update(const GameContext_t& g) const 
	{
		auto screen = m_framebuffer.get();
		const auto size = m_w*m_h;
		std::fill( screen , screen + size , 0x00999999);
		drawAllEntities( g.getEntities() );
		ptc_update(screen);
		return !ptc_process_events();
	}
}//namespace ECS
