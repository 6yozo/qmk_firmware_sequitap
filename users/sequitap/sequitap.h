// Copyright 2023 Gyozo Gaspar
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

#pragma once

#define MAKE_LAYOUT_ARGUMENT(HOST, LAYER) \
    HOST##_##LAYER##_LOLT, HOST##_##LAYER##_LLT, HOST##_##LAYER##_LRT, HOST##_##LAYER##_LMT,  HOST##_##LAYER##_LIT, HOST##_##LAYER##_LIIT, HOST##_##LAYER##_RIIT, HOST##_##LAYER##_RIT, HOST##_##LAYER##_RMT, HOST##_##LAYER##_RRT, HOST##_##LAYER##_RLT, HOST##_##LAYER##_ROLT, \
    HOST##_##LAYER##_LOLH, HOST##_##LAYER##_LLH, HOST##_##LAYER##_LRH, HOST##_##LAYER##_LMH,  HOST##_##LAYER##_LIH, HOST##_##LAYER##_LIIH, HOST##_##LAYER##_RIIH, HOST##_##LAYER##_RIH, HOST##_##LAYER##_RMH, HOST##_##LAYER##_RRH, HOST##_##LAYER##_RLH, HOST##_##LAYER##_ROLH, \
    HOST##_##LAYER##_LOLB, HOST##_##LAYER##_LLB, HOST##_##LAYER##_LRB, HOST##_##LAYER##_LMB,  HOST##_##LAYER##_LIB, HOST##_##LAYER##_LIIB, HOST##_##LAYER##_RIIB, HOST##_##LAYER##_RIB, HOST##_##LAYER##_RMB, HOST##_##LAYER##_RRB, HOST##_##LAYER##_RLB, HOST##_##LAYER##_ROLB, \
                                                                       HOST##_##LAYER##_LITH, HOST##_##LAYER##_LTH, HOST##_##LAYER##_LOTH, HOST##_##LAYER##_ROTH, HOST##_##LAYER##_RTH, HOST##_##LAYER##_RITH

#define MAKE_LAYOUT(LAYOUT_ARGUMENT)  LAYOUT_split_3x6_3(LAYOUT_ARGUMENT)
#define MAKE_LAYER(HOST, LAYER)  MAKE_LAYOUT(MAKE_LAYOUT_ARGUMENT(HOST, LAYER))

#define PROCESS_RECORD_CASE(KEY, KEY_CODE, LAYER)   \
    case KEY:                                       \
        if (record->event.pressed) {                \
            tap_code16(KEY_CODE);                   \
            layer_move(LAYER);                      \
        }                                           \
        return false;

#define PROCESS_RECORD_CASE2(KEY, STRING_TO_SEND, KEY_CODE, LAYER)  \
    case KEY:                                                       \
        if (record->event.pressed) {                                \
            SEND_STRING(SS_RALT("3"));                              \
            tap_code16(KEY_CODE);                                   \
            layer_move(LAYER);                                      \
        }                                                           \
        return false;
        
#define PROCESS_RECORD_CASE_CW(KEY, LAYER)      \
    case KEY:                                   \
    if (record->event.pressed) {                \
        caps_word_on();                         \
        layer_move(LAYER);                      \
    }                                           \
    return false;

//Implemented in Layout: PROCESS_RECORD_CASE(WHU_LMOD_LLH, OSM(MOD_LGUI), WHU_BASE)
//Implemented in Layout: PROCESS_RECORD_CASE(WHU_LMOD_LRH, OSM(MOD_LALT), WHU_BASE)
//Implemented in Layout: PROCESS_RECORD_CASE(WHU_LMOD_LMH, OSM(MOD_LCTL), WHU_BASE)
//Implemented in Layout: PROCESS_RECORD_CASE(WHU_LMOD_LIH, OSM(MOD_LSFT), WHU_BASE)
//Implemented in Layout: WHU_RMOD_RIH
//Implemented in Layout: WHU_RMOD_RMH
//Implemented in Layout: WHU_RMOD_RRH
//Implemented in Layout: WHU_RMOD_RLH
#define RECORD_CASES(PREFIX) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LOLT, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LLT, PREFIX##_ESC, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LRT, PREFIX##_TAB, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LMT, PREFIX##_ENT, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LIT, PREFIX##_DEL, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LIIT, PREFIX##_APP, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RIIT, PREFIX##_HBDC_RIIT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RIT, PREFIX##_HBDC_RIT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RMT, PREFIX##_HBDC_RMT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RRT, PREFIX##_HBDC_RRT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RLT, PREFIX##_HBDC_RLT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_ROLT, PREFIX##_HBDC_ROLT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LOLH, PREFIX##_O_DACUTE, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LIIH, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RIIH, PREFIX##_HBDC_RIIH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RIH, PREFIX##_HBDC_RIH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RMH, PREFIX##_HBDC_RMH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RRH, PREFIX##_HBDC_RRH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RLH, PREFIX##_HBDC_RLH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_ROLH, KC_NO, PREFIX##_NUM) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LOLB, PREFIX##_U_DACUTE, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LLB, PREFIX##_UNDO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LRB, PREFIX##_CUT, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LMB, PREFIX##_COPY, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LIB, PREFIX##_PASTE, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LIIB, PREFIX##_AGAIN, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RIIB, PREFIX##_HBDC_RIIB, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RIB, PREFIX##_HBDC_RIB, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RMB, PREFIX##_HBDC_RMB, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RRB, PREFIX##_HBDC_RRB, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RLB, PREFIX##_HBDC_RLB, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_ROLB, KC_NO, PREFIX##_FUN) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LITH, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LTH, PREFIX##_HBDC_LTH, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_LOTH, KC_NO, SYSTEM) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_ROTH, PREFIX##_HBDC_ROTH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RTH, PREFIX##_HBDC_RTH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_LMOD_RITH, KC_NO, PREFIX##_NAV) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LOLT, PREFIX##_HBDC_LOLT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LLT, PREFIX##_HBDC_LLT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LRT, PREFIX##_HBDC_LRT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LMT, PREFIX##_HBDC_LMT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LIT, PREFIX##_HBDC_LIT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LIIT, PREFIX##_HBDC_LIIT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_RIIT, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_RIT, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_RMT, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_RRT, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_RLT, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_ROLT, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LOLH, KC_NO, PREFIX##_NUM) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LLH, PREFIX##_HBDC_LLH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LRH, PREFIX##_HBDC_LRH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LMH, PREFIX##_HBDC_LMH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LIH, PREFIX##_HBDC_LIH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LIIH, PREFIX##_HBDC_LIIH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE_CW(PREFIX##_RMOD_RIIH, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_ROLH, PREFIX##_O_DIARESIS, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LOLB, KC_NO, PREFIX##_FUN) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LLB, PREFIX##_HBDC_LLB, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LRB, PREFIX##_HBDC_LRB, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LMB, PREFIX##_HBDC_LMB, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LIB, PREFIX##_HBDC_LIB, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LIIB, PREFIX##_HBDC_LIIB, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_RIIB, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_RIB, KC_NO , last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_RMB, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_RRB, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_RLB, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_ROLB, PREFIX##_U_DIARESIS, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LITH, KC_NO, PREFIX##_NAV) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LTH, PREFIX##_HBDC_LTH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_LOTH, KC_NO, SYSTEM) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_ROTH, PREFIX##_HBDC_ROTH, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_RTH, PREFIX##_HBDC_RTH, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_RMOD_RITH, KC_NO, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LOLT, KC_NO, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LLT, PREFIX##_AMPS, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LRT, PREFIX##_LT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LMT, PREFIX##_LBRC, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LIT, PREFIX##_EQUAL, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LIIT, PREFIX##_SEMI, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RIIT, PREFIX##_COLON, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RIT, PREFIX##_DQT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RMT, PREFIX##_RBRC, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RRT, PREFIX##_GT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RLT, PREFIX##_DOT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_ROLT, KC_NO, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LOLH, KC_NO, PREFIX##_NPAD) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LLH, PREFIX##_N6, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LRH, PREFIX##_N0, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LMH, PREFIX##_N2, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LIH, PREFIX##_N4, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LIIH, PREFIX##_STAR, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RIIH, PREFIX##_FSLH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RIH, PREFIX##_N5, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RMH, PREFIX##_N3, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RRH, PREFIX##_N1, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RLH, PREFIX##_N7, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_ROLH, KC_NO, PREFIX##_NPAD) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LOLB, KC_NO, PREFIX##_FUN) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LLB, PREFIX##_PIPE, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LRB, PREFIX##_LBKT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LMB, PREFIX##_RBKT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LIB, PREFIX##_N8, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LIIB, PREFIX##_PLUS, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RIIB, PREFIX##_MINUS, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RIB, PREFIX##_N9, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RMB, PREFIX##_LPAR, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RRB, PREFIX##_RPAR, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RLB, PREFIX##_COMMA, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_ROLB, KC_NO, PREFIX##_FUN) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LITH, PREFIX##_O_DACUTE, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LTH, PREFIX##_HBDC_LTH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_LOTH, KC_NO, SYSTEM) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_ROTH, PREFIX##_BSPC, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RTH, PREFIX##_SPACE, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_NUM_RITH, PREFIX##_O_DIARESIS, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LOLT, KC_NO, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LLT, PREFIX##_PRCNT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LRT, PREFIX##_TILDE, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LMT, PREFIX##_DLLR, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LIT, PREFIX##_GRAVE, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LIIT, PREFIX##_PSCR, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RIIT, PREFIX##_SCRL, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RIT, PREFIX##_SQT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RMT, PREFIX##_BSLH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RRT, PREFIX##_QMARK, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RLT, PREFIX##_HASH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_ROLT, KC_NO, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LOLH, KC_NO, PREFIX##_NUM) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LLH, PREFIX##_F6, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LRH, PREFIX##_F10, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LMH, PREFIX##_F2, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LIH, PREFIX##_F4, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LIIH, KC_NO, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RIIH, KC_NO, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RIH, PREFIX##_F5, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RMH, PREFIX##_F3, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RRH, PREFIX##_F1, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RLH, PREFIX##_F7, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_ROLH, KC_NO, PREFIX##_NUM) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LOLB, KC_NO, PREFIX##_MOUSE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LLB, PREFIX##_F12, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LRB, PREFIX##_EXCL, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LMB, PREFIX##_AT, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LIB, PREFIX##_F8, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LIIB, KC_NO, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RIIB, PREFIX##_PAUS, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RIB, PREFIX##_F9, PREFIX##_BASE) \
    PREFIX##_PROCESS_RECORD_CASE_CARET(PREFIX##_FUN_RMB, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RRB, PREFIX##_UNDER, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RLB, PREFIX##_F11, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_ROLB, KC_NO, PREFIX##_MOUSE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LITH, PREFIX##_U_DACUTE, last_permanent_layer) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LTH, PREFIX##_HBDC_LTH, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_LOTH, KC_NO, SYSTEM) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_ROTH, PREFIX##_BSPC, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RTH, PREFIX##_SPACE, PREFIX##_BASE) \
    PROCESS_RECORD_CASE(PREFIX##_FUN_RITH, PREFIX##_U_DIARESIS, last_permanent_layer)

// There is only a single System layer. It is language independent.

#define ALL_SYS_LOLT KC_NO
#define ALL_SYS_LLT  KC_NO
#define ALL_SYS_LRT  TO(MHU_BASE)
#define ALL_SYS_LMT  TO(LHU_BASE)
#define ALL_SYS_LIT  TO(WHU_BASE)
#define ALL_SYS_LIIT KC_MS_ACCEL0
#define ALL_SYS_RIIT RGB_TOG
#define ALL_SYS_RIT  RGB_MOD
#define ALL_SYS_RMT  RGB_HUI
#define ALL_SYS_RRT  RGB_SAI
#define ALL_SYS_RLT  RGB_VAI
#define ALL_SYS_ROLT KC_NO
#define ALL_SYS_LOLH KC_NO
#define ALL_SYS_LLH  KC_NO
#define ALL_SYS_LRH  KC_NO
#define ALL_SYS_LMH  KC_NO
#define ALL_SYS_LIH  KC_NO
#define ALL_SYS_LIIH KC_MS_ACCEL1
#define ALL_SYS_RIIH KC_NO
#define ALL_SYS_RIH  KC_VOLD
#define ALL_SYS_RMH  KC_MUTE
#define ALL_SYS_RRH  KC_VOLU
#define ALL_SYS_RLH  KC_NO
#define ALL_SYS_ROLH KC_NO
#define ALL_SYS_LOLB KC_NO
#define ALL_SYS_LLB  KC_NO
#define ALL_SYS_LRB  KC_NO
#define ALL_SYS_LMB  KC_NO
#define ALL_SYS_LIB  KC_NO
#define ALL_SYS_LIIB KC_MS_ACCEL2
#define ALL_SYS_RIIB KC_NO
#define ALL_SYS_RIB  KC_MPLY
#define ALL_SYS_RMB  KC_MPRV
#define ALL_SYS_RRB  KC_MNXT
#define ALL_SYS_RLB  KC_MSTP
#define ALL_SYS_ROLB KC_NO
#define ALL_SYS_LITH KC_NO
#define ALL_SYS_LTH  KC_NO
#define ALL_SYS_LOTH KC_NO
#define ALL_SYS_ROTH KC_NO
#define ALL_SYS_RTH  KC_NO
#define ALL_SYS_RITH KC_NO
