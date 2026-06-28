# Retroman

Retro arcade game engine in C++ using tinyPTC over X11 on Linux.

## Requirements

- `g++` with C++17 support
- X11 development libraries (`libx11-dev`, `libxext-dev`)
- tinyPTC (static library in `lib/tinyPTC/libtinyptc.a`)

## Build

```bash
make            # release build (O3)
make DEBUG=1    # debug build (g)
make clean      # remove objects
make cleanall   # remove objects and binary
```

## Structure

```
├── src/
│   ├── main.cpp              # Entry point
│   ├── main.hpp              # Application header
│   ├── sys/
│   │   ├── render.hpp        # RenderSystem (ECS)
│   │   └── render.cpp
│   └── tinyPTC/              # tinyPTC display backends
├── man/
│   ├── entitymanager.hpp     # EntityManager (ECS)
│   └── entitymanager.cpp
├── lib/tinyPTC/              # Precompiled static library
├── docs/RULES.md             # Versioning rules
├── VERSION                   # Current version
└── Makefile                  # Build system
```

## Architecture

- **ECS::RenderSystem_t** - Manages tinyPTC window and framebuffer rendering
- **ECS::EntityManager_t** - Entity lifecycle and sprite management

## Versioning

Version is defined in `VERSION` and mirrored as Git tags with `v` prefix (e.g. `v2.1.0`). See `docs/RULES.md`.

## License

Practice project. tinyPTC is licensed under GPLv2.
