---
name: retroman
description: Use when working on the Retroman retro arcade game engine — building, releasing, editing ECS code, or managing the project
---

# Retroman Project Skill

Retro arcade game engine in C++17 using tinyPTC over X11 on Linux. ECS architecture with RenderSystem and EntityManager.

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
1. Edit `VERSION` (e.g. `2.4.0`)
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
#include "sys/render.hpp"
#include "man/entitymanager.hpp"
#include "man/entity.hpp"
#include "../lib/tinyPTC/src/tinyptc.h"

// From src/sys/render.cpp
#include "../sys/render.hpp"
#include "../man/entitymanager.hpp"
#include "../man/entity.hpp"
#include "../../lib/tinyPTC/src/tinyptc.h"
```

Do NOT use angle-bracket system-style includes (`<sys/render.hpp>`) — use relative quoted includes.

## Architecture

See [`docs/ARCHITECTURE.md`](../../docs/ARCHITECTURE.md) for full documentation.

| Component | File | Description |
|-----------|------|-------------|
| `ECS::RenderSystem_t` | `src/sys/render.hpp` | tinyPTC window, framebuffer, entity drawing |
| `ECS::EntityManager_t` | `src/man/entitymanager.hpp` | Entity lifecycle, creation, sprite/color |
| `ECS::Entity_t` | `src/man/entity.hpp` | Position (x,y), dimensions (w,h), pixel sprite |

## Key Files

- `Makefile` — Build system with COMPILE/C2O/C2H macros, DEBUG mode
- `docs/RULES.md` — Versioning rules and validation scripts
- `docs/ARCHITECTURE.md` — Full architecture documentation
- `docs/API.md` — Complete API reference
- `VERSION` — Current version number (no `v` prefix)
- `src/tinyPTC/` — tinyPTC display backends (xlib, xshm, xdbe)
- `lib/tinyPTC/libtinyptc.a` — Precompiled static library

## Dependencies

- `g++` with C++17
- `libx11-dev`, `libxext-dev`
- tinyPTC static library

## .gitignore Notes

- `app` binary excluded
- `obj/`, `build/`, `bin/`, `lib/` excluded
- All `CMakeLists.txt` excluded (unrelated WIP from other projects)
