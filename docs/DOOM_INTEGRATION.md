# Minimal Doom Integration Plan

## Engine choice
Use **DoomGeneric** first for fastest platform adaptation and smallest code surface.

## Vendor source (BYOS)
```bash
mkdir -p third_party
cd third_party
git clone https://github.com/ozkl/doomgeneric.git
cd ..
```

If licensing policy requires, keep this repo source-free and apply local patches from `third_party/patches`.

## IWAD placement
Recommended runtime search order:
1. `/opt/faxdoom/doom1.wad`
2. `/tmp/doom1.wad`
3. `./doom1.wad`

## Compile options to reduce memory/CPU
- `-Os -ffunction-sections -fdata-sections -Wl,--gc-sections`
- Disable sound/music modules in Doom source config.
- Use fixed-point path where selectable.
- Start with low internal resolution (e.g., 160x100 or 200x120) and scale.

## Platform glue tasks
1. Add `third_party/doomgeneric/doomgeneric/doomgeneric_fax.c`.
2. Map required DG functions to `platform/fax`:
   - `DG_Init` -> `video_init`
   - `DG_DrawFrame` -> `video_present`
   - `DG_SleepMs` -> `timing_sleep_ms`
   - `DG_GetTicksMs` -> `time_now_ms`
   - `DG_GetKey` -> `input_poll`
3. Build target binary `faxdoom` with selected output backend.

## Integration milestone checks
- Launch binary with IWAD path argument.
- Reach title/menu.
- Enter level, move, fire, open menu.
- Measure frame pacing and watchdog safety.
