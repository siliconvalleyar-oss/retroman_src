# Retroman

Proyecto de práctica en C++ con gráficos utilizando la librería tinyPTC sobre X11 en Linux.

## Requisitos

- Compilador `g++`
- Librerías de desarrollo de X11 (`libx11-dev`, `libxext-dev`)
- tinyPTC (incluido como `libtinyptc.a` y código fuente en `src/tinyPTC/`)

## Compilación

```bash
make
```

Esto genera el binario `app` en la raíz del proyecto.

## Estructura

```
├── src/
│   ├── main.cpp           # Punto de entrada
│   └── tinyPTC/           # Librería tinyPTC (targets: xdbe, xlib, xshm, xvshm)
├── obj/                   # Objetos compilados
├── docs/RULES.md          # Reglas del proyecto
├── VERSION                # Versión actual
├── Makefile               # Build system
└── libtinyptc.a           # Librería precompilada
```

## Versionado

La versión se define en `VERSION` y se refleja en los tags de Git con prefijo `v` (ej. `v1.0.1`). Ver `docs/RULES.md` para la regla de sincronización.

## Licencia

Código de práctica. tinyPTC está licenciado bajo GPLv2 (ver cabeceras en `src/tinyPTC/`).


