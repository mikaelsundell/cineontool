#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

echo "Running clang-format in project root: $PROJECT_ROOT"

find "$PROJECT_ROOT" -name '*.cpp' -o -name '*.h' | xargs clang-format -i
echo "Clang-format completed."
