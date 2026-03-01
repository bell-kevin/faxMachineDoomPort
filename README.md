# faxMachineDoomPort

Minimal, reproducible scaffold to port a Doom engine (preferably DoomGeneric) onto a fax machine class embedded target.

This repository is intentionally BYOS (bring your own source): you vendor Doom source into `third_party/doomgeneric` and build it against the platform layer in `platform/fax`.

## What you get
- Step-by-step porting plan with success criteria: `docs/PORTING_PLAN.md`
- Device probing checklist and parsing guidance: `docs/DEVICE_PROBING_CHECKLIST.md`
- Doom integration guide and low-memory build options: `docs/DOOM_INTEGRATION.md`
- Cross-toolchain bootstrap scripts: `toolchain/`
- Platform scaffold (video/input/timing/logging): `platform/fax/`
- First-light output tests (framebuffer, printer raster, stream): `tests/`
- Deployment/probing helpers: `scripts/`

## Build quick test binaries
```bash
make help
make all
```

## Run first-light locally
```bash
./build/first_light_stream --frames 10 > /tmp/frame.pbm
./build/first_light_printer /tmp/fax_test.pbm
```

> For `/dev/fb0` test on target: run as root and stop UI service first.
