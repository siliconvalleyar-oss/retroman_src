#pragma once 
#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>
#include <fstream>
#include "../../lib/picoPNG/src/picopng.hpp"
#include <iostream>
#include <cstring>
//#include "../man/physics.hpp"
#include "physics.hpp"
#include "../util/typealiases.hpp"


namespace ECS{


//using VecEntities_t = Vect_t <Entity_t>;


	struct Entity_t
	{
		~Entity_t()=default;
		
		explicit Entity_t(uint32_t _w , uint32_t _h)
		: w(_w) , h(_h)
		{
			sprite.resize(w*h);	
		}

		explicit Entity_t(std::string filename ){
			std::vector <unsigned char>pixels{};
			unsigned long dw{0},dh{0};
			std::ifstream file(filename ,std::ios::binary);
			//filename
			std::vector<unsigned char> filevec(
					std::istreambuf_iterator<char>{file}
				,	std::istreambuf_iterator<char>{}
				
			);


			decodePNG(pixels ,dw,dh,filevec.data() , filevec.size());
			sprite.reserve(pixels.size()/4);
			//std::memcpy(sprite.data() , pixels.data() , pixels.size());
			w=dw;
			h=dh;
			for (auto p =pixels.begin() ; p != pixels.end() ; p +=4){
				uint32_t pixel = 
				static_cast <uint32_t>(*(p+0))<<16
			|	static_cast <uint32_t>(*(p+1))<<8
			|	static_cast <uint32_t>(*(p+2))
			|	static_cast <uint32_t>(*(p+3))<<24;
				
				sprite.push_back(pixel);
			}

		}


		uint32_t x { 0 } , y { 0 };	//fala comentar
		uint32_t vx { 1 } , vy { 1 };//falta comentar
		PhysicsComponent_t* phy { nullptr };
		uint32_t w { 0 } , h { 0 };
		
		std::vector<uint32_t>sprite{};
	
		EntityID_t entityID;
	};
}