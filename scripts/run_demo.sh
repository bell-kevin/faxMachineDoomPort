#!/usr/bin/env bash
set -euo pipefail

MODE="${1:-stream}"

case "$MODE" in
  fb)
    exec ./build/first_light_fb
    ;;
  printer)
    OUT="${2:-/tmp/fax_printer_test.pbm}"
    exec ./build/first_light_printer "$OUT"
    ;;
  stream)
    FRAMES="${2:-4}"
    exec ./build/first_light_stream --frames "$FRAMES"
    ;;
  *)
    echo "Usage: $0 [fb|printer|stream]"
    exit 1
    ;;
esac
