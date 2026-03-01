# Fax Doom Porting Plan (Execution Phases + Success Criteria)

## Phase 0 — Identify device architecture/OS
1. Run `scripts/probe_device.sh` on target shell.
2. Record CPU ISA, endianness, ABI, libc, kernel version.
3. Confirm writable path (`/tmp` or persistent partition).

**Success criteria**
- Architecture identified (ARMv7/MIPS32/etc).
- Linux vs RTOS classified.
- Output/input interfaces enumerated.

## Phase 1 — Toolchain setup
1. On host, run `toolchain/install_toolchains.sh` or use `toolchain/Dockerfile`.
2. Select profile: `toolchain/env-armv7.mk` or `toolchain/env-mips32.mk`.
3. Cross-build first-light test binaries.

**Success criteria**
- `file build/first_light_*` matches target arch.
- Binaries run on target (or under qemu-user for smoke checks).

## Phase 2 — Bring-up output path
1. Test A: framebuffer (`build/first_light_fb`) if `/dev/fb0` exists.
2. Test B: printer raster (`build/first_light_printer`) and submit PBM to print path.
3. Test C: stream PBM over SSH/serial when no direct display.

**Success criteria**
- At least one output path produces recognizable checker/pattern frames.

## Phase 3 — Bring-up input path
1. Enumerate `/dev/input/event*` and map front panel keys.
2. If no evdev, map GPIO sysfs/chardev reads.
3. Validate `input_poll()` reports directional + action keys.

**Success criteria**
- At least 5 actions (up/down/left/right/fire/use) reliably detected.

## Phase 4 — Integrate Doom engine + render loop
1. Vendor DoomGeneric source into `third_party/doomgeneric`.
2. Implement `doomgeneric_fax.c` platform bindings to `platform/fax` API.
3. Run IWAD from `/opt/faxdoom/doom1.wad` or `/tmp/doom1.wad`.

**Success criteria**
- Game reaches menu and starts E1M1.
- Stable control loop without watchdog reset.

## Phase 5 — Optimization + packaging
1. Disable sound/music/network features.
2. Reduce render resolution and scale output.
3. Strip binaries and package as tarball/init script or firmware payload.

**Success criteria**
- Stable framerate target reached (>=10 FPS minimal; >=20 FPS preferred).
- Reproducible build command and deploy script documented.

---

## Decision Tree (recommended approach)

- **If embedded Linux present:**
  - Cross-compile with glibc/musl-compatible toolchain.
  - Deploy with `scp` + `ssh`.
  - Use `/dev/fb0` or `/dev/input/event*` first.
- **If bare metal / RTOS:**
  - Use newlib + board SDK.
  - Start with serial PBM output and GPIO input.
  - Port timing and framebuffer/printer drivers directly.
- **If no usable display:**
  - Use printer raster pipeline (PBM -> print driver).
  - Or stream PBM frames over serial/SSH for remote visualization.
