#pragma once

#include <vector>

namespace ECS {

/// Generic vector type alias used throughout the ECS.
template <typename T>
using Vect_t = std::vector<T>;

/// Entity ID type – used to uniquely identify entities.
using EntityID_t = std::size_t;

} // namespace ECS
