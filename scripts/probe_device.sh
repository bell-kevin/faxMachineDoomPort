#!/usr/bin/env bash
set -euo pipefail

echo "== Basic system =="
uname -a || true
cat /etc/os-release 2>/dev/null || true

echo "== CPU and ABI =="
cat /proc/cpuinfo 2>/dev/null | sed -n '1,40p' || true
getconf LONG_BIT 2>/dev/null || true
file /bin/busybox 2>/dev/null || true
readelf -h /bin/busybox 2>/dev/null | sed -n '1,30p' || true

echo "== libc and loader =="
ldd --version 2>/dev/null | head -n 1 || true
strings /lib/libc.so.6 2>/dev/null | rg -m 1 'GNU C Library|musl' || true
ls -l /lib/ld-* /lib/*ld*.so* 2>/dev/null || true

echo "== Memory and storage =="
cat /proc/meminfo | sed -n '1,10p' || true
df -h || true

echo "== Graphics and framebuffer =="
ls -l /dev/fb* 2>/dev/null || true
ls -l /sys/class/graphics 2>/dev/null || true
for fb in /sys/class/graphics/fb*; do
  [ -e "$fb" ] || continue
  echo "-- $fb --"
  cat "$fb/name" 2>/dev/null || true
  cat "$fb/virtual_size" 2>/dev/null || true
  cat "$fb/bits_per_pixel" 2>/dev/null || true
done
ls -l /dev/dri 2>/dev/null || true

echo "== Input devices =="
ls -l /dev/input/event* 2>/dev/null || true
cat /proc/bus/input/devices 2>/dev/null | sed -n '1,120p' || true

echo "== Printer and spool interfaces =="
ls -l /dev/usb/lp* /dev/lp* 2>/dev/null || true
which lp 2>/dev/null || true
lpstat -p 2>/dev/null || true

echo "== Network and serial =="
ip a 2>/dev/null || ifconfig 2>/dev/null || true
ls -l /dev/ttyS* /dev/ttyAMA* /dev/ttyUSB* 2>/dev/null || true
