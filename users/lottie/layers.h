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

#pragma once

// Naming convention
// ---
// First letter:
//   w -> windows
//   l -> linux
//   m -> mac
// 2nd and 3rd letter:
//   en -> US International
//   hu -> Hungarian
//
// dacute -> double acute
// cap -> capital

// LAYERS FOR WIN-ENGLISH-QUERTY HOST (WEN)
//
#define SYSTEM    0

// BUNYA-DTM LAYOUT LAYERS FOR WIN-HUNGARIAN-QUERTZ HOST (WHU)

#define WHU_BASE 1
#define WHU_LMOD 2 // Left modifiers
#define WHU_RMOD 3 // Right modifiers
#define WHU_NAV 4
#define WHU_NUM 5
#define WHU_FUN 6
#define WHU_NPAD 7
