# API Reference

All types reside in the `ECS` namespace.

---

## `Entity_t` — `src/cmp/entity.hpp`

Data component representing a renderable entity.

### Fields

| Field | Type | Description |
|-------|------|-------------|
| `x` | `uint32_t` | Screen X position |
| `y` | `uint32_t` | Screen Y position |
| `w` | `uint32_t` | Sprite width in pixels |
| `h` | `uint32_t` | Sprite height in pixels |
| `sprite` | `std::vector<uint32_t>` | Flat array of RGBA pixel data (row-major, size = w×h) |

### Constructor

```cpp
explicit Entity_t(uint32_t w, uint32_t h);
```

Allocates `sprite` with `w×h` pixels (zero-initialised).

### Destructor

```cpp
~Entity_t() = default;
```

---

## `GameContext_t` — `src/util/gamecontext.hpp`

Abstract base class providing a common interface for entity storage.

### Methods (pure virtual)

```cpp
virtual const VecEntities_t& getEntities() const = 0;
```

Returns a const reference to the entity vector.

---

## `EntityManager_t` — `src/man/entitymanager.hpp`

Manages the entity pool. Inherits from `GameContext_t`.

### Constants

| Name | Value | Description |
|------|-------|-------------|
| `kNUMINITIALENTITIES` | `1000` | Initial reserved capacity |

### Constructor

```cpp
explicit EntityManager_t();
```

Reserves space for `kNUMINITIALENTITIES` entities.

### Methods

```cpp
void createEntity(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
```

Creates a new entity (WIP — currently being refactored).

---

```cpp
const VecEntities_t& getEntities() const override;
```

Returns a const reference to the internal entity vector.

### Private Members

| Field | Type | Description |
|-------|------|-------------|
| `m_Entity` | `VecEntities_t` | Internal entity storage |

---

## `RenderSystem_t` — `src/sys/rendersystem.hpp`

Rendering system: owns the framebuffer, draws entities via `GameContext_t`, interfaces with tinyPTC.

### Constants

| Name | Value | Description |
|------|-------|-------------|
| `kR` | `0x00FF0000` | Red channel mask |
| `kG` | `0x0000FF00` | Green channel mask |
| `kB` | `0x000000FF` | Blue channel mask |
| `msprite` | `uint32_t[64]` | Static 8×8 test sprite pattern |

### Constructor

```cpp
explicit RenderSystem_t(uint32_t width, uint32_t height);
```

Opens a tinyPTC window of `width`×`height` pixels and allocates the framebuffer.

### Destructor

```cpp
~RenderSystem_t();
```

Closes the tinyPTC window.

### Methods

```cpp
bool update(const GameContext_t& ctx) const;
```

Per-frame update:
1. Fill framebuffer with background colour (`0x00999999`)
2. Call `drawAllEntities(ctx.getEntities())`
3. Push framebuffer to screen via `ptc_update()`
4. Poll events via `ptc_process_events()`

Returns `true` while the window is open, `false` on close/quit.

---

```cpp
void drawAllEntities(const VecEntities_t& entities) const;
```

Renders all entities using a lambda that blits each sprite to the framebuffer at its (x,y) position.

### Private Members

| Field | Type | Description |
|-------|------|-------------|
| `m_w` | `uint32_t` | Framebuffer width |
| `m_h` | `uint32_t` | Framebuffer height |
| `m_framebuffer` | `std::unique_ptr<uint32_t[]>` | Pixel buffer (m_w × m_h) |

---

## Helper Types — `src/util/typealiases.hpp`

```cpp
using VecEntities_t = std::vector<Entity_t>;
```

---

## tinyPTC API (C) — `lib/tinyPTC/src/tinyptc.h`

Thin C wrapper over X11 for pixel-perfect window display.

| Function | Description |
|----------|-------------|
| `ptc_open(title, w, h)` | Create an X11 window |
| `ptc_update(buffer)` | Blit framebuffer to window |
| `ptc_close()` | Destroy window and free resources |
| `ptc_process_events()` | Check for X11 events (returns 1 if active, 0 on quit) |
