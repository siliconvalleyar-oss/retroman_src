# Architecture

Retroman is a retro arcade game engine using an **Entity-Component-System (ECS)** architecture, rendered via **tinyPTC** over X11 on Linux.

## Overview

```
┌─────────────────────────────────────────────────────────────┐
│                        main.cpp                             │
│  Creates: EntityManager, RenderSystem, Physics, Collision   │
│  Game loop:                                                 │
│    while(render.update(ctx)) {                              │
│      physics.update(ctx);                                   │
│      collision.update(ctx);                                 │
│    }                                                        │
└──────────┬──────────┬──────────────┬────────────────────────┘
           │          │              │
           ▼          ▼              ▼
┌──────────────┐ ┌──────────┐ ┌──────────────┐
│    Render    │ │ Physics  │ │  Collision   │
│   System_t   │ │System_t  │ │ System_t     │
│  (src/sys/)  │ │(src/sys/)│ │ (src/sys/)   │
│              │ │          │ │              │
│  Owns fb     │ │ Updates  │ │ Screen-edge  │
│  Blits       │ │ entity   │ │ collision    │
│  sprites     │ │ position │ │ detection    │
└──────┬───────┘ └──────────┘ └──────────────┘
       │              │              │
       └──────────────┴──────────────┘
                      │
                      ▼
        ┌───────────────────────────┐
        │     GameContext_t          │
        │  (src/util/gamecontext.)   │
        │  Abstract base:            │
        │    getEntities() const     │
        │    getEntities() mutable   │
        └──────────┬─────────────────┘
                   │
                   ▼
        ┌───────────────────────────┐
        │     EntityManager_t        │
        │  (src/man/)                │
        │  Inherits GameContext_t    │
        │  Stores entities in vector │
        └──────────┬─────────────────┘
                   │
                   ▼
        ┌───────────────────────────┐
        │     Entity_t (Component)   │
        │  src/cmp/entity.hpp        │
        │                            │
        │  Position (x,y)            │
        │  Velocity (vx,vy)          │
        │  Dimensions (w,h)          │
        │  Pixel sprite (vector)     │
        │  PNG loader constructor    │
        └───────────────────────────┘
```

## Namespace: `ECS`

All engine types live in the `ECS` namespace.

### `Entity_t` (`src/cmp/entity.hpp`)

Data component representing a renderable game entity:
- `x`, `y` — screen position
- `vx`, `vy` — velocity in pixels per frame
- `w`, `h` — sprite dimensions
- `sprite` — `std::vector<uint32_t>` of RGBA pixel data
- `has_physics()` — flag for physics processing
- Two constructors: dimensions-based and PNG file loader

### `GameContext_t` (`src/util/gamecontext.hpp`)

Abstract base class providing a common interface for entity storage:
- `virtual getEntities() const` — read-only access
- `virtual getEntities()` — mutable access for systems that modify entities
- `virtual ~GameContext_t()` — polymorphic destructor

### `EntityManager_t` (`src/man/entitymanager.hpp`)

Manages the entity pool, inherits `GameContext_t`:
- Pre-allocates space for `kNUMINITIALENTITIES` (1000)
- `createEntity(...)` — allocates a new entity
- `getEntities() override` — returns ref to internal entity vector

### `RenderSystem_t` (`src/sys/rendersystem.hpp`)

Rendering system:
- Owns the framebuffer (`unique_ptr<uint32_t[]>`)
- Receives `GameContext_t&` per frame via `update()`
- `update(ctx)` — per-frame: clear → draw → present → poll events
- `drawAllEntities(entities)` — renders all entity sprites using lambdas

### `PhysicsSystem_t` (`src/sys/physics.hpp`)

Velocity-based movement system:
- `update(ctx)` — applies velocity to entity position
- Basic boundary bounce: reverses velocity on screen edge contact

### `CollisionSystem_t` (`src/sys/collision.hpp`)

Screen-edge collision system:
- `update(ctx)` — detects when entities exceed screen boundaries
- Corrects position and reverses velocity on collision

## Render Pipeline (per frame)

1. **Clear** — fill entire framebuffer with background color (`0x00999999`)
2. **Draw** — for each entity, blit its sprite rows to the correct screen position
3. **Present** — call `ptc_update()` to push framebuffer to the X11 window
4. **Poll** — `ptc_process_events()` checks for window close; returns false to exit

## Game Loop

```
while (render.update(entityMan)) {
    physics.update(entityMan);   // move entities
    collision.update(entityMan); // resolve collisions
}
```

## Include Convention

All includes use **relative quoted paths**:

| Source file | Include path |
|-------------|-------------|
| `src/main.cpp` | `"sys/rendersystem.hpp"`, `"man/entitymanager.hpp"`, `"util/gamecontext.hpp"`, `"sys/collision.hpp"`, `"sys/physics.hpp"` |
| `src/sys/rendersystem.cpp` | `"rendersystem.hpp"`, `"../man/entitymanager.hpp"` |
| `src/sys/physics.cpp` | `"physics.hpp"`, `"../util/gamecontext.hpp"` |
| `src/sys/collision.cpp` | `"collision.hpp"`, `"../util/gamecontext.hpp"` |
| `src/man/entitymanager.hpp` | `"../util/typealiases.hpp"`, `"../util/gamecontext.hpp"` |
| `src/man/entitymanager.cpp` | `"entitymanager.hpp"`, `"../cmp/entity.hpp"` |
| `src/util/gamecontext.hpp` | `"../cmp/entity.hpp"`, `"typealiases.hpp"` |
| `src/util/typealiases.hpp` | `"../cmp/entity.hpp"` |

## Build System

The `Makefile` uses custom macros (`COMPILE`, `C2O`, `C2H`) for build rules:
- Recursively finds all `.cpp`/`.c` sources under `src/`
- Generates object files into `obj/` mirroring the `src/` directory tree
- Links against `lib/tinyPTC/libtinyptc.a`, `libX11`, `libXext`

## Dependency Graph

```
main.cpp
  ├── sys/rendersystem.hpp → rendersystem.cpp
  │     ├── man/entitymanager.hpp → entitymanager.cpp
  │     │     ├── util/typealiases.hpp
  │     │     │     └── cmp/entity.hpp → entity.cpp
  │     │     └── util/gamecontext.hpp
  │     │           ├── cmp/entity.hpp
  │     │           └── util/typealiases.hpp
  │     └── lib/tinyPTC/src/tinyptc.h (external)
  ├── sys/physics.hpp → physics.cpp
  │     └── util/gamecontext.hpp
  ├── sys/collision.hpp → collision.cpp
  │     └── util/gamecontext.hpp
  └── man/entitymanager.hpp
        ├── util/typealiases.hpp
        └── util/gamecontext.hpp
```

## Versioning

See [RULES.md](RULES.md). Version is stored in `VERSION` and tagged as `v<VERSION>`.
