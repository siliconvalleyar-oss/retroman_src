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
│   └── tinyPTC/              # tinyPTC display backends (source)
├── man/
│   ├── entitymanager.hpp     # EntityManager + Entity (ECS)
│   └── entitymanager.cpp
├── lib/tinyPTC/              # Precompiled static library (libtinyptc.a)
├── docs/RULES.md             # Versioning rules
├── VERSION                   # Current version
├── Makefile                  # Build system
└── .mimocode/skills/retroman/ # Project skill for MiMoCode
```

## Architecture

- **ECS::RenderSystem_t** — Manages tinyPTC window, framebuffer rendering, and entity drawing
- **ECS::EntityManager_t** — Entity lifecycle, creation, and sprite/color management
- **ECS::Entity_t** — Individual entity with position (x,y), dimensions (w,h), and pixel sprite

## Versioning

Version is defined in `VERSION` and mirrored as Git tags with `v` prefix (e.g. `v2.3.0`). See `docs/RULES.md`.

## License

Practice project. tinyPTC is licensed under GPLv2.
