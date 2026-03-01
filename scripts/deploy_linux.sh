#!/usr/bin/env bash
set -euo pipefail

if [ $# -lt 2 ]; then
  echo "Usage: $0 <user@target-ip> <binary> [remote-dir]"
  exit 1
fi

TARGET="$1"
BINARY="$2"
REMOTE_DIR="${3:-/tmp/faxdoom}"

ssh "$TARGET" "mkdir -p '$REMOTE_DIR'"
scp "$BINARY" "$TARGET:$REMOTE_DIR/"
ssh "$TARGET" "chmod +x '$REMOTE_DIR/$(basename "$BINARY")'"

echo "Deployed $(basename "$BINARY") to $TARGET:$REMOTE_DIR"
