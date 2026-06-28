#pragma once 
#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

namespace ECS{
	struct Entity_t
	{
		std::vector<uint32_t>sprite{};
		
		~Entity_t()=default;
		
		explicit Entity_t(uint32_t _w , uint32_t _h)
		: w(_w) , h(_h)
		{
			sprite.resize(w*h);	
		}

		//Entity_t& operator=(const Entity_t& other)=default;
		
		uint32_t x { 0 } , y { 0 };	
		uint32_t w { 0 } , h { 0 };
	};
}