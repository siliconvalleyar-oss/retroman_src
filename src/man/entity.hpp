#pragma once 
#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

namespace ECS{
	struct Entity_t
	{
		std::vector<uint32_t>sprite{};
		
		~Entity_t();

		explicit Entity_t(u_int32_t _w , u_int32_t _h)
		: w(_w) , h(_h)
		{
			//sprite.resize(w*h); 
			sprite.resize(w*h);	
		}

		uint32_t x { 0 } , y { 0 };	
		uint32_t w { 0 } , h { 0 };
	};
}