---
name: retroman
description: Use when working on the Retroman retro arcade game engine — building, releasing, editing ECS code, or managing the project
---

# Retroman Project Skill

Retro arcade game engine in C++17 using tinyPTC over X11 on Linux. ECS architecture with RenderSystem, PhysicsSystem, CollisionSystem, and EntityManager.

## Project Root

```
/mnt/disk/src/OLDS_src/RETROMAN/retroman_vxx/old_version_app_game/retroman_src
```

## Build Commands

```bash
make              # release build (O3)
make DEBUG=1      # debug build (g)
make info         # show source/object paths
make libs         # build dependencies in lib/
make clean        # remove objects
make cleanall     # remove objects and binary
```

## Versioning Rule (CRITICAL)

The file `VERSION` must match the git tag exactly (tag has `v` prefix, VERSION does not).

**Release workflow:**
1. Edit `VERSION` (e.g. `2.5.0`)
2. Commit: `git add VERSION && git commit -m "release: bump version to X.Y.Z"`
3. Tag: `git tag -a vX.Y.Z -m "Release vX.Y.Z"`
4. Push: `git push origin main --follow-tags`

**Verification:**
```bash
git tag -l | sort -V | tail -1  # latest tag
cat VERSION                       # should match without 'v'
```

## Include Path Convention

This project uses **relative paths** for includes:

```cpp
// From src/main.cpp
#include "sys/rendersystem.hpp"
#include "sys/physics.hpp"
#include "sys/collision.hpp"
#include "man/entitymanager.hpp"
#include "util/gamecontext.hpp"
#include "../lib/tinyPTC/src/tinyptc.h"

// From src/sys/rendersystem.cpp
#include "rendersystem.hpp"
#include "../man/entitymanager.hpp"
#include "../../lib/tinyPTC/src/tinyptc.h"
```

Do NOT use angle-bracket system-style includes (`<sys/rendersystem.hpp>`) — use relative quoted includes.

## Architecture

See [`docs/ARCHITECTURE.md`](../../docs/ARCHITECTURE.md) for full documentation.

| Component | File | Description |
|-----------|------|-------------|
| `ECS::RenderSystem_t` | `src/sys/rendersystem.hpp` | tinyPTC window, framebuffer, entity drawing |
| `ECS::PhysicsSystem_t` | `src/sys/physics.hpp` | Velocity-based movement and bounce |
| `ECS::CollisionSystem_t` | `src/sys/collision.hpp` | Screen-edge collision detection |
| `ECS::EntityManager_t` | `src/man/entitymanager.hpp` | Entity lifecycle, storage, GameContext_t impl |
| `ECS::Entity_t` | `src/cmp/entity.hpp` | Position, velocity, dimensions, pixel sprite, physics pointer |
| `ECS::PhysicsComponent_t` | `src/cmp/physics.hpp` | Pure position/velocity data component |
| `ECS::ComponentStorage_t` | `src/man/componentstorage.hpp` | RAII component vector manager |

## Key Files

- `Makefile` — Build system with COMPILE/C2O/C2H macros, DEBUG mode
- `docs/RULES.md` — Versioning rules and validation scripts
- `docs/ARCHITECTURE.md` — Full architecture documentation
- `docs/API.md` — Complete API reference
- `VERSION` — Current version number (no `v` prefix)
- `lib/tinyPTC/libtinyptc.a` — Precompiled static library
- `lib/picoPNG/` — PNG decoding library

## Dependencies

- `g++` with C++17
- `libx11-dev`, `libxext-dev`
- tinyPTC static library

## .gitignore Notes

- `app` binary excluded
- `obj/`, `build/`, `bin/`, `lib/` excluded
- `*.old` backup files excluded
- All `CMakeLists.txt` excluded (unrelated WIP from other projects)
