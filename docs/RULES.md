## Sincronización entre VERSION y tags de Git

**Propósito:** Garantizar que cada release esté correctamente etiquetado y que la versión del código coincida exactamente con la etiqueta del tag.

### Flujo correcto de trabajo

1. Editar el archivo `VERSION` en la raíz del repositorio con el nuevo número de versión (ej. `1.2.3`).
2. Hacer commit del cambio:
   ```
   git add VERSION
   git commit -m "release: bump version to 1.2.3"
   ```
3. Crear un tag **anotado** con el mismo valor (el tag debe incluir el prefijo `v`):
   ```
   git tag -a v1.2.3 -m "Release v1.2.3"
   ```
4. Hacer push del commit y del tag juntos:
   ```
   git push origin main --follow-tags
   ```
   O explícitamente:
   ```
   git push origin main v1.2.3
   ```

### Regla

El nombre del tag **debe coincidir exactamente** con el contenido del archivo `VERSION` en el commit al que apunta el tag. La convención es:
- El archivo `VERSION` contiene solo el número (ej. `1.2.3`), sin prefijo `v`.
- El tag se nombra con el prefijo `v` seguido del número (ej. `v1.2.3`).
- La coincidencia se verifica ignorando el prefijo `v` del tag: el tag `v1.2.3` debe corresponder a un `VERSION` con contenido `1.2.3`.

### Ejemplo de éxito

```
VERSION → "1.2.3"
Tag     → v1.2.3
✓ Coinciden → push aceptado
```

### Ejemplos de fallo

| Tag       | Contenido de VERSION | Resultado |
|-----------|----------------------|-----------|
| `v1.2.3`  | `1.2.4`              | ❌ Rechazado |
| `v1.2.3`  | `v1.2.3`             | ❌ Rechazado (VERSION no debe incluir `v`) |
| `v1.2.3`  | `1.2.3 `             | ❌ Rechazado (espacio extra en VERSION) |
| `1.2.3`   | `1.2.3`              | ❌ Rechazado (tag sin prefijo `v`) |

### Script de validación

Usar este script en hooks de **pre-push** (lado servidor) o en CI/CD para validar la regla:

```bash
#!/bin/bash
# validate-version-tag.sh
# Uso: validate-version-tag.sh <tag_name>
# Ejemplo: validate-version-tag.sh v1.2.3

set -euo pipefail

TAG="$1"

# Validar que el tag comience con 'v'
if [[ ! "$TAG" =~ ^v ]]; then
  echo "ERROR: El tag '$TAG' debe comenzar con 'v' (ej. v1.2.3)"
  exit 1
fi

# Obtener el commit al que apunta el tag
COMMIT=$(git rev-list -n 1 "$TAG" 2>/dev/null) || {
  echo "ERROR: El tag '$TAG' no existe"
  exit 1
}

# Obtener el contenido del archivo VERSION en ese commit
VERSION_CONTENT=$(git show "$COMMIT":VERSION 2>/dev/null | tr -d '[:space:]') || {
  echo "ERROR: No se encontró el archivo VERSION en el commit $COMMIT"
  exit 1
}

# Obtener el nombre del tag sin el prefijo 'v'
TAG_VERSION="${TAG#v}"

# Comparar
if [ "$TAG_VERSION" != "$VERSION_CONTENT" ]; then
  echo "ERROR: El tag '$TAG' no coincide con el archivo VERSION."
  echo "  Tag (sin v):  $TAG_VERSION"
  echo "  VERSION:      $VERSION_CONTENT"
  exit 1
fi

echo "OK: Tag '$TAG' coincide con VERSION ('$VERSION_CONTENT')"
```

**Hook del lado servidor (pre-receive):** Para usarlo como hook de servidor que rechaza el push si algún tag no cumple la regla:

```bash
#!/bin/bash
# hooks/pre-receive
# Validar que todos los tags nuevos cumplan la sincronización con VERSION

set -euo pipefail

while read oldrev newrev refname; do
  if [[ "$refname" =~ ^refs/tags/ ]]; then
    TAG="${refname#refs/tags/}"
    # Omitir si es un delete
    [ "$newrev" = "0000000000000000000000000000000000000000" ] && continue

    # Saltarse validación si se está creando el tag contra el commit actual
    # (sirve para pushes que incluyen tanto el commit como el tag)
    TAG_COMMIT=$(git rev-parse "$newrev"^{commit} 2>/dev/null)
    VERSION_CONTENT=$(git show "$TAG_COMMIT":VERSION 2>/dev/null | tr -d '[:space:]') || {
      echo "ERROR [$TAG]: No se encontró VERSION en el commit $TAG_COMMIT"
      exit 1
    }
    TAG_VERSION="${TAG#v}"

    if [ "$TAG_VERSION" != "$VERSION_CONTENT" ]; then
      echo "ERROR [$TAG]: Tag '$TAG' no coincide con VERSION ('$VERSION_CONTENT')"
      exit 1
    fi

    echo "OK [$TAG]: Tag sincronizado con VERSION"
  fi
done
```

### Advertencia

No seguir esta regla puede causar:
- **Despliegues erróneos:** El sistema de CI/CD puede empaquetar una versión incorrecta o sobrescribir un release existente.
- **Confusión en el versionado:** No se podrá determinar con certeza qué versión del código corresponde a un tag dado, dificultando debugging y auditorías.
- **Rotura de herramientas automáticas:** Gestores de paquetes, generadores de changelog y scripts de release que dependen de esta coincidencia pueden fallar o producir artefactos inconsistentes.
- **Rechazo en producción:** Si el servidor o el hook de pre-push aplica esta validación, el push será rechazado y habrá que corregir el tag manualmente, lo cual requiere `git tag -d` y `git push --delete origin <tag>`, operaciones que deberían evitarse en repositorios compartidos.
