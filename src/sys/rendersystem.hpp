#pragma once

#include <cstdint>
#include <memory>

#include "../util/typealiases.hpp"
#include "../cmp/entity.hpp"

namespace ECS {

// Forward declarations
struct EntityManager_t;
struct GameContext_t;

/// Rendering system.
/// Owns the framebuffer and draws entity sprites to the screen
/// via tinyPTC over X11.
struct RenderSystem_t
{
    /// Construct and open a tinyPTC window.
    /// @param w  Window/framebuffer width
    /// @param h  Window/framebuffer height
    explicit RenderSystem_t(uint32_t w, uint32_t h);

    /// Destructor – closes the tinyPTC window.
    ~RenderSystem_t();

    /// Per-frame update: clear → draw → present → poll events.
    /// @param g  Game context providing entity data
    /// @return   true while the window is open, false on quit
    bool update(const GameContext_t& g) const;

    /// Draw all entities to the framebuffer.
    /// @param entities  Entity vector to render
    void drawAllEntities(const Vect_t<Entity_t>& entities) const;

    // Colour channel masks
    static constexpr uint32_t kR = 0x00FF0000;
    static constexpr uint32_t kG = 0x0000FF00;
    static constexpr uint32_t kB = 0x000000FF;

    /// Static 8×8 test sprite pattern
    static constexpr uint32_t msprite[8 * 8] = {
        kG, kR, kB, kG, kR, kB, kG,
        kG, kR, kB, kG, kR, kB, kG,
        kG, kR, kB, kG, kR, kB, kG,
        kG, kR, kB, kG, kR, kB, kG,
        kG, kR, kB, kG, kR, kB, kG,
        kG, kR, kB, kG, kR, kB, kG,
        kG, kR, kB, kG, kR, kB, kG,
        kG, kR, kB, kG, kR, kB, kG,
    };

private:
    const uint32_t m_w{0};                             ///< Framebuffer width
    const uint32_t m_h{0};                             ///< Framebuffer height
    std::unique_ptr<uint32_t[]> m_framebuffer{nullptr}; ///< Pixel buffer
};

} // namespace ECS
