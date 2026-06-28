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



	void RenderSystem_t::drawEntity(const Entity_t& e)
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
		auto& entities { m_EntMan.getEntities()}; 
		this->m_framebuffer.get();
		auto screen = m_framebuffer.get();
		// struct A{
		// 	A( const std::unique_ptr<uint32_t[]>& mf , const uint32_t& w )
		// 	: m_framebuffer(mf) , m_w(w)
		// 	{
		// 	}
			
		// 	void operator()(const Entity_t& e) const{
		// 		auto screen = m_framebuffer.get();
		// 		screen += e.y + e.x ; 
		// 		auto sprite_it = begin(e.sprite);
		// 		for(uint32_t y=0; y < e.h ; ++y){
		// 	std::copy(sprite_it , sprite_it + e.w, screen );
		// 			sprite_it += e.w;
		// 			screen += m_w;
		// 		}
		// 	};
		// 	const std::unique_ptr<uint32_t[]>& m_framebuffer;
		// 	const uint32_t& m_w;
		// };
		// A drwEntity(m_framebuffer , m_w);
		auto getScreenXY = [&] (uint32_t x, uint32_t  y){
			return screen + y*m_w + x ;
		};

		auto drwEntity = [&](const Entity_t& e){
			auto screen = getScreenXY(e.x ,e.y);
			auto sprite_it = begin(e.sprite);
			for(uint32_t y=0 ; y < e.h ; ++y ){
				std::copy(sprite_it , sprite_it +e.w ,screen);
				sprite_it += e.w;
				screen += m_w;
			}
		};

		std::for_each(begin(entities) , end(entities) , drwEntity);  // ver da error
	}





	bool RenderSystem_t::update() const 
	{
		auto screen = m_framebuffer.get();
		const auto size = m_w*m_h;
		std::fill( screen , screen + size , 0x0000FFF0);
					//for(uint32_t i = 0 ;i< m_w * m_h ; ++i )screen[i]=kR;
		drawAllEntities();
		ptc_update(screen);
		return !ptc_process_events();
	}
}//namespace ECS
