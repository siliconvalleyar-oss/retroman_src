#pragma once

#include <cstddef>
#include <vector>

namespace ECS {

/// Generic vector type alias used for entity storage throughout the ECS.
template <typename T>
using Vect_t = std::vector<T>;

/// Unique entity identifier type.
using EntityID_t = std::size_t;

} // namespace ECS
