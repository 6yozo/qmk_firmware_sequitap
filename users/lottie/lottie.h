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
    HOST##_##LAYER##_LOLH, HOST##_##LAYER##_LLH, HOST##_##LAYER##_LRH,  HOST##_##LAYER##_LMH,  HOST##_##LAYER##_LIH, HOST##_##LAYER##_LIIH, HOST##_##LAYER##_RIIH, HOST##_##LAYER##_RIH, HOST##_##LAYER##_RMH, HOST##_##LAYER##_RRH, HOST##_##LAYER##_RLH, HOST##_##LAYER##_ROLH, \
    HOST##_##LAYER##_LOLB, HOST##_##LAYER##_LLB, HOST##_##LAYER##_LRB,  HOST##_##LAYER##_LMB,  HOST##_##LAYER##_LIB, HOST##_##LAYER##_LIIB, HOST##_##LAYER##_RIIB, HOST##_##LAYER##_RIB, HOST##_##LAYER##_RMB, HOST##_##LAYER##_RRB, HOST##_##LAYER##_RLB, HOST##_##LAYER##_ROLB, \
        HOST##_##LAYER##_LITH, HOST##_##LAYER##_LTH, HOST##_##LAYER##_LOTH, HOST##_##LAYER##_ROTH, HOST##_##LAYER##_RTH, HOST##_##LAYER##_RITH

#define MAKE_LAYOUT(LAYOUT_ARGUMENT)  LAYOUT_split_3x6_3(LAYOUT_ARGUMENT)
#define MAKE_LAYER(HOST, LAYER)  MAKE_LAYOUT(MAKE_LAYOUT_ARGUMENT(HOST, LAYER))

// There is only a single System layer. It is language independent.

#define ALL_SYS_LOLT KC_NO
#define ALL_SYS_LLT  KC_NO
#define ALL_SYS_LRT  KC_NO
#define ALL_SYS_LMT  KC_NO
#define ALL_SYS_LIT  TO(WHU_BASE)
#define ALL_SYS_LIIT KC_NO
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
#define ALL_SYS_LIIH KC_NO
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
#define ALL_SYS_LIIB KC_NO
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
