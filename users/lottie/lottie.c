// Copyright 2023-24 Gyozo Gaspar
//
// This file is part of Lottie layout. The Lottie layout is free
// software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option)
// any later version.  The Lottie layout is distributed in the hope
// that it will be useful, but WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE. See the GNU General Public License for more details.  You
// should have received a copy of the GNU General Public License along
// with Lottie layout. If not, see <https://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lottie.h"
#include "whu.h"
#include "layers.h"
#include "whu-layers.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [SYSTEM] = MAKE_LAYER(ALL, SYS),
    [WHU_BASE] = MAKE_LAYER(WHU, HBDC),
    [WHU_LMOD] = MAKE_LAYER(WHU, LMOD),
    [WHU_RMOD] = MAKE_LAYER(WHU, RMOD),
    [WHU_NAV] = MAKE_LAYER(WHU, NAV),
    [WHU_NUM] = MAKE_LAYER(WHU, NUM),
    [WHU_FUN] = MAKE_LAYER(WHU, FUN),
    [WHU_NPAD] = MAKE_LAYER(WHU, NPAD),
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

// Based on qmk_firmware\keyboards\crkbd\keymaps\default

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf (keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
            record->event.key.row, record->event.key.col,
            keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }

  switch(keycode) {
    PROCESS_RECORD_CASE(WHU_LMOD_LOLT, WHU_ESC, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LLT, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LRT, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LMT, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LIT, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LIIT, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RIIT, WHU_HBDC_RIIT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RIT, WHU_HBDC_RIT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RMT, WHU_HBDC_RMT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RRT, WHU_HBDC_RRT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RLT, WHU_HBDC_RLT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_ROLT, WHU_HBDC_ROLT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LOLH, WHU_O_DACUTE, WHU_BASE)
    //Implemented in Layout: PROCESS_RECORD_CASE(WHU_LMOD_LLH, OSM(MOD_LGUI), WHU_BASE)
    //Implemented in Layout: PROCESS_RECORD_CASE(WHU_LMOD_LRH, OSM(MOD_LALT), WHU_BASE)
    //Implemented in Layout: PROCESS_RECORD_CASE(WHU_LMOD_LMH, OSM(MOD_LCTL), WHU_BASE)
    //Implemented in Layout: PROCESS_RECORD_CASE(WHU_LMOD_LIH, OSM(MOD_LSFT), WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LIIH, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RIIH, WHU_HBDC_RIIH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RIH, WHU_HBDC_RIH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RMH, WHU_HBDC_RMH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RRH, WHU_HBDC_RRH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RLH, WHU_HBDC_RLH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_ROLH, WHU_O_DIARESIS, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LOLB, WHU_DEL, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LLB, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LRB, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LMB, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LIB, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LIIB, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RIIB, WHU_HBDC_RIIB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RIB, WHU_HBDC_RIB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RMB, WHU_HBDC_RMB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RRB, WHU_HBDC_RRB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RLB, WHU_HBDC_RLB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_ROLB, WHU_HBDC_ROLB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LITH, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LTH, WHU_HBDC_LTH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_LOTH, KC_NO, SYSTEM)
    PROCESS_RECORD_CASE(WHU_LMOD_ROTH, WHU_HBDC_ROTH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RTH, WHU_HBDC_RTH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_LMOD_RITH, KC_NO, WHU_NAV)

    PROCESS_RECORD_CASE(WHU_RMOD_LOLT, WHU_HBDC_LOLT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LLT, WHU_HBDC_LLT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LRT, WHU_HBDC_LRT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LMT, WHU_HBDC_LMT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LIT, WHU_HBDC_LIT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LIIT, WHU_HBDC_LIIT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_RIIT, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_RIT, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_RMT, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_RRT, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_RLT, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_ROLT, WHU_TAB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LOLH, WHU_O_DACUTE, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LLH, WHU_HBDC_LLH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LRH, WHU_HBDC_LRH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LMH, WHU_HBDC_LMH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LIH, WHU_HBDC_LIH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LIIH, WHU_HBDC_LIIH, WHU_BASE)
    PROCESS_RECORD_CASE_CW(WHU_RMOD_RIIH, WHU_BASE)
    //Implemented in Layout: WHU_RMOD_RIH
    //Implemented in Layout: WHU_RMOD_RMH
    //Implemented in Layout: WHU_RMOD_RRH
    //Implemented in Layout: WHU_RMOD_RLH
    PROCESS_RECORD_CASE(WHU_RMOD_ROLH, WHU_O_DIARESIS, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LOLB, WHU_HBDC_LOLB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LLB, WHU_HBDC_LLB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LRB, WHU_HBDC_LRB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LMB, WHU_HBDC_LMB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LIB, WHU_HBDC_LIB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LIIB, WHU_HBDC_LIIB, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_RIIB, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_RIB, KC_NO , WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_RMB, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_RRB, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_RLB, KC_NO, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_ROLB, WHU_ENT, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LITH, KC_NO, WHU_NAV)
    PROCESS_RECORD_CASE(WHU_RMOD_LTH, WHU_HBDC_LTH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_LOTH, KC_NO, SYSTEM)
    PROCESS_RECORD_CASE(WHU_RMOD_ROTH, WHU_HBDC_ROTH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_RTH, WHU_HBDC_RTH, WHU_BASE)
    PROCESS_RECORD_CASE(WHU_RMOD_RITH, KC_NO, WHU_BASE)

        PROCESS_RECORD_CASE(WHU_NUM_LOLT, WHU_ESC, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LLT, WHU_AMPS, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LRT, WHU_LT, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LMT, WHU_LPAR, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LIT, WHU_EQUAL, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LIIT, WHU_SEMI, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RIIT, WHU_COLON, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RIT, WHU_DQT, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RMT, WHU_RPAR, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RRT, WHU_GT, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RLT, WHU_DOT, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_ROLT, WHU_TAB, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LOLH, KC_NO, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LLH, WHU_N6, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LRH, WHU_N0, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LMH, WHU_N2, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LIH, WHU_N4, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LIIH, WHU_STAR, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RIIH, WHU_FSLH, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RIH, WHU_N5, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RMH, WHU_N3, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RRH, WHU_N1, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RLH, WHU_N7, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_ROLH, KC_NO, WHU_NPAD)
        PROCESS_RECORD_CASE(WHU_NUM_LOLB, WHU_DEL, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LLB, WHU_PIPE, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LRB, WHU_LBKT, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LMB, WHU_RBKT, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LIB, WHU_N8, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LIIB, WHU_PLUS, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RIIB, WHU_MINUS, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RIB, WHU_N9, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RMB, WHU_LBRC, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RRB, WHU_RBRC, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RLB, WHU_COMMA, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_ROLB, WHU_ENT, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LITH, WHU_O_DACUTE, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LTH, WHU_HBDC_LTH, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_LOTH, KC_NO, SYSTEM)
        PROCESS_RECORD_CASE(WHU_NUM_ROTH, WHU_BSPC, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RTH, WHU_SPACE, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_NUM_RITH, KC_NO, WHU_RMOD)

        PROCESS_RECORD_CASE(WHU_FUN_LOLT, WHU_ESC, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LLT, WHU_PRCNT, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LRT, WHU_TILDE, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LMT, WHU_DLLR, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LIT, WHU_GRAVE, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LIIT, KC_NO, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RIIT, KC_SCRL, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RIT, WHU_SQT, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RMT, WHU_BSLH, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RRT, WHU_QMARK, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RLT, WHU_HASH, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_ROLT, WHU_TAB, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LOLH, KC_NO, WHU_NPAD)
        PROCESS_RECORD_CASE(WHU_FUN_LLH, WHU_F6, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LRH, WHU_F10, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LMH, WHU_F2, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LIH, WHU_F4, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LIIH, KC_NO, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RIIH, KC_PSCR, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RIH, WHU_F5, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RMH, WHU_F3, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RRH, WHU_F1, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RLH, WHU_F7, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_ROLH, KC_NO, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LOLB, WHU_DEL, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LLB, WHU_F12, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LRB, WHU_EXCL, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LMB, WHU_AT, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LIB, WHU_F8, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LIIB, KC_NO, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RIIB, KC_PAUS, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RIB, WHU_F9, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RMB, WHU_CARET, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RRB, WHU_UNDER, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RLB, WHU_F11, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_ROLB, WHU_ENT, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LITH, KC_NO, WHU_LMOD)
        PROCESS_RECORD_CASE(WHU_FUN_LTH, WHU_HBDC_LTH, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_LOTH, KC_NO, SYSTEM)
        PROCESS_RECORD_CASE(WHU_FUN_ROTH, WHU_BSPC, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RTH, WHU_SPACE, WHU_BASE)
        PROCESS_RECORD_CASE(WHU_FUN_RITH, WHU_O_DIARESIS, WHU_BASE)
        /*
  case U_ACUTE_WEN:
      if (record->event.pressed) {
          SEND_STRING("]");
      }
      layer_move(WHU_BASE);
      return false;
  case M_STAR_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("/"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_PRCNT_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_LSFT("5"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_AT_WEN:
      if (record->event.pressed) {
         SEND_STRING(SS_RALT("v"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_COMMA_WEN:
      if (record->event.pressed) {
          SEND_STRING(",");
      }
      layer_move(WHU_BASE);
      return false;
  case E_ACUTE_WEN:
      if (record->event.pressed) {
          SEND_STRING(";");
      }
      layer_move(WHU_BASE);
      return false;
  case I_ACUTE_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_NUBS));
      }
      layer_move(WHU_BASE);
      return false;
  case O_ACUTE_WEN:
      if (record->event.pressed) {
          SEND_STRING("=");
      }
      layer_move(WHU_BASE);
      return false;
  case M_LT_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT(SS_TAP(X_NUBS)));
      }
      layer_move(WHU_BASE);
      return false;
  case M_LBRC_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("b"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_LBKT_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("f"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_LPAR_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_LSFT("8"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_BSLH_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("q"));
      }
      layer_move(WHU_BASE);
      return false;
  case A_ACUTE_WEN:
      if (record->event.pressed) {
          SEND_STRING("'");
      }
      layer_move(WHU_BASE);
      return false;
  case M_SQT_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_LSFT("1"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_DQT_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_LSFT("2"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_DOT_WEN:
      if (record->event.pressed) {
          SEND_STRING(".");
      }
      layer_move(WHU_BASE);
      return false;
  case M_GRAVE_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("7"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_TILDE_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("1"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_PLUS_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_LSFT("3"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_RPAR_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_LSFT("9"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_RBKT_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("g"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_RBRC_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("n"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_GT_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("z"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_LC_BSPC_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_LCTL(SS_TAP(X_BSPC)));
      }
      layer_move(WHU_BASE);
      return false;
  case M_BSPC_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_BSPC));
      }
      layer_move(WHU_BASE);
      return false;
  case M_RET_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_ENT));
      }
      layer_move(WHU_BASE);
      return false;
  case M_TAB_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_TAB));
      }
      layer_move(WHU_BASE);
      return false;
  case M_DEL_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_DEL));
      }
      layer_move(WHU_BASE);
      return false;
  case M_ESC_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_ESC));
      }
      layer_move(WHU_BASE);
      return false;
  case U_DACUTE_WEN:
      if (record->event.pressed) {
          SEND_STRING("\\");
      }
      layer_move(WHU_BASE);
      return false;
  case M_EQUAL_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_LSFT("7"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_CARET_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("3"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_HASH_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("x"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_EXCL_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_LSFT("4"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_SEMI_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT(","));
      }
      layer_move(WHU_BASE);
      return false;
  case M_FSLH_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_LSFT("6"));
      }
      layer_move(WHU_BASE);
      return false;
  case O_DACUTE_WEN:
      if (record->event.pressed) {
          SEND_STRING("[");
      }
      layer_move(WHU_BASE);
      return false;
  case U_DIARESIS_WEN:
      if (record->event.pressed) {
          SEND_STRING("-");
      }
      layer_move(WHU_BASE);
      return false;
  case M_PIPE_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("w"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_AMPS_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT("c"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_DLLR_WEN:
      if (record->event.pressed) {
          SEND_STRING(SS_RALT(";"));
      }
      layer_move(WHU_BASE);
      return false;
  case M_MINUS_WEN:
      if (record->event.pressed) {
          SEND_STRING("/");
      }
      layer_move(WHU_BASE);
      return false;
  case M_QMARK_WEN:
      if (record->event.pressed) {
          SEND_STRING("<");
      }
      layer_move(WHU_BASE);
      return false;
  case M_COLON_WEN:
      if (record->event.pressed) {
          SEND_STRING(">");
      }
      layer_move(WHU_BASE);
      return false;
  case O_DIARESIS_WEN:
      if (record->event.pressed) {
          SEND_STRING("0");
      }
      layer_move(WHU_BASE);
      return false;
  case M_UNDER_WEN:
      if (record->event.pressed) {
          SEND_STRING("?");
      }
      layer_move(WHU_BASE);
      return false;*/
  default:
      return true;
  }
}

#endif // OLED_ENABLE
