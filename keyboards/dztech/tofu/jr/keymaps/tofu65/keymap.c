#include QMK_KEYBOARD_H


// Base layers should be lowest layers else issues can arrise
#define _BASE_LAYER_QWERTY 0
#define _COLEMAK 1
#define _WINDOWS 2
#define _FUNCTION_LAYER 3
#define _THUMB_MODIFIER 4
#define _TAB_HOLD_LAYER 6
#define _TAB_HOLD_ONE_OSL 8
#define _TAB_HOLD_TWO_OSL 9

// Custom Keycodes
enum custom_keycodes {
  KC_TEN_UP = SAFE_RANGE,
  KC_TEN_DOWN,
  KC_THUMB_MODIFIER_LAYER,
  KC_EMAIL_XR,
  USB_RESTART
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
// For quad function
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
    Q_LFT_NAV = 0,
    E_RHT_NAV,
    W_UP_NAV,
    S_DOWN_NAV,
    // SHFT_HYPR,
    TD_TILD
};

// Speciifcally used for Navigation of MacOS
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

// For quad function
typedef struct {
  bool is_press_action;
  int state;
} tap;

// function to determine the current tapdance state
int cur_dance (tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void shft_finished (tap_dance_state_t *state, void *user_data);
void shft_reset (tap_dance_state_t *state, void *user_data);
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
        KC_CAPS, RM_SPDU, RM_SPDD, _______, _______, _______, _______, _______, _______, _______, _______, _______,         EE_CLR,  USB_RESTART,
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
        HYPR(KC_P), HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        HYPR(KC_TAB), HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        HYPR(KC_BACKSLASH), HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        HYPR(KC_LSFT), HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            HYPR(KC_SPC),          _______, _______, _______,          _______, _______, _______
    ),
    [_TAB_HOLD_TWO_OSL] = LAYOUT_65_ansi(
        _______, KC_EMAIL_XR, KC_A, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,          _______, _______, _______,          _______, _______, _______
    ),
    [10] = LAYOUT_65_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,          _______, _______, _______,          _______, _______, _______
    )
};

// ********** TAP DANCE **********
// Tap-hold helper functions for ACTION_TAP_DANCE_TAP_HOLD
void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                                        \
    {                                                                               \
        .fn        = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, \
        .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}),               \
    }

tap_dance_action_t tap_dance_actions[] = {
    // Navigation tap dance actions - these appear to be for MacOS navigation
    [Q_LFT_NAV] = ACTION_TAP_DANCE_TAP_HOLD(KC_Q, LCTL(KC_LEFT)),
    [E_RHT_NAV] = ACTION_TAP_DANCE_TAP_HOLD(KC_E, LCTL(KC_RIGHT)),
    [W_UP_NAV] = ACTION_TAP_DANCE_TAP_HOLD(KC_W, LCTL(KC_UP)),
    [S_DOWN_NAV] = ACTION_TAP_DANCE_TAP_HOLD(KC_S, LCTL(KC_DOWN)),
    // [SHFT_HYPR]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,shft_finished, shft_reset),
    // TODO HOLD should be a different key like ~/
    [TD_TILD] = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, KC_TILD)
};
// ********** TAP DANCE **********

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case QK_REBOOT:
          /* Don't allow reset from oneshot layer state */
          if (record->event.pressed && is_oneshot_layer_active()){
            clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            return false;
          }
          return true;
        case TD(Q_LFT_NAV): case TD(E_RHT_NAV): case TD(W_UP_NAV): case TD(S_DOWN_NAV):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;
        case KC_THUMB_MODIFIER_LAYER:
            if (record->event.pressed) {
                layer_on(_THUMB_MODIFIER);
            } else {
                layer_off(_THUMB_MODIFIER);
            }
            return false;
        case KC_TEN_UP:
            if (record->event.pressed) {
                // for loop KC_UP 10 times
                for (int i = 0; i < 10; i++) {
                    tap_code(KC_UP);
                }
            }
            return false;
        case KC_EMAIL_XR:
            if (record->event.pressed) {
                SEND_STRING("luke.martin@extremereach.com");
            }
            return false;
        case KC_TEN_DOWN:
            if (record->event.pressed) {
                // for loop KC_DOWN 10 times
                for (int i = 0; i < 10; i++) {
                    tap_code(KC_DOWN);
                }
            }
            return false;
        default:
          return true;
    }
    return true;
}

// ********** TAP DANCE **********
// determine the tapdance state to return
int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}
