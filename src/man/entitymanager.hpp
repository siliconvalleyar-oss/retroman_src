#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>
#include "componentstorage.hpp"
#include "../util/typealiases.hpp"
#include "../util/gamecontext.hpp"
//#include "../cmp/entity.hpp"

namespace ECS{
	struct GameContext_t;

	struct  EntityManager_t : public GameContext_t
	{
		static constexpr std::size_t kNUMINITIALENTITIES { 1000 } ;	
		explicit EntityManager_t();
		void createEntity(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t) ;
		const Vect_t<Entity_t>& getEntities() const override { return m_Entity; };
		      Vect_t<Entity_t>& getEntities()  override { return m_Entity; };
		const std::vector<PhysicsComponent_t>& getPhysicsComponent() const override {};
         	  std::vector<PhysicsComponent_t>& getPhysicsComponent()	   override {};

	private:
		Vect_t<Entity_t>m_Entity{};
		ComponentStorage_t m_components;
	};

}

