extern "C" {
    #include "../../lib/tinyPTC/src/tinyptc.h"
}

#include <algorithm>
#include <cstdint>
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

        // Clip position to framebuffer bounds
        int32_t x0 = e.phy->x;
        int32_t y0 = e.phy->y;
        if (x0 >= static_cast<int32_t>(m_w)) return;
        if (y0 >= static_cast<int32_t>(m_h)) return;

        // Compute visible region
        int32_t clipW = static_cast<int32_t>(e.w);
        int32_t clipH = static_cast<int32_t>(e.h);
        int32_t srcOff{0};
        if (x0 < 0) { srcOff -= x0; clipW += x0; x0 = 0; }
        if (y0 < 0) { srcOff -= static_cast<int32_t>(e.w) * (-y0); clipH += y0; y0 = 0; }
        if (x0 + clipW > static_cast<int32_t>(m_w)) clipW = static_cast<int32_t>(m_w) - x0;
        if (y0 + clipH > static_cast<int32_t>(m_h)) clipH = static_cast<int32_t>(m_h) - y0;
        if (clipW <= 0 || clipH <= 0) return;

        auto dst = screen + static_cast<std::size_t>(y0) * m_w + static_cast<std::size_t>(x0);
        auto src = begin(e.sprite) + srcOff;

        for (int32_t row = 0; row < clipH; ++row, dst += m_w, src += static_cast<std::size_t>(e.w))
        {
            std::copy(src, src + clipW, dst);
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
