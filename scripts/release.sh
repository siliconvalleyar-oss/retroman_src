#!/bin/bash
set -euo pipefail

# ──────────────────────────────────────────────
# Retroman Release Script
# Usage: ./scripts/release.sh [commit_message]
#
# Auto-increments VERSION (0-9 rollover per segment),
# stages all changes, commits, tags, and pushes.
# ──────────────────────────────────────────────

VERSION_FILE="VERSION"

if [ ! -f "$VERSION_FILE" ]; then
    echo "ERROR: $VERSION_FILE not found"
    exit 1
fi

# ── Read & increment version with rollover ──
OLD_VER=$(cat "$VERSION_FILE" | tr -d '[:space:]')
IFS='.' read -r MAJOR MINOR PATCH <<< "$OLD_VER"

PATCH=$((PATCH + 1))
if [ "$PATCH" -ge 10 ]; then
    PATCH=0
    MINOR=$((MINOR + 1))
fi
if [ "$MINOR" -ge 10 ]; then
    MINOR=0
    MAJOR=$((MAJOR + 1))
fi

NEW_VER="${MAJOR}.${MINOR}.${PATCH}"
echo "→ $OLD_VER → $NEW_VER"

# ── Detect changes ──
if [ -z "$(git status --porcelain)" ]; then
    echo "No changes to commit."
    exit 0
fi

CHANGED=$(git diff --stat | tail -1 | awk '{print $1 " files changed"}')
echo "→ Changes detected: $CHANGED"

# ── Build commit message ──
if [ $# -ge 1 ]; then
    COMMIT_MSG="$*"
else
    # Auto-detect conventional commit type from changes
    if git diff --cached --name-only 2>/dev/null | grep -qE '^docs/|\.md$'; then
        PREFIX="docs:"
    elif git diff --cached --name-only 2>/dev/null | grep -qE '^src/cmp/'; then
        PREFIX="feat(cmp):"
    elif git diff --cached --name-only 2>/dev/null | grep -qE '^src/sys/'; then
        PREFIX="feat(sys):"
    elif git diff --cached --name-only 2>/dev/null | grep -qE '^src/man/'; then
        PREFIX="refactor(man):"
    elif git diff --cached --name-only 2>/dev/null | grep -qE '^src/util/'; then
        PREFIX="refactor(util):"
    elif git diff --cached --name-only 2>/dev/null | grep -qE '^Makefile|\.gitignore'; then
        PREFIX="chore:"
    else
        PREFIX="refactor:"
    fi
    COMMIT_MSG="$PREFIX bump version to $NEW_VER"
fi

# ── Write new version ──
echo "$NEW_VER" > "$VERSION_FILE"

# ── Stage, commit, tag, push ──
git add -A
git commit -m "$COMMIT_MSG"
git tag -a "v$NEW_VER" -m "v$NEW_VER"
git push origin main "v$NEW_VER"

echo "✓ Released v$NEW_VER"
