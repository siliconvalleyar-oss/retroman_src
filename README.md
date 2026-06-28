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
│   ├── cmp/
│   │   ├── entity.hpp        # Entity_t component
│   │   └── entity.cpp
│   ├── sys/
│   │   ├── rendersystem.hpp  # RenderSystem (ECS)
│   │   └── rendersystem.cpp
│   ├── man/
│   │   ├── entitymanager.hpp # EntityManager (ECS)
│   │   ├── entitymanager.cpp
│   │   ├── entity.hpp        # (legacy)
│   │   └── entity.cpp        # (legacy)
│   └── util/
│       ├── gamecontext.hpp   # GameContext_t abstract base
│       └── typealiases.hpp   # VecEntities_t alias
│   ├── man/
│   │   ├── entitymanager.hpp # EntityManager (ECS)
│   │   ├── entitymanager.cpp
│   │   ├── entity.hpp        # Entity_t component (ECS)
│   │   └── entity.cpp
│   └── tinyPTC/              # tinyPTC display backends (source)
├── lib/tinyPTC/              # Precompiled static library (libtinyptc.a)
├── docs/
│   ├── RULES.md              # Versioning rules
│   ├── ARCHITECTURE.md       # Full architecture documentation
│   └── API.md                # Complete API reference
├── VERSION                   # Current version
├── Makefile                  # Build system
└── .mimocode/skills/retroman/ # Project skill for MiMoCode
```

## Documentation

| File | Description |
|------|-------------|
| [`docs/ARCHITECTURE.md`](docs/ARCHITECTURE.md) | System architecture, pipeline, dependency graph |
| [`docs/API.md`](docs/API.md) | Complete API reference for all ECS types |
| [`docs/RULES.md`](docs/RULES.md) | Versioning rules and validation scripts |

## Include Convention

Relative quoted includes, not angle-bracket system-style. See [`docs/ARCHITECTURE.md`](docs/ARCHITECTURE.md#include-convention).

## Versioning

Version is defined in `VERSION` and mirrored as Git tags with `v` prefix (e.g. `v2.4.0`). See [`docs/RULES.md`](docs/RULES.md).

## License

Practice project. tinyPTC is licensed under GPLv2.
