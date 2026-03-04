#!/usr/bin/env bash

# Clang-tidy – stilske provere i statička analiza za GuessMyDrawing.
# Upotreba: ./run_clang_tidy.sh [putanja_do_07-GuessMyDrawing-master]

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

# Projekat (podrazumevano: master folder je pored foldera gde je skripta)
MASTER_DIR="${1:-$(dirname "$SCRIPT_DIR")/07-GuessMyDrawing-master}"
SUBMODULE_DIR="${MASTER_DIR}/07-GuessMyDrawing"

RESULTS_DIR="./results"
OUTPUT_FILE="${RESULTS_DIR}/clang_tidy_report.txt"

mkdir -p "$RESULTS_DIR"
rm -f "$OUTPUT_FILE"

# Grupe provera (bez bugprone-implicit-widening – izaziva crash na Qt/headerima)
CHECKS='clang-diagnostic-*,clang-analyzer-*,modernize-*,performance-*,readability-*,bugprone-*,-bugprone-implicit-widening-of-multiplication-result,cppcoreguidelines-*'
# Samo projekat: prikazuj upozorenja iz Application/, Server/ i zajedničkih header-a (ne iz Qt/sistema)
HEADER_FILTER='.*(Application|Server|MessageType|MessageReceivedEnum|ServerMessageEnum).*'

# Qt5 include paths (Ubuntu/Debian)
QT_INC='/usr/include/x86_64-linux-gnu/qt5'

echo "Clang-tidy analiza: $SUBMODULE_DIR"

if ! command -v clang-tidy >/dev/null 2>&1; then
  echo "Greška: clang-tidy nije instaliran. (sudo apt install clang-tidy)"
  exit 1
fi

# Uključi build/ da clang-tidy nađe Qt generisane headere (ui_*.h)
BUILD_APP="${SUBMODULE_DIR}/build/Application"
BUILD_SRV="${SUBMODULE_DIR}/build/Server"

find "$SUBMODULE_DIR" -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" -o -name "*.cc" \) \
  ! -path "*/build/*" \
| while read -r file; do
    echo "[Processing] $file"
    EXTRA=""
    case "$file" in *.h|*.hpp) EXTRA="-x c++-header" ;; esac
    clang-tidy "$file" \
      -checks="$CHECKS" \
      -header-filter="$HEADER_FILTER" \
      -- \
      $EXTRA -std=c++17 \
      -I"$SUBMODULE_DIR/Application" \
      -I"$SUBMODULE_DIR/Server" \
      -I"$SUBMODULE_DIR" \
      -I"$BUILD_APP" \
      -I"$BUILD_SRV" \
      -I"$QT_INC" \
      -I"$QT_INC/QtCore" \
      -I"$QT_INC/QtGui" \
      -I"$QT_INC/QtWidgets" \
      -I"$QT_INC/QtNetwork" \
      >> "$OUTPUT_FILE" 2>&1
done

echo ""
echo "Izvestaj: $OUTPUT_FILE"
