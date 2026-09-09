#include QMK_KEYBOARD_H


// Base layers should be lowest layers else issues can arrise
#define _BASE_LAYER_QWERTY 0
// #define _COLEMAK 1   // not implemented (no layer defined)
// #define _WINDOWS 2   // not implemented; re-add with OS detection if needed
#define _FUNCTION_LAYER 3
#define _THUMB_MODIFIER 4
#define _TAB_HOLD_LAYER 6
#define _TAB_HOLD_ONE_OSL 8
#define _TAB_HOLD_TWO_OSL 9

// Custom Keycodes
enum custom_keycodes {
  KC_THUMB_MODIFIER_LAYER = SAFE_RANGE,
  KC_EMAIL_XR
};

// ********** COMBOS **********
// Thumb Combo ... still a work in progress
const uint16_t PROGMEM thumb_combo[] = {KC_LGUI, KC_RALT, COMBO_END};
const uint16_t PROGMEM thumb_combo_reverse[] = {KC_RALT, KC_LGUI, COMBO_END};
combo_t key_combos[] = {
    COMBO(thumb_combo, KC_THUMB_MODIFIER_LAYER),
    COMBO(thumb_combo_reverse, KC_THUMB_MODIFIER_LAYER),
};
// ********** COMBOS **********


// ********** TAP DANCE **********
enum {
    TD_TILD = 0
};
// ********** TAP DANCE **********

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE_LAYER_QWERTY] = LAYOUT_65_ansi(
        KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  TD(TD_TILD), KC_HOME,
        LT(_TAB_HOLD_LAYER, KC_TAB),   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_BSPC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_END,
        KC_LCTL,  KC_LALT, KC_LGUI,                            KC_SPC,           KC_RALT, MO(_FUNCTION_LAYER), KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FUNCTION_LAYER] = LAYOUT_65_ansi(
        KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  QK_BOOT,
        _______, RM_TOGG, RM_NEXT, RM_HUEU, RM_HUED, RM_SATU, RM_SATD, RM_VALU, RM_VALD, _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_NO, QK_RBT,
        KC_CAPS, RM_SPDU, RM_SPDD, _______, _______, _______, _______, _______, _______, _______, _______, _______,         EE_CLR,  _______,
        KC_LSFT, _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______, _______,          KC_VOLU, KC_MUTE,
        _______, _______, _______,                            _______,          _______, _______, _______,          KC_MPRV, KC_VOLD, KC_MNXT
    ),
    [_THUMB_MODIFIER] = LAYOUT_65_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,          _______, _______, _______,          _______, _______, _______
    ),

    [_TAB_HOLD_LAYER] = LAYOUT_65_ansi(
        _______,          OSL(_TAB_HOLD_ONE_OSL),     OSL(_TAB_HOLD_TWO_OSL), _______,    _______,    _______,_______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          LCTL(KC_LEFT),LCTL(KC_UP),  LCTL(KC_RIGHT),_______,LCTL(KC_T),   _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          LCTL(KC_A),      LCTL(KC_DOWN), _______,    _______,_______,   _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,          _______,  _______, _______,    _______,  _______,   _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,          _______, _______,                            _______,          _______, _______, _______,          _______, _______, _______
    ),

    [_TAB_HOLD_ONE_OSL] = LAYOUT_65_ansi(
        HYPR(KC_P), HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5), HYPR(KC_6), HYPR(KC_7), HYPR(KC_8), HYPR(KC_9), HYPR(KC_0), _______, _______, _______, _______,
        HYPR(KC_TAB), HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T), HYPR(KC_Y), HYPR(KC_U), HYPR(KC_I), HYPR(KC_O), _______, _______, _______, _______, _______,
        HYPR(KC_BACKSLASH), HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G), HYPR(KC_H), HYPR(KC_J), HYPR(KC_K), HYPR(KC_L), _______, _______,          _______, _______,
        HYPR(KC_LSFT), HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B), HYPR(KC_N), HYPR(KC_M), _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            HYPR(KC_SPC),          _______, _______, _______,          _______, _______, _______
    ),
    [_TAB_HOLD_TWO_OSL] = LAYOUT_65_ansi(
        _______, KC_EMAIL_XR, KC_A, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,          _______, _______, _______,          _______, _______, _______
    )
};

// ********** TAP DANCE **********
tap_dance_action_t tap_dance_actions[] = {
    // TODO HOLD should be a different key like ~/
    [TD_TILD] = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, KC_TILD)
};
// ********** TAP DANCE **********

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_REBOOT:
          /* Don't allow reset from oneshot layer state */
          if (record->event.pressed && is_oneshot_layer_active()){
            clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            return false;
          }
          return true;
        case KC_THUMB_MODIFIER_LAYER:
            if (record->event.pressed) {
                layer_on(_THUMB_MODIFIER);
            } else {
                layer_off(_THUMB_MODIFIER);
            }
            return false;
        case KC_EMAIL_XR:
            if (record->event.pressed) {
                SEND_STRING("luke.martin@extremereach.com");
            }
            return false;
        default:
          return true;
    }
    return true;
}

// ********** RGB LAYER INDICATOR **********
// Lights ONLY the keys that are actually bound on the active layer, in a
// per-layer colour. Unbound keys go dark, so at a glance you can see both
// which layer is live and exactly what it offers -- useful with the one-shot
// hyper layer, which times out after ONESHOT_TIMEOUT with no other cue.
//
// Brightness follows the normal RGB value, so RM_VALU / RM_VALD (Fn+U / Fn+I)
// dim it for night and raise it for daylight. RGB_MATRIX_MAXIMUM_BRIGHTNESS in
// config.h caps how bright it can ever get.
#ifdef RGB_MATRIX_ENABLE

// Two independent knobs so the base wash and the layer colours can be tuned
// against each other:
//
//   BASE_GLOW_PERCENT - the resting white wash, as a % of the current RGB
//                       value. Lower = subtler desk glow.
//   LAYER_VAL         - a fixed brightness for layer colours, independent of
//                       the RGB value. Layers always render at exactly this,
//                       so Fn+U / Fn+I now tune ONLY the resting base wash and
//                       can never wash out or over-brighten the layer signal.
#define BASE_GLOW_PERCENT 20
#define LAYER_VAL         90

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    // Base layer: a soft neutral white wash across the whole board. This
    // OVERRIDES whatever animation is selected, so the board stays calm and the
    // layer colours below read as a deliberate signal rather than more noise.
    // To get animations back (RM_NEXT), delete this block.
    if (layer == _BASE_LAYER_QWERTY) {
        uint8_t w = (uint16_t)rgb_matrix_get_val() * BASE_GLOW_PERCENT / 100;
        for (uint8_t i = led_min; i < led_max; ++i) {
            rgb_matrix_set_color(i, w, w, w);
        }
        return false;
    }

    uint8_t r, g, b;
    switch (layer) {
        case _FUNCTION_LAYER:   r = 255; g =  70; b =   0; break;  // amber
        case _THUMB_MODIFIER:   r =   0; g = 120; b = 255; break;  // blue
        case _TAB_HOLD_LAYER:   r =   0; g = 200; b = 200; break;  // teal
        case _TAB_HOLD_ONE_OSL: r =   0; g = 255; b =  60; break;  // green (hyper)
        case _TAB_HOLD_TWO_OSL: r = 255; g =   0; b = 160; break;  // magenta
        default: return false;
    }

    // Fixed layer brightness, deliberately not tied to the RGB value.
    r = (uint16_t)r * LAYER_VAL / 255;
    g = (uint16_t)g * LAYER_VAL / 255;
    b = (uint16_t)b * LAYER_VAL / 255;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index == NO_LED || index < led_min || index >= led_max) {
                continue;
            }
            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col, row});
            if (kc > KC_TRNS) {
                rgb_matrix_set_color(index, r, g, b);
            } else {
                rgb_matrix_set_color(index, 0, 0, 0);
            }
        }
    }
    return false;
}
#endif
