extern "C" {
    #include "../../lib/tinyPTC/src/tinyptc.h"
}

#include <algorithm>
#include <iostream>
#include "rendersystem.hpp"
#include "../man/entitymanager.hpp"
#include "../util/gamecontext.hpp"

namespace ECS {

/// Open a tinyPTC window and allocate the framebuffer.
RenderSystem_t::RenderSystem_t(uint32_t w, uint32_t h)
    : m_w{w}, m_h{h}
    , m_framebuffer{std::make_unique<uint32_t[]>(m_w * m_h)}
{
    ptc_open("Retroman", w, h);
}

/// Close the tinyPTC window.
RenderSystem_t::~RenderSystem_t()
{
    ptc_close();
}

/// Blit all entity sprites to the framebuffer at their physics position.
void RenderSystem_t::drawAllEntities(const Vect_t<Entity_t>& entities) const
{
    auto screen = m_framebuffer.get();

    auto drawOne = [&](const Entity_t& e)
    {
        if (!e.phy) return;

        auto dst = screen + e.phy->y * m_w + e.phy->x;
        auto src = begin(e.sprite);

        for (uint32_t row = 0; row < e.h; ++row, dst += m_w, src += e.w)
        {
            std::copy(src, src + e.w, dst);
        }
    };

    std::for_each(begin(entities), end(entities), drawOne);
}

/// Per-frame update: clear, draw, present, poll.
bool RenderSystem_t::update(const GameContext_t& g) const
{
    auto screen = m_framebuffer.get();

    // Clear framebuffer
    std::fill(screen, screen + m_w * m_h, 0x00999999);

    // Draw all entities
    drawAllEntities(g.getEntities());

    // Push to screen
    ptc_update(screen);

    // Return false when window is closed
    return !ptc_process_events();
}

} // namespace ECS
