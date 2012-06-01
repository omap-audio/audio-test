/*
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
 */
#include <abegen.h>

/* Flat response with Gain =1 */
static const int32_t dl2r_flat_coeffs[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0x040002, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0,
};

/* 800Hz cut-off frequency and Gain = 1  */
static const int32_t dl2r_800Hz_0db_coeffs[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, -7554223,
	708210, -708206, 7554225, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 6802833, -682266, 731554,
};

/* 800Hz cut-off frequency and Gain = 0.25  */
static const int32_t dl2r_800Hz_m12db_coeffs[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, -3777112,
	5665669, -5665667, 3777112, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 6802833, -682266, 731554,
};

/* 800Hz cut-off frequency and Gain = 0.1  */
static const int32_t dl2r_800Hz_m20db_coeffs[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, -1510844,
	4532536, -4532536, 1510844, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 6802833, -682266, 731554,
};

/* 450Hz High pass and Gain = 1 */
static const int32_t dl2r_450Hz_0db_coeffs[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	8046381, -502898, 8046381, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,-7718119, 502466,
};

static struct abe_coeff_elem elems[] = {
	ABE_COEFF("Flat Response", dl2r_flat_coeffs),
	ABE_COEFF("800Hz HPF 0dB", dl2r_800Hz_0db_coeffs),
	ABE_COEFF("800Hz HPF -12dB", dl2r_800Hz_m12db_coeffs),
	ABE_COEFF("800Hz HPF -20dB", dl2r_800Hz_m20db_coeffs),
	ABE_COEFF("450Hz HPF 0dB", dl2r_450Hz_0db_coeffs),	
};

struct abe_coeff coeffs = {
	.description	= "DL2 Left Equalizer",
	.count		= ARRAY_SIZE(elems),
	.coeff		= elems,
};

