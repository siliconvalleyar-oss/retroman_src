#include "entity.hpp"
#include "component.hpp"

namespace ECS {

/// Static ID counter for generating unique entity identifiers.
EntityID_t Entity_t::nextID{0};

/// Static ID counter for the base Component_t.
std::size_t Component_t::nextID{0};

} // namespace ECS
