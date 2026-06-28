#pragma once
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

namespace ECS{
	struct Entity_t{
		explicit Entity_t(u_int32_t _w , u_int32_t _h)
		: w(_w) , h(_h)
		{
			sprite.resize(w*h);	
		}

		uint32_t x { 0 } , y { 0 };	
		uint32_t w { 0 } , h { 0 };
		std::vector<uint32_t> sprite{};
	};

	struct  EntityManager_t {
		static constexpr std::size_t kNUMINITIALENTITIES { 1000 } ;
		explicit EntityManager_t();
		void createEntity(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);

		//void createEntity(uint32_t x , uint32_t y,uint32_t w , uint32_t h , uint32_t color);
	private:
		std::vector<Entity_t>m_Entity{};
	};

}

