#!/usr/bin/env bash
set -euo pipefail

# cppcheck – statička analiza (GuessMyDrawing). Kao kod koleginice: suppress Qt i sistem.
# Upotreba: ./run_cppcheck.sh [putanja_do_07-GuessMyDrawing-master]

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

MASTER_DIR="${1:-$(dirname "$SCRIPT_DIR")/07-GuessMyDrawing-master}"
SOURCE_DIR="${MASTER_DIR}/07-GuessMyDrawing"
TXT_FILE="${SCRIPT_DIR}/results/cppcheck_report.txt"

mkdir -p "$(dirname "$TXT_FILE")"
rm -f "$TXT_FILE"

if ! command -v cppcheck &>/dev/null; then
  echo "Greška: cppcheck nije instaliran. (sudo apt install cppcheck)"
  exit 1
fi

# --library=qt = ugrađene Qt definicije (bez -I za Qt), da cppcheck parsira naš kod i prijavi nalaze
CPPCHECK_ARGS=(
  -q
  --enable=all
  --inconclusive
  --std=c++17
  --force
  --library=qt
  -I"$SOURCE_DIR/Application"
  -I"$SOURCE_DIR/Server"
  -I"$SOURCE_DIR"
  -I"$SOURCE_DIR/build/Application"
  -I"$SOURCE_DIR/build/Server"
  -D__linux__
  -DQ_OS_LINUX
  --suppress=missingIncludeSystem
  --suppress=preprocessorErrorDirective
  --suppress='*:*/Qt*/*'
  --suppress='*:*/usr/include/*'
  -i build
)

echo "Pokrećem cppcheck analizu nad $SOURCE_DIR ..."

{
  echo "=== cppcheck izveštaj: $SOURCE_DIR ==="
  echo ""
  cppcheck "${CPPCHECK_ARGS[@]}" "$SOURCE_DIR" 2>&1 || true
  echo ""
  echo "=== Kraj izveštaja ==="
} > "$TXT_FILE"

echo "Izveštaj: $TXT_FILE"
echo "Završeno."
