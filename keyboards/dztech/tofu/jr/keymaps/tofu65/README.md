# Tofu65 QMK Keymap

Custom keymap for DZTech Tofu Jr (RP2040) with tap dance, combos, and custom keycodes.

## Compilation Steps

If you encounter submodule issues (missing ChibiOS files), run this first:
```bash
# Be in root of repo
make git-submodule
```

Then compile:
```bash
qmk compile -kb dztech/tofu/jr -km tofu65
```

Or flash directly:
```bash
qmk flash -kb dztech/tofu/jr -km tofu65
```

## Flashing (RP2040)

1. Put keyboard in bootloader mode: **FN + the top-right corner key**
   (base-layer `KC_HOME`, layout index 14 - the key immediately RIGHT of
   Backspace). Note this is NOT the grave/tilde key: tilde is `TD(TD_TILD)`
   on the Backspace key itself (index 13), one position to the left.
   FN is the bottom-row key between Right Alt and Right Ctrl.
2. Keyboard appears as USB drive
3. Copy the generated `.uf2` file to the drive
4. Keyboard automatically reboots with new firmware

# Updating fork

Last done 2025-09-10 so that QMK’s changelog for 2025-05-25 lists: “Fix OS_DETECTION_KEYBOARD_RESET (#25015).” was added