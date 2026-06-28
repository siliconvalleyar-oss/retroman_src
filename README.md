# Retroman

Retro arcade game engine in C++17 using tinyPTC over X11 on Linux.
ECS architecture with separate component storage.

## Requirements

- `g++` with C++17 support
- X11 development libraries (`libx11-dev`, `libxext-dev`)
- tinyPTC (`lib/tinyPTC/libtinyptc.a`)
- picoPNG (`lib/picoPNG/libpicopng.a`)

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
│   ├── main.hpp              # (reserved)
│   ├── cmp/
│   │   ├── entity.hpp        # Entity_t component
│   │   ├── entity.cpp
│   │   └── physics.hpp       # PhysicsComponent_t
│   ├── sys/
│   │   ├── rendersystem.hpp  # RenderSystem_t
│   │   ├── rendersystem.cpp
│   │   ├── physics.hpp       # PhysicsSystem_t
│   │   ├── physics.cpp
│   │   ├── collision.hpp     # CollisionSystem_t
│   │   └── collision.cpp
│   ├── man/
│   │   ├── entitymanager.hpp # EntityManager_t
│   │   ├── entitymanager.cpp
│   │   ├── componentstorage.hpp # ComponentStorage_t
│   │   └── componentstorage.cpp
│   └── util/
│       ├── gamecontext.hpp   # GameContext_t abstract base
│       └── typealiases.hpp   # Vect_t, EntityID_t
├── lib/
│   ├── tinyPTC/              # tinyPTC static library
│   └── picoPNG/              # picoPNG static library
├── png/                      # Sprite assets (PNG/JPG)
├── assets/                   # Additional assets
├── docs/
│   ├── RULES.md              # Versioning rules
│   ├── ARCHITECTURE.md       # Architecture documentation
│   └── API.md                # API reference
├── scripts/
│   └── release.sh            # Automated release script
├── VERSION                   # Current version
├── Makefile                  # Build system
└── .mimocode/skills/retroman/ # Project skill
```

## Documentation

| File | Description |
|------|-------------|
| [`docs/ARCHITECTURE.md`](docs/ARCHITECTURE.md) | System architecture, pipeline, dependency graph |
| [`docs/API.md`](docs/API.md) | Complete API reference for all ECS types |
| [`docs/RULES.md`](docs/RULES.md) | Versioning rules and validation scripts |

## Include Convention

Relative quoted includes (see `docs/ARCHITECTURE.md`).

## Versioning

Version in `VERSION`, mirrored as `v<VERSION>` tags. See `docs/RULES.md`.

## License

Practice project. tinyPTC is GPLv2.
