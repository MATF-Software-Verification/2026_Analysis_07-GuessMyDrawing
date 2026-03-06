#!/bin/bash
# Skripta: pokreće Server u pozadini, pa Application pod Valgrindom. Na kraju gasi Server.
# Prvo uradi Build u Qt Creatoru. Upotreba: ./run_valgrind.sh [putanja_do_07-GuessMyDrawing-master]

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

SRC_DIR="${1:-$(dirname "$SCRIPT_DIR")/07-GuessMyDrawing-master}"
PROJECT_DIR="${SRC_DIR}/07-GuessMyDrawing"
BUILD_DIR="${PROJECT_DIR}/build"
RESULTS_DIR="${SCRIPT_DIR}/results"
OUTPUT_FILE="valgrind_report.txt"

SERVER_PID=""
cleanup() {
    if [ -n "$SERVER_PID" ] && kill -0 "$SERVER_PID" 2>/dev/null; then
        echo "Gašenje Servera (PID $SERVER_PID)..."
        kill "$SERVER_PID" 2>/dev/null
    fi
}
trap cleanup EXIT

mkdir -p "$RESULTS_DIR"


APP_BIN="${BUILD_DIR}/Application/Application"
SERVER_BIN="${BUILD_DIR}/Server/Server"
if [ ! -f "$APP_BIN" ]; then
    APP_BIN=$(find "$BUILD_DIR" -maxdepth 3 -type f -executable -name 'Application' 2>/dev/null | head -1)
fi
if [ ! -f "$SERVER_BIN" ]; then
    SERVER_BIN=$(find "$BUILD_DIR" -maxdepth 3 -type f -executable -name 'Server' 2>/dev/null | head -1)
fi

if [ -z "$APP_BIN" ] || [ ! -f "$APP_BIN" ]; then
    echo "Greška: nije pronađen Application! Uradi Build u Qt Creatoru."
    exit 1
fi
if [ -z "$SERVER_BIN" ] || [ ! -f "$SERVER_BIN" ]; then
    echo "Greška: nije pronađen Server! Uradi Build u Qt Creatoru."
    exit 1
fi

"$SERVER_BIN" &
SERVER_PID=$!
sleep 2
if ! kill -0 "$SERVER_PID" 2>/dev/null; then
    echo "Greška: Server nije pokrenut."
    exit 1
fi
echo "Server pokrenut."
echo "Aplikacija se pokreće."
echo "Ugasite aplikaciju kad se klijent poveže."
echo ""

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --log-file="${RESULTS_DIR}/${OUTPUT_FILE}" \
         "$APP_BIN"

EXIT_CODE=$?
echo "Rezultati: ${RESULTS_DIR}/${OUTPUT_FILE}"
exit $EXIT_CODE
