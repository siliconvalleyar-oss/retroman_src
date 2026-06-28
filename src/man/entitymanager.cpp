#include "entitymanager.hpp"
#include <iostream>

namespace ECS 
{
	EntityManager_t::EntityManager_t(){
	
		m_Entity.reserve(kNUMINITIALENTITIES);
	}
	
	void EntityManager_t::createEntity( uint32_t x , uint32_t y , uint32_t w ,uint32_t h , uint32_t color )
	{
		//auto& me = m_Entity.emplace_back(w,h);
		//  me.x = x ;
		//  me.y = y ;
		//  std::fill(me.sprite.begin() , me.sprite.end(),color);
	}
}

