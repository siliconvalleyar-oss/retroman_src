#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "../../lib/picoPNG/src/picopng.hpp"
#include "physics.hpp"
#include "../util/typealiases.hpp"

namespace ECS {

/// Component that represents a renderable game entity.
/// Holds position, dimensions, a pixel sprite, an optional physics component,
/// and a unique entity identifier.
struct Entity_t
{
    /// Construct an entity with a blank sprite of given dimensions.
    explicit Entity_t(uint32_t _w, uint32_t _h)
        : w(_w), h(_h)
    {
        sprite.resize(w * h);
    }

    /// Construct an entity by loading a PNG file.
    /// Decodes RGBA8 data and converts to packed uint32_t format (XRGB).
    explicit Entity_t(const std::string& filename)
    {
        std::vector<unsigned char> pixels{};
        unsigned long dw{0}, dh{0};
        std::ifstream file(filename, std::ios::binary);
        std::vector<unsigned char> filevec(
            std::istreambuf_iterator<char>{file},
            std::istreambuf_iterator<char>{}
        );

        decodePNG(pixels, dw, dh, filevec.data(), filevec.size());

        w = static_cast<uint32_t>(dw);
        h = static_cast<uint32_t>(dh);
        sprite.reserve(pixels.size() / 4);

        // Convert RGBA byte sequence -> packed uint32_t (XRGB)
        for (auto p = pixels.begin(); p != pixels.end(); p += 4)
        {
            uint32_t pixel =
                (static_cast<uint32_t>(p[0]) << 16) |
                (static_cast<uint32_t>(p[1]) <<  8) |
                (static_cast<uint32_t>(p[2])      ) |
                (static_cast<uint32_t>(p[3]) << 24);
            sprite.push_back(pixel);
        }
    }

    uint32_t x{0}, y{0};                ///< Screen position in pixels
    uint32_t vx{1}, vy{1};              ///< Velocity in pixels per frame
    uint32_t w{0}, h{0};                ///< Sprite dimensions

    std::vector<uint32_t> sprite{};     ///< Packed pixel data (XRGB format)

    PhysicsComponent_t* phy{nullptr};   ///< Optional physics component
    EntityID_t entityID{++nextID};      ///< Unique identifier
    static EntityID_t nextID;           ///< Auto-incrementing ID counter
};

} // namespace ECS
