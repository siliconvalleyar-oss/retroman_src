#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>
#include "entity.hpp"

namespace ECS{
	//foward declaration
//	struct Entity_t;

	// struct Entity_t
	// {
	// 	std::vector<uint32_t>sprite{};

	// 	explicit Entity_t(u_int32_t _w , u_int32_t _h)
	// 	: w(_w) , h(_h)
	// 	{
	// 		//sprite.resize(w*h); 
	// 		sprite.resize(w*h);	
	// 	}

	// 	uint32_t x { 0 } , y { 0 };	
	// 	uint32_t w { 0 } , h { 0 };
	// };


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

