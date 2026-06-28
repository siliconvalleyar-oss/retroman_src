extern "C" {
    #include "../../lib/tinyPTC/src/tinyptc.h"
}

#include <iostream>
#include "rendersystem.hpp"
#include "../man/entitymanager.hpp"

namespace ECS {

/// Constructor – opens a tinyPTC window and allocates the framebuffer.
/// @param w  Window width in pixels
/// @param h  Window height in pixels
RenderSystem_t::RenderSystem_t(uint32_t w, uint32_t h)
    : m_w{w}, m_h{h}
    , m_framebuffer{std::make_unique<uint32_t[]>(m_w * m_h)}
{
    ptc_open("Program C++", w, h);
}

/// Destructor – closes the tinyPTC window.
RenderSystem_t::~RenderSystem_t()
{
    ptc_close();
}

/// Draw all entities to the framebuffer using lambda-based sprite blitting.
/// For each entity, copies sprite rows into the framebuffer at position.
/// @param entities  Entity vector to render
void RenderSystem_t::drawAllEntities(const Vect_t<Entity_t>& entities) const
{
    auto screen = m_framebuffer.get();

    // Lambda to compute framebuffer offset for a given screen position
    auto getScreenXY = [&](uint32_t x, uint32_t y) {
        return screen + y * m_w + x;
    };

    // Lambda to blit a single entity's sprite to the framebuffer
    auto drwEntity = [&](const Entity_t& e) {
        if (e.phy != nullptr)
        {
            auto screen = getScreenXY(e.phy->x, e.phy->y);
            auto sprite_it = begin(e.sprite);
            for (uint32_t y = 0; y < e.h; ++y)
            {
                std::copy(sprite_it, sprite_it + e.w, screen);
                sprite_it += e.w;
                screen += m_w;
            }
        }
    };

    std::for_each(begin(entities), end(entities), drwEntity);
}

/// Per-frame update: fill background, draw entities, present, poll events.
/// @param g  Game context providing entity data
/// @return   true while running, false on window close
bool RenderSystem_t::update(const GameContext_t& g) const
{
    auto screen = m_framebuffer.get();
    const auto size = m_w * m_h;

    // Clear framebuffer to background colour
    std::fill(screen, screen + size, 0x00999999);

    // Render all entities
    drawAllEntities(g.getEntities());

    // Present framebuffer to screen
    ptc_update(screen);

    // Return false when window close is requested
    return !ptc_process_events();
}

} // namespace ECS
