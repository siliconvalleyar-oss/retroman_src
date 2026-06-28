#pragma once
#include <cstdint>
#include <memory>

namespace ECS{
	//foward declaration
	struct EntityManager_t;
	struct Entity_t;

	struct RenderSystem_t
	{
		explicit RenderSystem_t(uint32_t w ,uint32_t h,EntityManager_t& em);
		~RenderSystem_t();
		bool update() const;
		void drawAllEntities()const;

		static constexpr uint32_t kR = 0x00FF0000;
		static constexpr uint32_t kG = 0x0000FF00;
		static constexpr uint32_t kB = 0x000000FF;
		static constexpr uint32_t sprite[8*8]={
			kG,kR,kB,kG,kR,kB,kG,
			kG,kR,kB,kG,kR,kB,kG,
			kG,kR,kB,kG,kR,kB,kG,
			kG,kR,kB,kG,kR,kB,kG,
			kG,kR,kB,kG,kR,kB,kG,
			kG,kR,kB,kG,kR,kB,kG,
			kG,kR,kB,kG,kR,kB,kG,
			kG,kR,kB,kG,kR,kB,kG,
		};

        private:
        	const int32_t m_w { 0 } , m_h { 0 };       
			std::unique_ptr<uint32_t[]> m_framebuffer{ nullptr };
			EntityManager_t& m_EntMan;
	};
}//end namespace ECS
