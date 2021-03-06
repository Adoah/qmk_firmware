#include "adoorthsplit.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _DVORAK 1
#define _RAISE 2
#define _LOWER 3
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  RAISE,
  LOWER,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define QUIT LALT(KC_F4)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Func |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Esc  | Alt  |Lower |    Space    |Raise | Left | Up   | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */

    [_QWERTY] = KEYMAP(
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        FUNCTION, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        SFT_T(KC_ESC), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MT(MOD_RSFT, KC_ENT),
        KC_LCTL, KC_LGUI, KC_ESC, KC_LALT, LOWER, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT),

    /* Modded Dvorak
 *
 * ,----------------------------------.                  ,----------------------------------.
 * |   ;  |   P  |   Y  |   F  |   G  |                 |   C  |   R  |   L  |   V  |   Z  |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |   A  |   E  |   O  |   U  |   I  |                 |   D  |   H  |   T  |   N  |   S  |
 * |------+------+------+------+------|                 |------+------+------+------+------|
 * |   Q  |   J  |   K  |   X  |   B  |                 |   M  |   W  |   ,  |   .  |   /  |
 * `----------------------------------'                  `----------------------------------'
 *              ,-----------------------------.       ,---------------------------.
 *              | Windows| LOWER|      |     |       |      |      | RAISE| Tab |
 *              `--------------| Space|Enter|       |BckSpc|Shift |------+------.
 *                            |      |     |       |      |      |
 *                            `------------'       `------------'
*/
    [_DVORAK] = KEYMAP(
        KC_SCLN, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_V, KC_Z,
        KC_A, KC_E, KC_O, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S,
        KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_COMM, KC_DOT, KC_SLSH,
        LT(_LOWER, KC_TAB), KC_SPC, KC_LCTRL, KC_LGUI, KC_LALT, KC_LSFT, KC_BSPC, LT(_RAISE, KC_ENT)),

    /* Raise
 *
 * ,----------------------------------.                  ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |                  |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|                  |------+------+------+------+------|
 * |  DEL |   `  |  UP  |   :  |  ;   |                  |   -  |   (  |   )  |   [  |   ]  |
 * |------+------+------+------+------|                  |------+------+------+------+------|
 * |  Ctrl|   LEFT  |  DOWN |  RIGHT |DVORAK TOGGLE|     |   =  |   {  |   }  |   \  |   '  |
 * `----------------------------------'                  `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
    [_RAISE] = KEYMAP(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_DEL, KC_GRV, KC_UP, KC_COLN, KC_SCLN, KC_MINS, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC,
        KC_LCTL, KC_LEFT, KC_DOWN, KC_RIGHT, /*TG(DVORAK)*/ _______, KC_EQL, KC_LCBR, KC_RCBR, KC_BSLS, KC_QUOT,
        _______, _______, _______, _______, _______, _______, _______, _______),

    /* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Esc | lclk | msup | rclk |      |           |wh up |   _  |   +  |  del |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Caps|msleft|msdown|msrght|   ~  |           |wh dn |      | QUIT |   |  |   "  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|  Del |
 *                  `-------------|      |    | Enter|------+------.
 *                                |      |    |      |
 *                                `------'    `------
  */
    [_LOWER] = KEYMAP(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, _______, _______,
        KC_ESC, KC_BTN1, KC_MS_U, KC_BTN2, _______, KC_WH_U, KC_UNDS, KC_PLUS, KC_DEL, _______,
        KC_CAPS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TILD, KC_WH_D, TG(_DVORAK), QUIT, KC_PIPE, KC_DQT,
        _______, _______, _______, _______, KC_ENT, _______, _______, _______),

    /* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |      |RGBSAI|RGBSAD|           |RGBVAD|VolDn | PLAY |      |caltde|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Reset|RGBTOG|RGBMOD|RGBHUI|RGBHUD|           |RGBVAI|VolUp|MPrevi |MNext |Taskmg|
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
    [_ADJUST] = KEYMAP(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
        KC_F11, KC_F12, _______, RGB_SAI, RGB_SAD, RGB_VAD, KC_VOLU, KC_MPLY, _______, CALTDEL,
        RESET, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_VAI, KC_VOLD, KC_MPRV, KC_MNXT, TSKMGR,
        _______, _______, _______, _______, _______, _______, _______, _______)};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (IS_LAYER_ON(_ADJUST)) {
          layer_off(_RAISE);
          layer_off(_LOWER);
        }
      } else {
        layer_off(_RAISE);
        if (IS_LAYER_ON(_ADJUST)) {
          layer_off(_ADJUST);
          layer_on(_LOWER);
        }
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (IS_LAYER_ON(_ADJUST)) {
          layer_off(_LOWER);
          layer_off(_RAISE);
        }
      } else {
        layer_off(_LOWER);
        if (IS_LAYER_ON(_ADJUST)) {
          layer_off(_ADJUST);
          layer_on(_RAISE);
        }
      }
      return false;
  }
  return true;
}
