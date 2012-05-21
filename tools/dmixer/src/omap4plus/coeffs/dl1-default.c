/*

  This file is provided under a dual BSD/GPLv2 license.  When using or
  redistributing this file, you may do so under either license.

  GPL LICENSE SUMMARY

  Copyright(c) 2010-2011 Texas Instruments Incorporated,
  All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
  The full GNU General Public License is included in this distribution
  in the file called LICENSE.GPL.

  BSD LICENSE

  Copyright(c) 2010-2011 Texas Instruments Incorporated,
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the
      distribution.
    * Neither the name of Texas Instruments Incorporated nor the names of
      its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/*
 * Default Coefficients for DL1EQ.
 */

#ifndef _DL1_COEFFS_H
#define _DL1_COEFFS_H

#define DL1_COEFF		25

const int32_t dl1_equ_coeffs[][DL1_COEFF] = {
/* Flat response with Gain =1 */
				{0, 0, 0, 0, 0,
				0, 0, 0, 0, 0,
				0, 0, 0x040002, 0, 0,
				0, 0, 0, 0, 0,
				0, 0, 0, 0, 0},

/* 800Hz cut-off frequency and Gain = 1  */
				{0, 0, 0, 0, 0, 0, 0, 0, 0, -7554223,
				708210, -708206, 7554225, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 6802833, -682266, 731554},

/* 800Hz cut-off frequency and Gain = 0.25 */
				{0, 0, 0, 0, 0, 0, 0, 0, 0, -3777112,
				5665669, -5665667, 3777112, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 6802833, -682266, 731554},

/* 800Hz cut-off frequency and Gain = 0.1 */
				{0, 0, 0, 0, 0, 0, 0, 0, 0, -1510844,
				4532536, -4532536, 1510844, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 6802833, -682266, 731554},
/* 4kHz LPF filter */
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0x0002e630,
				0x0008b290, 0x0008b290, 0x0002e630,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0x0058ae58, 0xfffa666a, 0x0007da1e},
};

#define DL1_EQU_NAME "DL1 Equalizer"
#define DL1_EQU_TEXTS \
				"Flat response",\
				"High-pass 0dB",\
				"High-pass -12dB",\
				"High-pass -20dB",\
				"4Khz LPF   0dB",

#endif

