#pragma once

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "../../lib/picoPNG/src/picopng.hpp"
#include "physics.hpp"
#include "../util/typealiases.hpp"

namespace ECS {

/// Component that represents a renderable game entity.
/// Holds position, dimensions, optional physics component pointer,
/// a pixel sprite, and a unique entity ID.
struct Entity_t
{
    /// Default destructor
    ~Entity_t() = default;

    /// Construct an entity with a blank sprite of given dimensions.
    /// @param _w  Width in pixels
    /// @param _h  Height in pixels
    explicit Entity_t(uint32_t _w, uint32_t _h)
        : w(_w), h(_h)
    {
        sprite.resize(w * h);
    }

    /// Construct an entity by loading a PNG file.
    /// Decodes RGBA8 PNG data and converts to packed uint32_t format.
    /// @param filename  Path to PNG file
    explicit Entity_t(std::string filename)
    {
        std::vector<unsigned char> pixels{};
        unsigned long dw{0}, dh{0};
        std::ifstream file(filename, std::ios::binary);

        std::vector<unsigned char> filevec(
            std::istreambuf_iterator<char>{file},
            std::istreambuf_iterator<char>{}
        );

        decodePNG(pixels, dw, dh, filevec.data(), filevec.size());

        sprite.reserve(pixels.size() / 4);
        w = dw;
        h = dh;

        // Convert RGBA byte sequence → packed uint32_t (XRGB)
        for (auto p = pixels.begin(); p != pixels.end(); p += 4)
        {
            uint32_t pixel =
                static_cast<uint32_t>(*(p + 0)) << 16 |
                static_cast<uint32_t>(*(p + 1)) <<  8 |
                static_cast<uint32_t>(*(p + 2))       |
                static_cast<uint32_t>(*(p + 3)) << 24;
            sprite.push_back(pixel);
        }
    }

    uint32_t x{0}, y{0};        ///< Screen position in pixels
    uint32_t vx{1}, vy{1};      ///< Velocity in pixels per frame
    PhysicsComponent_t* phy{ nullptr };  ///< Optional physics component
    uint32_t w{0}, h{0};        ///< Sprite dimensions in pixels

    std::vector<uint32_t> sprite{};   ///< Packed pixel data (XRGB)

    EntityID_t entityID;              ///< Unique identifier for this entity
};

} // namespace ECS
