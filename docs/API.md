# API Reference

All types reside in the `ECS` namespace.

---

## `Entity_t` — `src/cmp/entity.hpp`

Data component representing a renderable game entity with position, velocity, dimensions, and sprite data.

### Fields

| Field | Type | Description |
|-------|------|-------------|
| `x` | `uint32_t` | Screen X position |
| `y` | `uint32_t` | Screen Y position |
| `vx` | `uint32_t` | Horizontal velocity (pixels/frame) |
| `vy` | `uint32_t` | Vertical velocity (pixels/frame) |
| `w` | `uint32_t` | Sprite width in pixels |
| `h` | `uint32_t` | Sprite height in pixels |
| `sprite` | `std::vector<uint32_t>` | Flat RGBA pixel data (row-major, size = w×h) |

### Constructors

```cpp
explicit Entity_t(uint32_t w, uint32_t h);
```

Allocates `sprite` with `w×h` pixels (zero-initialised).

---

```cpp
explicit Entity_t(std::string filename);
```

Loads a PNG file via picoPNG, decodes it, and populates `sprite`, `w`, `h` from the image data.

### Methods

```cpp
bool has_physics();
```

Returns `true` — indicates this entity should be processed by physics/collision systems.

### Destructor

```cpp
~Entity_t() = default;
```

---

## `GameContext_t` — `src/util/gamecontext.hpp`

Abstract base class providing a common interface for entity storage.
All systems receive a `GameContext_t&` to access entities.

### Methods (pure virtual)

```cpp
virtual const VecEntities_t& getEntities() const = 0;
```

Read-only access to the entity vector.

---

```cpp
virtual VecEntities_t& getEntities() = 0;
```

Mutable access to the entity vector (for systems that modify entities).

### Destructor

```cpp
virtual ~GameContext_t() = default;
```

Polymorphic destructor for safe deletion through base pointer.

---

## `EntityManager_t` — `src/man/entitymanager.hpp`

Manages the entity pool. Inherits from `GameContext_t`.

### Constants

| Name | Value | Description |
|------|-------|-------------|
| `kNUMINITIALENTITIES` | `1000` | Pre-allocated capacity |

### Constructor

```cpp
explicit EntityManager_t();
```

Reserves space for `kNUMINITIALENTITIES` entities.

### Methods

```cpp
void createEntity(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
```

Creates a new entity with the given position, dimensions, and fill color.

---

```cpp
const VecEntities_t& getEntities() const override;
VecEntities_t& getEntities() override;
```

Returns a const or mutable reference to the internal entity vector.

### Private Members

| Field | Type | Description |
|-------|------|-------------|
| `m_Entity` | `VecEntities_t` | Internal entity storage |

---

## `RenderSystem_t` — `src/sys/rendersystem.hpp`

Rendering system: owns the framebuffer, draws entity sprites via `GameContext_t`, interfaces with tinyPTC.

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

Renders all entities using a lambda that blits each sprite to the framebuffer at its `(x, y)` position. Copies each sprite row into the correct scanline, accounting for the framebuffer pitch (`m_w`).

### Private Members

| Field | Type | Description |
|-------|------|-------------|
| `m_w` | `uint32_t` | Framebuffer width |
| `m_h` | `uint32_t` | Framebuffer height |
| `m_framebuffer` | `std::unique_ptr<uint32_t[]>` | Pixel buffer (m_w × m_h) |

---

## `PhysicsSystem_t` — `src/sys/physics.hpp`

Velocity-based movement system. Updates entity positions each frame.

### Constructor

```cpp
PhysicsSystem_t();
```

### Destructor

```cpp
~PhysicsSystem_t();
```

### Methods

```cpp
bool update(GameContext_t& g) const;
```

Iterates all entities. If an entity reaches the screen boundary (640×360), its velocity is reversed to simulate a bounce.

---

## `CollisionSystem_t` — `src/sys/collision.hpp`

Screen-edge collision detection and response system.

### Constructor

```cpp
CollisionSystem_t();
```

### Destructor

```cpp
~CollisionSystem_t();
```

### Methods

```cpp
bool update(GameContext_t& g) const;
```

Iterates all entities. Detects when an entity exceeds the screen boundaries (640×360), corrects its position, and reverses its velocity.

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
