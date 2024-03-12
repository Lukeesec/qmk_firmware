#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=false;
}

// Base layers should be lowest layers else issues can arrise
#define _BASE_LAYER_QWERTY 0
#define _COLEMAK 1
#define _WINDOWS 2
#define _FUNCTION_LAYER 3
#define _THUMB_MODIFIER 4
#define _ONESHOT_LAYER 5
#define _TAB_HOLD_LAYER 6
#define _ONE_HOLD_LAYER 7

// Custom Keycodes
enum custom_keycodes {
  EMAIL_CUMULUSOPS = SAFE_RANGE,
  EMAIL_EXTREMEREACH,
  EMAIL_FISSION_CONSULTING,
  EMAIL_GMAIL,
  TEN_UP,
  TEN_DOWN,
  THUMB_MODIFIER_LAYER,
};

// ********** Tap Dance START **********
// Custom Combo Keycodes
const uint16_t PROGMEM thumb_combo[] = {KC_LGUI, KC_RALT, COMBO_END};
const uint16_t PROGMEM thumb_combo_reverse[] = {KC_RALT, KC_LGUI, COMBO_END};
combo_t key_combos[] = {
    COMBO(thumb_combo, THUMB_MODIFIER_LAYER),
    COMBO(thumb_combo_reverse, THUMB_MODIFIER_LAYER),
};

// Tap Dance
enum {
    TD_Q_NAV,
    TD_E_NAV,
    TD_W_NAV,
    Q_LFT_NAV,
    E_RHT_NAV,
    W_UP_NAV,
    SHFT_ONESHOT_LAYER2,
    ESC_SWITCH_LAYER,
    TD_TILD,
};

// Tap Dance
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

typedef struct {
  bool is_press_action;
  int state;
} tap;

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

int cur_dance (tap_dance_state_t *state);
void shft_finished (tap_dance_state_t *state, void *user_data);
void shft_reset (tap_dance_state_t *state, void *user_data);

// ********** TAP DANCE END **********

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /* Base Layer
   * ,------------------------------------------------------------------------------------------------
   * | Esc         |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | TILD|~/ |       | PGUP |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | Tab          |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P       |  [ { |  ] } |  |\  |  | PGDOWN |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | Backspace     |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ; :  |  " '        |    Enter    |
   * |--------------------------------------------------------------------------------------------+
   * | Shift|OSL      |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /               | Shift            | Up  |
   * +--------------------------------------------------------------------------------------------+-----+
   * | Enter Ctrl      | Option   | GUI  |               Space                | Option  | Ctrl | FN    | Left| Down |Right|
   * `--------------------------------------------------------------------------------------------------
   */

  [_BASE_LAYER_QWERTY] = LAYOUT(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINUS,KC_EQL, TD(TD_TILD),                     KC_PGUP,
        LT(3, KC_TAB), KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,     KC_PGDN,
        KC_BSPC,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,     KC_ENT,
        TD(SHFT_ONESHOT_LAYER2),KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,     KC_UP,
        KC_LCTL,KC_LALT,KC_LGUI,          KC_SPC,                       KC_RALT,KC_RCTL,MO(1),      KC_LEFT,KC_DOWN,KC_RGHT
    ),

   /* TODO COLEMAK(DHm) Layer
   * ,------------------------------------------------------------------------------------------------
   * | Esc         |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | TILD|~/ |       | PGUP |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | Tab          |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P       |  [ { |  ] } |  |\  |  | PGDOWN |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | Backspace     |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ; :  |  " '        |    Enter    |
   * |--------------------------------------------------------------------------------------------+
   * | Shift|OSL      |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /               | Shift            | Up  |
   * +--------------------------------------------------------------------------------------------+-----+
   * | Enter Ctrl      | Option   | GUI  |               Space                | Option  | Ctrl | FN    | Left| Down |Right|
   * `--------------------------------------------------------------------------------------------------
   */

    [_COLEMAK] = LAYOUT(
        KC_ESC,        KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINUS,KC_EQL, TD(TD_TILD),                     KC_PGUP,
        LT(3, KC_TAB), KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,   KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,   KC_LBRC,KC_RBRC,KC_BSLS,     KC_PGDN,
        KC_BSPC,       KC_A,  KC_R,   KC_S,   KC_T,   KC_D,   KC_H,   KC_N,   KC_E,   KC_I,   KC_O,KC_QUOT,     KC_ENT,
        TD(SHFT_ONESHOT_LAYER2), KC_X,   KC_C,   KC_V,   KC_B,   KC_Z,   KC_K,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,     KC_UP,
        KC_LCTL,KC_LALT,KC_LGUI,          KC_SPC,                       KC_RALT,KC_RCTL,MO(1),      KC_LEFT,KC_DOWN,KC_RGHT
    ),

  [_WINDOWS] = LAYOUT(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_CAPS,     TO(_BASE_LAYER_QWERTY),
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,     KC_PGDN,
        KC_BSPC,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,     KC_ENT,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,     KC_UP,
        KC_LCTL,KC_LGUI,KC_LALT,          KC_SPC,                       KC_RALT,KC_RCTL,MO(_FUNCTION_LAYER),      KC_LEFT,KC_DOWN,KC_RGHT
    ),


   /* Thumb Modifier Layer
   * ,------------------------------------------------------------------------------------------------
   * | None          |  None  |  None  |  None  |  None  |  None  |  None  |  None  |  None  |  None  |  None  |  None  |  None  | None |       | None |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | None          |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0       |  None |  None |  None |  | None |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | None          |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  | )  |  None    |    None    |
   * |--------------------------------------------------------------------------------------------+
   * | None          |  None  |  None  |  None  |  None  |  None  |  None  |  None  |  None  |  None |  None               | None            | None  |
   * +--------------------------------------------------------------------------------------------+-----+
   * | None          | None   | MO()  |               None                | MO()  | None | None    | None| None |None|
   * `--------------------------------------------------------------------------------------------------
   */
    [_THUMB_MODIFIER] = LAYOUT(
    KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,
    KC_NO,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_NO,KC_NO,KC_NO,     KC_NO,
    KC_NO,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_NO,     KC_NO,
    KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, KC_NO,KC_NO,KC_NO,     KC_NO,
    KC_NO,KC_NO,KC_NO,                KC_NO,                KC_NO,KC_NO,KC_NO,       KC_NO,KC_NO,KC_NO
    ),

   /* Function Layer
   * Default Temporary Layer -> DTL
   * ,------------------------------------------------------------------------------------------------
   * | ~         |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F0  |  F10  |  F11  | F12 |       | QMK FLASH |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | None          |  DTL QWERTY  |  DTL COLEMAK DHM  |  DTL WINDOWS  |  R  |  T  |  Y  |  U  |  I  |  O  |  P       |  [ NONE |  NONE |  NONE  |   | NONE |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | None     |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ; :  |  " '        |    NONE    |
   * |--------------------------------------------------------------------------------------------+
   * | None      |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /               | NONE            | NONE  |
   * +--------------------------------------------------------------------------------------------+-----+
   * | None      | None   | None  |               None                | NONE  | NONE | FN    | NONE| NONE |NONE|
   * --------------------------------------------------------------------------------------------------
   */
  [_FUNCTION_LAYER] = LAYOUT(
        KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,     QK_BOOT,
        _______,DF(_BASE_LAYER_QWERTY),DF(_COLEMAK),DF(_WINDOWS),_______,_______,_______,_______,KC_PSCR,KC_SLCT,KC_PAUS,_______,_______,_______,     _______,
        _______,_______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_PGUP,_______,_______,     _______,
        _______,_______,_______,_______,_______,_______,_______,_______,KC_END, KC_PGDN,_______,_______,     _______,
        _______,_______,_______,                _______,                _______,_______,MO(1),       _______,_______,_______
    ),

  /* OSL Layer
   * ,------------------------------------------------------------------------------------------------
   * | Esc         |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | TILD|~/ |       | PGUP |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | Tab          |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P       |  [ { |  ] } |  |\  |  | PGDOWN |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | Backspace     |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ; :  |  " '        |    Enter    |
   * |--------------------------------------------------------------------------------------------+
   * | Shift|OSL      |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /               | Shift            | Up  |
   * +--------------------------------------------------------------------------------------------+-----+
   * | Enter Ctrl      | Option   | GUI  |               Space                | Option  | Ctrl | FN    | Left| Down |Right|
   * `--------------------------------------------------------------------------------------------------
   */
  [_ONESHOT_LAYER] = LAYOUT(
    HYPR(KC_M), HYPR(KC_1),  HYPR(KC_2),  HYPR(KC_3),  HYPR(KC_4),  HYPR(KC_EQUAL),  HYPR(KC_LEFT_BRACKET),  HYPR(KC_RIGHT_BRACKET),  _______,  _______,  _______, _______, _______, _______,     TG(_WINDOWS),
    HYPR(KC_RBRC),HYPR(KC_Q),HYPR(KC_W),HYPR(KC_E),HYPR(KC_R),_______,_______,_______,_______,_______,_______,_______,_______,_______,     _______,
    HYPR(KC_BSLS),HYPR(KC_A),HYPR(KC_S),HYPR(KC_D), HYPR(KC_F),_______,_______,_______,_______,_______,_______,_______,     _______,
    HYPR(KC_LBRC),HYPR(KC_Z),HYPR(KC_X),HYPR(KC_C),HYPR(KC_V),HYPR(KC_B),HYPR(KC_N),_______,_______, _______,_______,_______,     _______,
    KC_NO,_______,_______,                HYPR(KC_SPC),                _______,_______,_______,       _______,_______,_______
    ),

   /* Tab Hold Layer
   * ,------------------------------------------------------------------------------------------------.
   * | Authy |  Notion  |  SUBL  |  Pycharm  |  _______  |  _______  |  _______  |  _______  |  _______  |  _______  |  _______  |  -  |  =  | NONE |       | Bootloader |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | _______    |  _______  |  _______  |  Terminal  |  _______  |  T  |  Y  |  U  |  I  |  O  |  P  |  [ { |  ] } |  |\  |  | _______ |
   * |-----------------------------------------------------------------------------------------+  +-----+
   * | Alfred |  Todoist  |  Slack  |  Spotify  |  Safari  |  G  |  H  |  J  |  K  |  L  |  ; :  |  " '  |    Enter    |
   * |--------------------------------------------------------------------------------------------+
   * | Clipboard H      |  Z  |  X  |  Chrome  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | Shift            | Up  |
   * +--------------------------------------------------------------------------------------------+-----+
   * | _______  | _______   | GUI  |               1Pass Quick            | Option  | Ctrl | FN | Left| Down |Right|
   * `--------------------------------------------------------------------------------------------------´
   */
  [_TAB_HOLD_LAYER] = LAYOUT(
    _______, HYPR(KC_5),   HYPR(KC_6),   HYPR(KC_7),   HYPR(KC_8),   HYPR(KC_9),   HYPR(KC_MINUS),   _______,   _______,   _______,   _______,   _______,_______, _______,     _______,
    _______, LCTL(KC_LEFT),   LCTL(KC_UP),   LCTL(KC_RIGHT),   HYPR(KC_GRAVE),   _______,   _______,   _______,   _______,   _______,   _______,   _______,_______,_______, _______,
    HYPR(KC_BACKSLASH),HYPR(KC_G),   HYPR(KC_Y),   HYPR(KC_U),   HYPR(KC_COMMA),   _______,   _______,   _______,   _______,   _______,   _______,_______,     _______,
    HYPR(KC_NONUS_HASH),HYPR(KC_B),   HYPR(KC_H),   HYPR(KC_J),   HYPR(KC_DOT),   _______,   _______,   _______,   _______,_______, _______,_______,     _______,
    _______,_______,HYPR(KC_QUOTE),          HYPR(KC_SEMICOLON),                       _______,_______,_______,      _______,_______,_______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    tap_dance_action_t *action;

    switch (keycode) {
        case QK_REBOOT:
          /* Don't allow reset from oneshot layer state */
          if (record->event.pressed && is_oneshot_layer_active()){
            clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            return false;
          }
          return true;
        case TD(Q_LFT_NAV): case TD(E_RHT_NAV): case TD(W_UP_NAV):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
        
        case THUMB_MODIFIER_LAYER:
            if (record->event.pressed) {
                layer_on(_THUMB_MODIFIER);
            } else {
                layer_off(_THUMB_MODIFIER);
            }
            return false;
        case TEN_UP:
            if (record->event.pressed) {
                // for loop KC_UP 10 times
                for (int i = 0; i < 10; i++) {
                    tap_code(KC_UP);
                }
            }
            return false;
        case TEN_DOWN:
            if (record->event.pressed) {
                // for loop KC_DOWN 10 times
                for (int i = 0; i < 10; i++) {
                    tap_code(KC_DOWN);
                }
            }
            return false;
        case EMAIL_EXTREMEREACH:
            if (record->event.pressed) {
                SEND_STRING("luke.martin@extremereach.com");
            }
            return false;
        case EMAIL_CUMULUSOPS:
            if (record->event.pressed) {
                SEND_STRING("luke.martin@cumulusops.com");
            }
            return false;
        case EMAIL_FISSION_CONSULTING:
            if (record->event.pressed) {
                SEND_STRING("lmartin@fissionconsulting.com");
            }
            return false;
        case EMAIL_GMAIL:
            if (record->event.pressed) {
                SEND_STRING("luke.lm60@gmail.com");
            }
            return false;
        default:
          return true;
    }
    return true;
}

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

void tild_home(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_TILD);
        unregister_code16(KC_TILD);
        reset_tap_dance(state);
    } else if (state->count == 2) {
        SEND_STRING("~/");
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) return TD_SINGLE_HOLD;
    else if (!state->pressed) return TD_SINGLE_TAP;
    else return TD_SINGLE_HOLD;
  }
  else if (state->count == 2) {
    // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
    // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
    // keystrokes of the key, and not the 'double tap' action/macro.
    if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
    else if (state->pressed) return TD_DOUBLE_HOLD;
    else return TD_DOUBLE_TAP;
  } else return TD_UNKNOWN;
}

static td_tap_t shfttap_state = {
    .is_press_action = true,
    .state = TD_NONE
};


void shft_finished (tap_dance_state_t *state, void *user_data) {
  shfttap_state.state = cur_dance(state);
  switch (shfttap_state.state) {
    case TD_SINGLE_TAP: set_oneshot_layer(2, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case TD_SINGLE_HOLD: register_code(KC_LSFT); break;
    case TD_DOUBLE_TAP: set_oneshot_layer(4, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    default: break;
  }
}

void shft_reset (tap_dance_state_t *state, void *user_data) {
  switch (shfttap_state.state) {
    case TD_SINGLE_TAP: break;
    case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break;
    case TD_DOUBLE_TAP: break;
    case TD_DOUBLE_HOLD: break;
    default: break;
    }
    shfttap_state.state = TD_NONE;
}


static td_tap_t esctap_state = {
    .is_press_action = true,
    .state = TD_NONE
};


void esc_finished (tap_dance_state_t *state, void *user_data) {
  esctap_state.state = cur_dance(state);
  switch (esctap_state.state) {
    case TD_SINGLE_TAP: register_code(KC_ESC); break;
    case TD_SINGLE_HOLD: break;
    case TD_DOUBLE_HOLD:
        if (biton32(layer_state) == _WINDOWS) {
            layer_off(_WINDOWS);
        } else layer_on(_WINDOWS); break;
        break;
    default: break;
  }
}

void esc_reset (tap_dance_state_t *state, void *user_data) {
  switch (esctap_state.state) {
    case TD_SINGLE_TAP: unregister_code(KC_ESC); break;
    case TD_SINGLE_HOLD: break;
    case TD_DOUBLE_TAP: break;
    default: break;
    }
    esctap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [SHFT_ONESHOT_LAYER2]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,shft_finished, shft_reset),
    [ESC_SWITCH_LAYER]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,esc_finished, esc_reset),
    [TD_TILD] = ACTION_TAP_DANCE_FN(tild_home)
};
