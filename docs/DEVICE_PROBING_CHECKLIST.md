# Device Probing Checklist

Run on the fax target once shell access is available.

## 1) CPU architecture and ABI
```bash
uname -m
cat /proc/cpuinfo | sed -n '1,40p'
readelf -h /bin/busybox | sed -n '1,30p'
file /bin/busybox
```
Interpretation:
- `Machine: ARM` + `Class: ELF32` => ARM32 build (`arm-linux-gnueabihf-`).
- `Machine: MIPS` => MIPS toolchain (`mips-linux-gnu-`), check endianness in `readelf`.

## 2) OS, libc, kernel
```bash
uname -a
cat /etc/os-release
ldd --version | head -n1
strings /lib/libc.so.6 | rg -m 1 'GNU C Library|musl'
ls -l /lib/ld-* /lib/*ld*.so*
```
Interpretation:
- `GNU C Library` implies glibc-linked binaries are acceptable.
- `musl` implies prefer static/minimal dependencies.

## 3) RAM and storage budget
```bash
cat /proc/meminfo | sed -n '1,12p'
df -h
```
Interpretation:
- `MemTotal < 64MB` => aggressively lower resolution and disable all nonessential features.

## 4) Output interfaces
```bash
ls -l /dev/fb*
ls -l /sys/class/graphics
for fb in /sys/class/graphics/fb*; do cat "$fb/name" "$fb/virtual_size" "$fb/bits_per_pixel"; done
ls -l /dev/dri
ls -l /dev/usb/lp* /dev/lp*
```
Interpretation:
- `/dev/fb0` present => run framebuffer path first.
- Printer device nodes only => use raster print path.
- No display nodes => use stream fallback.

## 5) Input interfaces
```bash
ls -l /dev/input/event*
cat /proc/bus/input/devices | sed -n '1,160p'
```
Interpretation:
- `Handlers=eventX` for keypad/buttons => map keys in `input_poll()`.
- No evdev => inspect GPIO: `ls /sys/class/gpio` or `gpiodetect`.

## 6) Automated probe
```bash
scripts/probe_device.sh | tee /tmp/fax_probe.txt
```
Collect `/tmp/fax_probe.txt` for deterministic toolchain/profile selection.
