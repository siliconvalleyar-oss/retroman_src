# Retroman

Retro arcade game engine in C++17 using tinyPTC over X11 on Linux.

## Requirements

- `g++` with C++17 support
- X11 development libraries (`libx11-dev`, `libxext-dev`)
- tinyPTC (static library in `lib/tinyPTC/libtinyptc.a`)

## Build

```bash
make              # release build (O3)
make DEBUG=1      # debug build (g)
make info         # show source/object paths
make libs         # build dependencies in lib/
make clean        # remove objects
make cleanall     # remove objects and binary
```

## Structure

```
├── src/
│   ├── main.cpp              # Entry point
│   ├── main.hpp              # Application header
│   ├── sys/
│   │   ├── render.hpp        # RenderSystem (ECS)
│   │   └── render.cpp
│   ├── man/
│   │   ├── entitymanager.hpp # EntityManager (ECS)
│   │   ├── entitymanager.cpp
│   │   ├── entity.hpp        # Entity_t component (ECS)
│   │   └── entity.cpp
│   └── tinyPTC/              # tinyPTC display backends (source)
├── lib/tinyPTC/              # Precompiled static library (libtinyptc.a)
├── docs/RULES.md             # Versioning rules
├── VERSION                   # Current version
├── Makefile                  # Build system
└── .mimocode/skills/retroman/ # Project skill for MiMoCode
```

## Architecture

- **ECS::RenderSystem_t** — Manages tinyPTC window, framebuffer rendering, and entity drawing
- **ECS::EntityManager_t** — Entity lifecycle, creation, and sprite/color management
- **ECS::Entity_t** — Individual entity component with position (x,y), dimensions (w,h), and pixel sprite

## Include Convention

Relative quoted includes, not angle-bracket system-style:
```cpp
#include "sys/render.hpp"
#include "man/entitymanager.hpp"
#include "man/entity.hpp"
```

## Versioning

Version is defined in `VERSION` and mirrored as Git tags with `v` prefix (e.g. `v2.4.0`). See `docs/RULES.md`.

## License

Practice project. tinyPTC is licensed under GPLv2.
