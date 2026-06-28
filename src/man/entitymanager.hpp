#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>
#include "entity.hpp"

namespace ECS{
	struct  EntityManager_t 
	{
		using VecEntities_t = std::vector<Entity_t>;
		static constexpr std::size_t kNUMINITIALENTITIES { 1000 } ;	
		explicit EntityManager_t();
		void createEntity(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t) ;

		const VecEntities_t& getEntities() const
		{
			return m_Entity;
		}

	private:
		VecEntities_t m_Entity{};
	};

}

