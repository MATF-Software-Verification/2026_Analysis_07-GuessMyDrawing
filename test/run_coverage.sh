#!/bin/bash
# Pokrivenost koda: build u test/build, pokretanje testova, lcov + genhtml.
# Pokreni iz vs/test/:  ./run_coverage.sh
set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build"

echo "=== Build sa pokrivenošću (test/build) ==="
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake -DCOVERAGE=ON ..
make -j$(nproc 2>/dev/null || echo 2)

echo ""
echo "=== Pokretanje testova ==="
./bin/seminar_tests "[seminar]"

echo ""
echo "=== Izveštaj (lcov) ==="
if ! command -v lcov &>/dev/null; then
  echo "Nema lcov. Instaliraj: sudo apt install lcov"
  exit 1
fi
lcov -c -d . -o coverage.info --ignore-errors source,gcov
lcov --remove coverage.info '/usr/*' '*/test/*' -o coverage.info --ignore-errors unused
genhtml coverage.info -o coverage_html

COVERAGE_HTML="$(pwd)/coverage_html/index.html"
if [[ ! -f "$COVERAGE_HTML" ]]; then
  echo "Greška: genhtml nije kreirao coverage_html/index.html"
  exit 1
fi
echo ""
echo "Gotovo. Izveštaj je u folderu:"
echo "  $(pwd)/coverage_html/"
echo "Otvori u browseru (kopiraj celu putanju):"
echo "  file://${COVERAGE_HTML}"
