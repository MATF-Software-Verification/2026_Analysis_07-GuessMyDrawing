#!/usr/bin/env bash




SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

MASTER_DIR="${1:-$(dirname "$SCRIPT_DIR")/07-GuessMyDrawing-master}"
PROJECT_DIR="${MASTER_DIR}/07-GuessMyDrawing"
RESULTS_DIR="${SCRIPT_DIR}/results"
DOXYFILE="${SCRIPT_DIR}/Doxyfile"

if [ ! -d "$PROJECT_DIR" ]; then
  echo "Greška: nije pronađen projekat: $PROJECT_DIR"
  exit 1
fi

if ! command -v doxygen >/dev/null 2>&1; then
  echo "Greška: doxygen nije instaliran. (sudo apt install doxygen)"
  exit 1
fi

echo "Doxygen – dokumentacija za: $PROJECT_DIR"
echo "Izlaz: $RESULTS_DIR"
echo ""

# Generišemo Doxyfile
cat > "$DOXYFILE" << EOF
PROJECT_NAME          = "GuessMyDrawing"
PROJECT_NUMBER        = "1.0"
INPUT                 = "$PROJECT_DIR"
RECURSIVE             = YES
FILE_PATTERNS         = *.cpp *.h *.hpp *.c
OUTPUT_DIRECTORY      = "$RESULTS_DIR"
GENERATE_HTML         = YES
GENERATE_LATEX        = NO
EXTRACT_ALL           = YES
EXTRACT_PRIVATE       = NO
EXTRACT_STATIC        = YES
SOURCE_BROWSER        = YES
INLINE_SOURCES        = NO
REFERENCED_BY_RELATION = YES
REFERENCES_RELATION   = YES
QUIET                 = NO
WARNINGS              = YES
HAVE_DOT              = YES
CALL_GRAPH            = YES
CALLER_GRAPH          = YES
CLASS_DIAGRAMS        = YES
EOF

doxygen "$DOXYFILE"

echo ""
echo "Dokumentacija: $RESULTS_DIR/html/index.html"
