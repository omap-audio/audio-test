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
 * Default Coefficients for DL2


/*
 * Coefficients for DL2EQ_L
 */

#define DL2L_COEFF	25

const int32_t dl2l_equ_coeffs[][DL2L_COEFF] = {
/* Flat response with Gain =1 */
				{0, 0, 0, 0, 0,
				0, 0, 0, 0, 0,
				0, 0, 0x040002, 0, 0,
				0, 0, 0, 0, 0,
				0, 0, 0, 0, 0},

/* 800Hz cut-off frequency and Gain = 1 */
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
/* 450Hz High pass and Gain = 1 */
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				8046381, -502898, 8046381, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0,-7718119, 502466},
};

/*
 * Coefficients for DL2_EQ_R
 */

#define DL2R_COEFF	25

const int32_t dl2r_equ_coeffs[][DL2R_COEFF] = {
/* Flat response with Gain =1 */
				{0, 0, 0, 0, 0,
				0, 0, 0, 0, 0,
				0, 0, 0x040002, 0, 0,
				0, 0, 0, 0, 0,
				0, 0, 0, 0, 0},

/* 800Hz cut-off frequency and Gain = 1 */
				{0, 0, 0, 0, 0, 0, 0, 0, 0, -7554223,
				708210, -708206, 7554225, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 6802833, -682266, 731554},

/*800Hz cut-off frequency and Gain = 0.25 */
				{0, 0, 0, 0, 0, 0, 0, 0, 0, -3777112,
				5665669, -5665667, 3777112, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 6802833, -682266, 731554},

/* 800Hz cut-off frequency and Gain = 0.1 */
				{0, 0, 0, 0, 0, 0, 0, 0, 0, -1510844,
				4532536, -4532536, 1510844, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 6802833, -682266, 731554},
/* 450Hz High pass and Gain = 1 */
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				8046381, -502898, 8046381, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0,-7718119, 502466},
};

/*
 * Coefficients for DMICEQ
 */

#define DMIC_COEFF	19

const int32_t dmic_equ_coeffs[][DMIC_COEFF] = {
/* 20kHz cut-off frequency and Gain = 1 */
				{-4119413, -192384, -341428, -348088,
				-151380, 151380, 348088, 341428, 192384,
				4119419, 1938156, -6935719, 775202,
				-1801934, 2997698, -3692214, 3406822,
				-2280190, 1042982},

/* 20kHz cut-off frequency and Gain = 0.25 */
				{-1029873, -3078121, -5462817, -5569389,
				-2422069, 2422071, 5569391, 5462819,
				3078123, 1029875, 1938188, -6935811,
				775210, -1801950, 2997722, -3692238,
				3406838, -2280198, 1042982},

/* 20kHz cut-off frequency and Gain = 0.125 */
				{-514937, -1539061, -2731409, -2784693,
				-1211033, 1211035, 2784695, 2731411,
				1539063, 514939, 1938188, -6935811,
				775210, -1801950, 2997722, -3692238,
				3406838, -2280198, 1042982},
};

/*
 * Coefficients for AMICEQ
 */

#define AMIC_COEFF	19

const int32_t amic_equ_coeffs[][AMIC_COEFF] = {
/* 20kHz cut-off frequency and Gain = 1 */
				{-4119413, -192384, -341428, -348088,
				-151380, 151380, 348088, 341428, 192384,
				4119419, 1938156, -6935719, 775202,
				-1801934, 2997698, -3692214, 3406822,
				-2280190, 1042982},
/* 20kHz cut-off frequency and Gain = 0.25 */
				{-1029873, -3078121, -5462817, -5569389,
				-2422069, 2422071, 5569391, 5462819,
				3078123, 1029875, 1938188, -6935811,
				775210, -1801950, 2997722, -3692238,
				3406838, -2280198, 1042982},

/* 20kHz cut-off frequency and Gain = 0.125 */
				{-514937, -1539061, -2731409, -2784693,
				-1211033, 1211035, 2784695, 2731411,
				1539063, 514939, 1938188, -6935811,
				775210, -1801950, 2997722, -3692238,
				3406838, -2280198, 1042982},
};


/*
 * Coefficients for SDTEQ
 */

#define SDT_COEFF	9

const int32_t sdt_equ_coeffs[][SDT_COEFF] = {
/* Flat response with Gain =1 */
				{0, 0, 0, 0, 0x040002, 0, 0, 0, 0},

/* 800Hz cut-off frequency and Gain = 1  */
				{0, -7554223, 708210, -708206, 7554225,
				0, 6802833, -682266, 731554},

/* 800Hz cut-off frequency and Gain = 0.25 */
				{0, -3777112, 5665669, -5665667, 3777112,
				0, 6802833, -682266, 731554},

/* 800Hz cut-off frequency and Gain = 0.1 */
				{0, -1510844, 4532536, -4532536, 1510844,
				0, 6802833, -682266, 731554}
};

