# API Reference

All types reside in the `ECS` namespace.

---

## `Entity_t` — `src/cmp/entity.hpp`

Renderable game entity with an optional physics component.

### Fields

| Field | Type | Description |
|-------|------|-------------|
| `x` | `uint32_t` | Screen X position |
| `y` | `uint32_t` | Screen Y position |
| `vx` | `uint32_t` | Horizontal velocity (pixels/frame) |
| `vy` | `uint32_t` | Vertical velocity (pixels/frame) |
| `w` | `uint32_t` | Sprite width in pixels |
| `h` | `uint32_t` | Sprite height in pixels |
| `sprite` | `std::vector<uint32_t>` | Packed RGBA pixel data (XRGB) |
| `phy` | `PhysicsComponent_t*` | Pointer to physics component (nullable) |
| `entityID` | `EntityID_t` | Unique auto-incrementing identifier |

### Constructors

```cpp
explicit Entity_t(uint32_t w, uint32_t h);
```
Creates a blank sprite of given dimensions.

```cpp
explicit Entity_t(const std::string& filename);
```
Loads a PNG file via picoPNG, converts RGBA byte data to packed XRGB `uint32_t` pixels.

### Static Members

```cpp
static EntityID_t nextID;
```
Auto-incrementing counter for generating unique entity IDs.

---

## `PhysicsComponent_t` — `src/cmp/physics.hpp`

Pure data component holding position and velocity.

| Field | Type | Description |
|-------|------|-------------|
| `x` | `uint32_t` | Position X |
| `y` | `uint32_t` | Position Y |
| `vx` | `uint32_t` | Velocity X |
| `vy` | `uint32_t` | Velocity Y |

---

## `GameContext_t` — `src/util/gamecontext.hpp`

Abstract interface for entity and component access.

```cpp
virtual ~GameContext_t() = default;
virtual const Vect_t<Entity_t>& getEntities() const = 0;
virtual Vect_t<Entity_t>& getEntities() = 0;
virtual const std::vector<PhysicsComponent_t>& getPhysicsComponent() const = 0;
virtual std::vector<PhysicsComponent_t>& getPhysicsComponent() = 0;
```

---

## `EntityManager_t` — `src/man/entitymanager.hpp`

Entity pool implementing `GameContext_t`. Owns entity vector and `ComponentStorage_t`.

### Constants

| Name | Value | Description |
|------|-------|-------------|
| `kNUMINITIALENTITIES` | `1000` | Pre-allocated capacity |

### Methods

```cpp
explicit EntityManager_t();
```
Reserves entity and physics component storage.

```cpp
void createEntity(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
```
Creates an entity with a solid-colour sprite and an associated physics component.

```cpp
void createEntity(uint32_t x, uint32_t y, const std::string& filename);
```
Creates an entity from a PNG file with an associated physics component.

---

## `ComponentStorage_t` — `src/man/componentstorage.hpp`

RAII component storage. Non-copyable.

```cpp
PhysicsComponent_t& createPhysicsComponent();
std::vector<PhysicsComponent_t>& getPhysicsComponent();
const std::vector<PhysicsComponent_t>& getPhysicsComponent() const;
```

---

## `RenderSystem_t` — `src/sys/rendersystem.hpp`

TinyPTC window and framebuffer rendering.

### Constants

| Name | Value | Description |
|------|-------|-------------|
| `kR` | `0x00FF0000` | Red mask |
| `kG` | `0x0000FF00` | Green mask |
| `kB` | `0x000000FF` | Blue mask |
| `msprite[64]` | — | Static 8×8 test sprite |

### Methods

```cpp
explicit RenderSystem_t(uint32_t width, uint32_t height);
~RenderSystem_t();
bool update(const GameContext_t& ctx) const;
void drawAllEntities(const Vect_t<Entity_t>& entities) const;
```

### Private Members

| Field | Type | Description |
|-------|------|-------------|
| `m_w` | `uint32_t` | Framebuffer width |
| `m_h` | `uint32_t` | Framebuffer height |
| `m_framebuffer` | `unique_ptr<uint32_t[]>` | Pixel buffer |

---

## `PhysicsSystem_t` — `src/sys/physics.hpp`

```cpp
bool update(GameContext_t& g) const;
```
Adds velocity to position for every `PhysicsComponent_t`.

---

## `CollisionSystem_t` — `src/sys/collision.hpp`

```cpp
bool update(GameContext_t& g) const;
```
Reverses velocity when an entity's physics component reaches screen edge (640×360).

---

## Helper Types — `src/util/typealiases.hpp`

```cpp
template <typename T> using Vect_t = std::vector<T>;
using EntityID_t = std::size_t;
```

---

## tinyPTC API (C) — `lib/tinyPTC/src/tinyptc.h`

| Function | Description |
|----------|-------------|
| `ptc_open(title, w, h)` | Create X11 window |
| `ptc_update(buffer)` | Blit framebuffer to window |
| `ptc_close()` | Destroy window |
| `ptc_process_events()` | Returns 1 if active, 0 on quit |

## picoPNG API (C++) — `lib/picoPNG/src/picopng.hpp`

| Function | Description |
|----------|-------------|
| `decodePNG(out, w, h, in, insize)` | Decode PNG to RGBA bytes |
