#include <stdint>
namespace ECS{
	struct Entity_t{
		explicit Entity()
		: w (_w) , h(_h)
		{
			m_sprite.reserve(w*h);	
		}
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
	
		uint32_t x { 0 } , y { 0 };	
		uint32_t w { 0 } , h { 0 };
		std::vector<uint32_t>m_sprite{ nullptr };
	};

	struct  EntityManager_t
	{
		static constexpr std::size_t kNUMINITIALENTITIES{1000}
		explicit EntityManager_t();
		void createEntity(uint32_t w , uint32_t h , uint32_t color);
	private:
		std::vector<Entity_t> m_Entity{nullptr};
	};

}

