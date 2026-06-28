# API Reference

All types reside in the `ECS` namespace.

---

## `Entity_t` — `src/man/entity.hpp`

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
~Entity_t();
```

Default destructor (defined in `entity.cpp`).

---

## `EntityManager_t` — `src/man/entitymanager.hpp`

Manages the entity pool. Owns a pre-allocated vector of entities.

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

Creates a new entity (WIP — currently a no-op stub).

---

```cpp
const VecEntities_t& getEntities() const;
```

Returns a const reference to the internal entity vector.

### Types

| Alias | Definition |
|-------|------------|
| `VecEntities_t` | `std::vector<Entity_t>` |

---

## `RenderSystem_t` — `src/sys/render.hpp`

Rendering system: owns the framebuffer, draws entities, interfaces with tinyPTC.

### Constants

| Name | Value | Description |
|------|-------|-------------|
| `kR` | `0x00FF0000` | Red channel mask |
| `kG` | `0x0000FF00` | Green channel mask |
| `kB` | `0x000000FF` | Blue channel mask |
| `msprite` | `uint32_t[64]` | Static 8×8 test sprite pattern |

### Constructor

```cpp
explicit RenderSystem_t(uint32_t width, uint32_t height, EntityManager_t& em);
```

Opens a tinyPTC window of `width`×`height` pixels and allocates the framebuffer.

### Destructor

```cpp
~RenderSystem_t();
```

Closes the tinyPTC window.

### Methods

```cpp
bool update() const;
```

Per-frame update:
1. Fill framebuffer with background colour (`0x0000FFF0`)
2. Call `drawAllEntities()`
3. Push framebuffer to screen via `ptc_update()`
4. Poll events via `ptc_process_events()`

Returns `true` while the window is open, `false` on close/quit.

---

```cpp
void drawAllEntities() const;
```

Iterates all entities from `EntityManager_t` and renders each one using `drawEntity()`.

---

```cpp
void drawEntity(const Entity_t& entity);
```

Blits an entity's sprite to the framebuffer at its (x,y) position.
Copies each sprite row into the correct scanline, accounting for the framebuffer pitch (`m_w`).

### Private Members

| Field | Type | Description |
|-------|------|-------------|
| `m_w` | `int32_t` | Framebuffer width |
| `m_h` | `int32_t` | Framebuffer height |
| `m_framebuffer` | `std::unique_ptr<uint32_t[]>` | Pixel buffer (m_w × m_h) |
| `m_EntMan` | `EntityManager_t&` | Reference to the entity manager |

---

## tinyPTC API (C) — `lib/tinyPTC/src/tinyptc.h`

Thin C wrapper over X11 for pixel-perfect window display.

| Function | Description |
|----------|-------------|
| `ptc_open(title, w, h)` | Create an X11 window |
| `ptc_update(buffer)` | Blit framebuffer to window |
| `ptc_close()` | Destroy window and free resources |
| `ptc_process_events()` | Check for X11 events (returns 1 if active, 0 on quit) |
