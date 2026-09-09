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

## The Hyper layer, and why Karabiner is also involved

This keymap is only half the story. The Hyper chords it emits are consumed on
the Mac by **Hammerspoon** (`~/.hammerspoon/`), and there are **two independent
ways** a Hyper chord gets produced. That split is the thing most likely to be
forgotten, so it is written down here.

Hyper = `SHIFT + CTRL + ALT + CMD` pressed together. Nobody can chord that by
hand, so both producers synthesise it:

| Producer | How | Scope |
|---|---|---|
| **This firmware** | Hold `TAB` -> `_TAB_HOLD_LAYER`, tap `1` -> `OSL(_TAB_HOLD_ONE_OSL)`, then a key sending `HYPR(...)` | Tofu65 only |
| **Karabiner-Elements** | Hold `caps_lock` (or hold `TAB`) -> Hyper; tap `caps_lock` alone -> `ESCAPE` | Every keyboard, incl. the MacBook's internal one |

Consequences worth remembering:

* **The firmware does NOT depend on Karabiner.** The Tofu65 produces Hyper on
  its own. Karabiner exists so the same shortcuts work on the laptop keyboard
  when the Tofu is unplugged.
* **A Hyper binding only works if the key is mapped in `_TAB_HOLD_ONE_OSL`.**
  Anything left `_______` there falls through and sends nothing. This bit us
  with `R` and `F`, which looked like Hyper keys but were transparent, so the
  Hammerspoon binding appeared broken when the firmware was simply never
  sending the chord. If a Hyper shortcut does nothing, check that layer FIRST.
* Karabiner's caps-lock Hyper *will* still work for a key that is transparent
  in the firmware, which makes this failure mode confusing: the same shortcut
  works from the laptop keyboard but not the Tofu.

### Karabiner config locations

* Live config: `~/.config/karabiner/karabiner.json`
* Importable rules: `~/.config/karabiner/assets/complex_modifications/*.json`

**Gotcha:** enabling a rule *copies* it into `karabiner.json`. Editing the file
under `assets/` afterwards does **not** update an already-enabled rule -- either
remove and re-add it in Complex Modifications, or edit `karabiner.json` directly
(Karabiner reloads it automatically).

### Custom rules in use

* **Hold TAB -> Hyper**, tap TAB -> `TAB`
* **Hold caps_lock -> Hyper**, tap caps_lock -> `ESCAPE`
* **Double-tap left Shift -> Spotlight** is NOT a Karabiner rule. It was tried
  there first and abandoned: Karabiner's variable + `to_delayed_action` idiom
  works for ordinary keys but proved unreliable on a modifier key, and Karabiner
  cannot easily be instrumented to find out why. It now lives in Hammerspoon
  (`~/.hammerspoon/doubleshift.lua`), where the rule can be stated directly:
  fire only if shift goes down-up-down, both presses are bare shift, no other
  key was pressed in between, and both are within 300ms. The "no other key in
  between" test is what stops CamelCase typing ("RememberToThankTheLord") from
  triggering it.

  Gotcha worth keeping: macOS reports the `fn` flag set alongside `shift` in
  some cases (and Hammerspoon-posted synthetic events always do). Treating `fn`
  as disqualifying silently broke edge detection and the whole thing looked
  dead. Only `cmd`/`ctrl`/`alt` disqualify a tap.

  This replaced Alfred's built-in double-tap-Shift hotkey, which was the
  original source of the CamelCase false positives.

## Related host-side config

* `~/.hammerspoon/apps.lua` - Hyper + key launches/focuses apps
  (D Spotify, E Ghostty, 1 Notion, S Slack, X 1Password, Z Zoom, C Clockify)
* `~/.hammerspoon/killprocess.lua` - Hyper + `R` opens a process-killer chooser
* `~/.hammerspoon/doubleshift.lua` - double-tap left Shift -> Spotlight
* Spotlight is at the macOS default `cmd+space` (`AppleSymbolicHotKeys` id 64 is
  unset), which is what the double-tap-Shift rule sends.

# Updating fork

Last done 2025-09-10 so that QMK’s changelog for 2025-05-25 lists: “Fix OS_DETECTION_KEYBOARD_RESET (#25015).” was added