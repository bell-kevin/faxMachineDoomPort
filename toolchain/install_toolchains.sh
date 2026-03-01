#!/usr/bin/env bash
set -euo pipefail

sudo apt-get update
sudo apt-get install -y \
  build-essential git make cmake pkg-config \
  gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf \
  gcc-mips-linux-gnu g++-mips-linux-gnu \
  qemu-user-static file binutils

echo "Installed ARMv7 and MIPS32 cross toolchains."
