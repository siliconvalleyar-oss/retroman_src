
#include <iostream>
#include "entitymanager.hpp"
#include "../cmp/entity.hpp"

namespace ECS 
{
	EntityManager_t::EntityManager_t(){
	
		m_Entity.reserve(kNUMINITIALENTITIES);
	}
	
	void EntityManager_t::createEntity( uint32_t x , uint32_t y , uint32_t i  ,uint32_t j , uint32_t color )
	{

		//auto& e =m_Entity.emplace_back(filename);
//		auto& ph = m_components.createPhysicsComponent();
		//e.phy = ph;
		//ph.x = x; 
		//ph.y = y;

		//e.x =x ;  e.y  =y;
	//	e.x=; e.y = y;
	}
}

