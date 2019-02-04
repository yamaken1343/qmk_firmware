#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _DVORAK 1
#define _TENKY 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

#define CC_NORM MAGIC_UNSWAP_CONTROL_CAPSLOCK
#define CC_SWAP MAGIC_SWAP_CONTROL_CAPSLOCK

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  TENKY,
  CUT,
  COPY
  PSTE,
  UNDO
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | BKSP |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Shift  /       \Shift \  |RAISE | RGUI | ESC  |
 *                   |      |      |Space |/       /         \      \ |Enter |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_BSLS, \
                             KC_LALT, KC_LGUI, LT(_LOWER,KC_SPC), KC_LSFT,   KC_RSFT,LT(_RAISE,KC_ENT),   KC_RGUI, KC_ESC \
),

/* Dvorak
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |   =  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   '  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  |   /  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  |   -  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  |   [  |   ]  |   B  |   M  |   W  |   V  |   Z  |   \  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   *                      | Alt  | GUI  |Lower |      |      |Raise | GUI  | KANA |
   *                      |      |      |Space |Shift |Shift |Enter |      |      |
   *                      ---------------------------------------------------------
   */
[_DVORAK] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,             KC_7,    KC_8,  KC_9,  KC_0,   KC_EQL, \
      KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                           KC_F,             KC_G,    KC_C,  KC_R,  KC_L,   KC_SLSH, \
      KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,LT(_TENKEY,KC_I) ,                  KC_D,             KC_H,    KC_T,  KC_N,  KC_S,   KC_MINS, \
      KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,         KC_LBRC, KC_RBRC, KC_B,             KC_M,    KC_W,  KC_V,  KC_Z,   KC_BSLS , \
                        KC_LALT, KC_LGUI,LT(_LOWER,KC_SPC),KC_LSFT, KC_RSFT, LT(_RAISE,KC_ENT),KC_RGUI, KC_ESC \
      ),
/* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  ESC |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |BrowBk|      |      |BrowFw|      |             | Bksp | Left |  Up  | Down |Right |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | Undo | Cut  | Copy |Paste |      |  (   |   )  | Del  | Home |PageUp|PageDn| End  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   *                      |      |      |      |      |      |ADJUST| Next | Play |
   *                      ---------------------------------------------------------
   */
[_LOWER] = LAYOUT( \
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
      KC_GRV,  KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12, \
      _______, KC_WBAK, _______, _______, KC_WFWD, _______,                   KC_BSPC, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_MINS, \
      _______, UNDO   , CUT    , COPY   , PSTE   , _______, KC_LPRN, KC_RPRN, KC_DEL,  KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______, \
                                 _______, _______, _______, _______, _______, ADJUST, KC_MNXT, KC_MPLY \
      ),

/* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  ESC |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |BrowBk|      |      |BrowFw|      |             |      |   -  |   =  |   [  |   ]  |   _  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | Undo | Cut  | Copy |Paste |      |   (  |   )  |      |   _  |   +  |   {  |   }  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   *                      |      |      |ADJUST|      |      |      | Next | Play |
   *                      ---------------------------------------------------------
   */
[_RAISE] = LAYOUT( \
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_F12, \
      _______, KC_WBAK, _______, _______, KC_WFWD, _______,                   _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_UNDS, \
      _______, UNDO   , CUT    , COPY   , PSTE   , _______, KC_LPRN, KC_RPRN, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, \
                                 _______, _______, ADJUST , _______, _______, _______, KC_MNXT, KC_MPLY \
      ),

/* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  ESC |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |Reset |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | CAPS |Insert|      |Aud on|Audoff| Mac  |             | Win  |Qwerty|Tenkey|Dvorak|      |  F12 |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |PRTSCR|      |      |      |      |return|      |      | swap | Back | Vol+ | Vol- | Next | Play |
   * |      |      |      |      |      |caps-ctrl    |      |caps-ctrl    |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   *                      |      |      |      |      |      |      |      | Play |
   *                      ---------------------------------------------------------
   */
[_ADJUST] =  LAYOUT( \
      KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
      RESET  , KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
      KC_CAPS, KC_INS , _______, AU_ON,   AU_OFF,  AG_NORM,                   AG_SWAP, QWERTY,  TENKEY , DVORAK,  _______, KC_F12, \
      KC_PSCR, _______, _______, _______, _______, CC_NORM, _______, _______, CC_SWAP, KC_MPRV, KC_VOLU, KC_VOLD, KC_MNXT, KC_MPLY, \
                                 _______, _______, _______, _______, _______, _______, _______, KC_MPLY \
      ),


/* Ten key pad
* ,-----------------------------------------.             ,-----------------------------------------.
* |  ESC |      |      |      |      |      |             |NUMLK | Tab  |   /  |   *  |      | Bksp |
* |------+------+------+------+------+------|             |------+------+------+------+------+------|
* |      |      |  Up  |      |      |      |             |      |   7  |   8  |   9  |   =  | Del  |
* |------+------+------+------+------+------|             |------+------+------+------+------+------|
* | Ctrl | Left | Down | Right|      |      |             |      |   4  |   5  |   6  |   -  |Enter |
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
* |Shift | Undo | Cut  | Copy |Paste |      |      |      |      |   1  |   2  |   3  |   +  |Shift |
* |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
*                      |      |      |      |      |  SP  |Enter |   0  |   .  |
*                      ---------------------------------------------------------
*/
[_TENKEY] =  LAYOUT( \
      KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_NLCK, KC_TAB,  KC_PSLS, KC_PAST, XXXXXXX, KC_BSPC, \
      _______, XXXXXXX, KC_UP  , XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PEQL, KC_DEL, \
      KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,                   _______, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, KC_ENT, \
      KC_LSFT, KC_UNDO, KC_CUT , KC_COPY, KC_PSTE, XXXXXXX, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, KC_RSFT, \
                                 _______, _______, _______, _______, KC_SPC , _______, KC_P0,   KC_PDOT \
      )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
      case DVORAK:
          if(record->event.pressed){
              persistent_default_layer_set(1UL << _DVORAK);
              default_layer_current_mode = _DVORAK;
          }
          return false;
          break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;

      case TENKEY:
          if(record->event.pressed){
              persistent_default_layer_set(1UL << _TENKEY);
              default_layer_current_mode = _TENKEY;
              return false;
          }
          break;
      case UNDO:
          if(record->event.pressed){
              if(keymap_config.swap_lalt_lgui == false){
                  SEND_STRING(SS_LGUI("z"));
              }else{
                  SEND_STRING(SS_LCTRL("z"));
              }
          }
          return false;
          break;
      case COPY:
          if(record->event.pressed){
              if(keymap_config.swap_lalt_lgui == false){
                  SEND_STRING(SS_LGUI("c"));
              }else{
                  SEND_STRING(SS_LCTRL("c"));
              }
          }
          return false;
          break;
      case PSTE:
          if(record->event.pressed){
              if(keymap_config.swap_lalt_lgui == false){
                  SEND_STRING(SS_LGUI("v"));
              }else{
                  SEND_STRING(SS_LCTRL("v"));
              }
          }
          return false;
          break;
      case CUT:
          if(record->event.pressed){
              if(keymap_config.swap_lalt_lgui == false){
                  SEND_STRING(SS_LGUI("x"));
              }else{
                  SEND_STRING(SS_LCTRL("x"));
              }
          }
          return false;
          break;
  }
  return true;
}