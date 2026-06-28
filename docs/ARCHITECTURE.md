# Architecture

Retroman is a retro arcade game engine using an **Entity-Component-System (ECS)** architecture, rendered via **tinyPTC** over X11 on Linux.

## Overview

```
┌──────────────────────────────────────────────┐
│                   main.cpp                    │
│  Creates EntityManager + RenderSystem         │
│  Runs main loop: while(render.update())       │
└──────────┬───────────────────┬────────────────┘
           │                   │
           ▼                   ▼
┌──────────────────────────┐  ┌────────────────────────────┐
│     GameContext_t         │  │      RenderSystem          │
│  (src/util/gamecontext.)  │  │  (src/sys/rendersystem.)   │
│  Abstract base with       │  │                            │
│  virtual getEntities()    │  │  Owns framebuffer          │
└──────────┬────────────────┘  │  Renders sprites via       │
           │                   │  tinyPTC (X11)             │
           ▼                   │                            │
┌──────────────────────────┐   │  update(GameContext_t&):   │
│     EntityManager         │  │    fill bg →               │
│  (src/man/)               │  │    drawAllEntities(ctx) →  │
│  Inherits GameContext_t   │  │    ptc_update →            │
│  Manages Entity lifecycle │  │    ptc_process_events      │
│  Stores entities in vec   │  └────────────────────────────┘
└──────────────────────────┘              
           │                               
           ▼                               
┌──────────────────────────────────────────┐
│         Entity_t (Component)             │
│  src/cmp/entity.hpp                      │
│                                          │
│  Position (x,y), dimensions (w,h),       │
│  pixel sprite (vector<uint32_t>)         │
└──────────────────────────────────────────┘

## Namespace: `ECS`

All engine types live in the `ECS` namespace.

### `Entity_t` (`src/cmp/entity.hpp`)

Data component with:
- `x`, `y` — screen position
- `w`, `h` — dimensions
- `sprite` — `std::vector<uint32_t>` of RGBA pixel data

### `GameContext_t` (`src/util/gamecontext.hpp`)

Abstract base class providing a common interface for entity storage:
- `virtual getEntities()` — returns `const VecEntities_t&`

### `EntityManager_t` (`src/man/entitymanager.hpp`)

Manages the entity pool, inherits `GameContext_t`:
- `createEntity(...)` — allocates a new entity (WIP)
- `getEntities() override` — returns const ref to entity vector
- Pre-allocates space for `kNUMINITIALENTITIES` (1000)

### `RenderSystem_t` (`src/sys/rendersystem.hpp`)

Rendering system:
- Owns the framebuffer (`unique_ptr<uint32_t[]>`)
- Receives `GameContext_t&` per frame via `update()`
- `update(ctx)` — per-frame: clear → draw → present → poll events
- `drawAllEntities(entities)` — renders using lambdas

## Render Pipeline (per frame)

1. **Clear** — fill entire framebuffer with background color (`0x00999999`)
2. **Draw** — for each entity, blit its sprite to the correct screen position
3. **Present** — call `ptc_update()` to push framebuffer to the X11 window
4. **Poll** — `ptc_process_events()` checks for window close; returns false to exit

## Include Convention

All includes use **relative quoted paths**:

| Source file | Include path |
|-------------|-------------|
| `src/main.cpp` | `"sys/rendersystem.hpp"`, `"man/entitymanager.hpp"`, `"util/gamecontext.hpp"` |
| `src/sys/rendersystem.cpp` | `"rendersystem.hpp"`, `"../man/entitymanager.hpp"` |
| `src/man/entitymanager.hpp` | `"../util/typealiases.hpp"`, `"../util/gamecontext.hpp"` |
| `src/man/entitymanager.cpp` | `"../cmp/entity.hpp"` |
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
  └── man/entitymanager.hpp
  ├── util/gamecontext.hpp
  └── util/typealiases.hpp
```

## Versioning

See [RULES.md](RULES.md). Version is stored in `VERSION` and tagged as `v<VERSION>`.
