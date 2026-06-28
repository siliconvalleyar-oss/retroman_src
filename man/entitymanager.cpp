
#include <algorithm>
#include "entitymanager.hpp"

namespace ECS {
	EntityManager_t::EntityManager_t(){
		//m_Entity.reserve(kNUMINITIALENTITIES);
		m_Entity.reserve(kNUMINITIALENTITIES);
	}
	
	void EntityManager_t::createEntity(uint32_t x,uint32_t y , uint32_t w ,uint32_t h , uint32_t color)
	{
		auto& e = m_Entity.emplace_back(w,h);

		e.x = x ;
		e.y = y ;
		std::fill(e.sprite.begin() , e.sprite.end(),color);
	}
}

