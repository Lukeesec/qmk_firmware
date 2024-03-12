# The default keymap for the FC660C with QMK installed

# Commands / Setup
Install commands shouldn't be needed if apple-install-script was used for install. Please reference the Git for the commands
-> https://github.com/Lukeesec/apple-install-script/blob/main/setup.sh

1. Setup QMK -> `qmk setup LukeeSec/qmk_firmware`
    1. Firmware location -> `/Users/$USER/qmk_firmware`
2. Create keymap
    1. qmk new-keymap -kb <keyboard_name>
    2. From here I have yet to figure out how to set the wanted directory.. I dont want a "new-keymap" but I want to pass QMK compile,flash the directory path to my custom keymap. For now create new keymap, override with wanted keymap, and vscode from there.
3. For each change to the code that you want to push to the KB
    1. Buiild the firmware -> `qmk compile -kb fc660c -km lukeesec`
    2. Flashing new code -> `qmk flash -kb fc660c -km lukeesec`
    3. Push keybind to get into DFU -> FN (>_) + PGUP
        1. If something goes wrong there is a button under the keyboard to get into DFU
