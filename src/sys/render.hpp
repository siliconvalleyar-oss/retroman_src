#pragma once
#include <cstdint>
#include <memory>
namespace ECS{

	struct RenderSystem_t{

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
                explicit RenderSystem_t(uint32_t w ,uint32_t h);
                ~RenderSystem_t();
		bool update() const;
        private:
                const uint32_t m_w { 0 } , m_h { 0 };       
		std::unique_ptr<uint32_t> m_framebuffer{ nullptr };
	};
}//end namespace ECS
