# Architecture

Retroman is a retro arcade game engine using an **Entity-Component-System (ECS)** architecture, rendered via **tinyPTC** over X11 on Linux.

## Overview

```
┌─────────────────────────────────────────────────────────┐
│                       main.cpp                          │
│  Creates: EntityManager, RenderSystem, Physics, Collision│
│  Game loop:                                              │
│    while (render.update(ctx)) {                          │
│        physics.update(ctx);                              │
│        collision.update(ctx);                            │
│    }                                                     │
└──────────┬──────────┬────────────┬───────────────────────┘
           │          │            │
           ▼          ▼            ▼
┌──────────────┐ ┌──────────┐ ┌──────────┐
│    Render    │ │  Physics  │ │ Collision │
│   System_t   │ │ System_t  │ │ System_t  │
│  (src/sys/)  │ │(src/sys/) │ │(src/sys/) │
│              │ │          │ │          │
│  Blits       │ │ Applies  │ │ Boundary  │
│  sprites to  │ │ velocity  │ │ bounce    │
│  framebuffer │ │ to pos    │ │ detection │
└──────┬───────┘ └─────┬────┘ └─────┬────┘
       │               │            │
       └───────────────┴────────────┘
                       │
                       ▼
            ┌─────────────────────┐
            │    GameContext_t     │
            │ (src/util/)         │
            │ getEntities()       │
            │ getPhysicsComponent()│
            └──────────┬──────────┘
                       │
                       ▼
            ┌─────────────────────┐
            │   EntityManager_t   │
            │ (src/man/)          │
            │ Entity pool +       │
            │ ComponentStorage_t  │
            └──────────┬──────────┘
                       │
            ┌──────────┴──────────┐
            ▼                    ▼
    ┌──────────────┐   ┌────────────────┐
    │   Entity_t   │   │PhysicsComponent│
    │ (src/cmp/)   │   │  (src/cmp/)    │
    │ w,h,sprite   │   │ x,y,vx,vy     │
    │ x,y,vx,vy    │   └────────────────┘
    │ phy* ────────┼───►
    │ entityID     │
    └──────────────┘
```

## Key Design

- **Entity_t** holds visual data (sprite, dimensions) and a pointer to an optional `PhysicsComponent_t`.
- **PhysicsComponent_t** is stored separately in `ComponentStorage_t` for cache-friendly iteration by `PhysicsSystem_t`.
- **GameContext_t** is the abstract interface passed to all systems, providing both entity and component access.
- **EntityManager_t** implements `GameContext_t`, owning both the entity vector and the `ComponentStorage_t`.

## Namespace: `ECS`

### `Entity_t` (`src/cmp/entity.hpp`)
Visual component with position, velocity, dimensions, packed pixel sprite, physics pointer, and auto-incrementing entity ID. Two constructors: blank dimensions or PNG file loader.

### `PhysicsComponent_t` (`src/cmp/physics.hpp`)
Pure data: position and velocity. Stored in a separate vector for efficient system iteration.

### `ComponentStorage_t` (`src/man/componentstorage.hpp`)
RAII manager for physics component vectors. Non-copyable.

### `EntityManager_t` (`src/man/entitymanager.hpp`)
Implements `GameContext_t`. Owns `Vect_t<Entity_t>` and `ComponentStorage_t`. Creates entities with associated physics components.

### `GameContext_t` (`src/util/gamecontext.hpp`)
Abstract base: `getEntities()` and `getPhysicsComponent()` (const and mutable).

### `RenderSystem_t` (`src/sys/rendersystem.hpp`)
Opens a tinyPTC window, allocates a framebuffer, draws entity sprites at physics position.

### `PhysicsSystem_t` (`src/sys/physics.hpp`)
Updates `PhysicsComponent_t::x,y` by adding `vx,vy` each frame.

### `CollisionSystem_t` (`src/sys/collision.hpp`)
Checks screen boundaries (640x360) and reverses velocity on contact.

## Render Pipeline (per frame)

1. **Clear** — fill framebuffer with background colour `0x00999999`
2. **Draw** — for each entity with a physics component, blit sprite rows at `(phy->x, phy->y)`
3. **Present** — `ptc_update()` pushes framebuffer to the X11 window
4. **Poll** — `ptc_process_events()` returns 0 on window close

## Build System

`Makefile` with `COMPILE`/`C2O`/`C2H` macros. Recursively finds all `.cpp`/`.c` under `src/`. Links `libtinyptc.a` and `libpicopng.a` plus `libX11`/`libXext`.

## Dependency Graph

```
main.cpp
  ├── sys/rendersystem.hpp -> rendersystem.cpp
  │     ├── man/entitymanager.hpp -> entitymanager.cpp
  │     │     ├── man/componentstorage.hpp
  │     │     │     └── cmp/physics.hpp
  │     │     ├── util/typealiases.hpp
  │     │     └── util/gamecontext.hpp
  │     │           ├── cmp/entity.hpp
  │     │           │     ├── cmp/physics.hpp
  │     │           │     └── util/typealiases.hpp
  │     │           └── util/typealiases.hpp
  │     └── lib/tinyPTC/src/tinyptc.h (external)
  ├── sys/physics.hpp -> physics.cpp -> util/gamecontext.hpp
  ├── sys/collision.hpp -> collision.cpp -> util/gamecontext.hpp
  └── man/entitymanager.hpp
```

## Versioning

See [RULES.md](RULES.md).
