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
┌──────────────────┐  ┌────────────────────────┐
│  EntityManager   │  │     RenderSystem       │
│  (src/man/)      │  │  (src/sys/render.)     │
│                  │  │                        │
│  Manages Entity  │  │  Owns framebuffer      │
│  lifecycle       │  │  Renders sprites via   │
│  Stores all      │  │  tinyPTC (X11)         │
│  entities in     │  │                        │
│  vector          │  │  update():             │
│                  │  │    fill bg →           │
│                  │  │    drawAllEntities →   │
│                  │  │    ptc_update →        │
│                  │  │    ptc_process_events  │
└──────────────────┘  └────────────────────────┘
           │                   │
           └───────────────────┘
                   │
                   ▼
┌──────────────────────────────────────────────┐
│              Entity_t (Component)             │
│  src/man/entity.hpp                           │
│                                               │
│  Position (x,y), dimensions (w,h),            │
│  pixel sprite (vector<uint32_t>)              │
└──────────────────────────────────────────────┘
```

## Namespace: `ECS`

All engine types live in the `ECS` namespace.

### `Entity_t` (`src/man/entity.hpp`)

Data component with:
- `x`, `y` — screen position
- `w`, `h` — dimensions
- `sprite` — `std::vector<uint32_t>` of RGBA pixel data

### `EntityManager_t` (`src/man/entitymanager.hpp`)

Manages the entity pool:
- `createEntity(...)` — allocates a new entity (WIP)
- `getEntities()` — returns const ref to entity vector
- Pre-allocates space for `kNUMINITIALENTITIES` (1000)

### `RenderSystem_t` (`src/sys/render.hpp`)

Rendering system:
- Owns the framebuffer (`unique_ptr<uint32_t[]>`)
- References `EntityManager_t` for entity data
- `update()` — per-frame: clear → draw → present → poll events
- `drawAllEntities()` — iterates entities and calls `drawEntity()`
- `drawEntity()` — copies sprite rows to framebuffer at entity position

## Render Pipeline (per frame)

1. **Clear** — fill entire framebuffer with background color (`0x0000FFF0`)
2. **Draw** — for each entity, blit its sprite to the correct screen position
3. **Present** — call `ptc_update()` to push framebuffer to the X11 window
4. **Poll** — `ptc_process_events()` checks for window close; returns false to exit

## Include Convention

All includes use **relative quoted paths**:

| Source file | Include path |
|-------------|-------------|
| `src/main.cpp` | `"sys/render.hpp"`, `"man/entitymanager.hpp"` |
| `src/sys/render.cpp` | `"../sys/render.hpp"`, `"../man/entitymanager.hpp"` |
| `src/sys/render.cpp` (tinyPTC) | `"../../lib/tinyPTC/src/tinyptc.h"` |

## Build System

The `Makefile` uses custom macros (`COMPILE`, `C2O`, `C2H`) for build rules:
- Recursively finds all `.cpp`/`.c` sources under `src/`
- Generates object files into `obj/` mirroring the `src/` directory tree
- Links against `lib/tinyPTC/libtinyptc.a`, `libX11`, `libXext`

## Dependency Graph

```
main.cpp
  ├── sys/render.hpp → sys/render.cpp
  │     ├── man/entitymanager.hpp → man/entitymanager.cpp
  │     │     └── man/entity.hpp → man/entity.cpp
  │     └── lib/tinyPTC/src/tinyptc.h (external)
  └── man/entitymanager.hpp
        └── man/entity.hpp
```

## Versioning

See [RULES.md](RULES.md). Version is stored in `VERSION` and tagged as `v<VERSION>`.
