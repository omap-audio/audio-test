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
 * Default Coefficients for amicEQ.
 * Please submit new coefficients upstream.
 */

#include <abegen.h>

/* 20kHz cut-off frequency and Gain = 1 */
static const int32_t amic_20kHz_0dB_coeffs[] = {
	-4119413, -192384, -341428, -348088,
	-151380, 151380, 348088, 341428, 192384,
	4119419, 1938156, -6935719, 775202,
	-1801934, 2997698, -3692214, 3406822,
	-2280190, 1042982
};

/* 20kHz cut-off frequency and Gain = 0.25 */
static const int32_t amic_20kHz_m12db_coeffs[] = {
	-1029873, -3078121, -5462817, -5569389,
	-2422069, 2422071, 5569391, 5462819,
	3078123, 1029875, 1938188, -6935811,
	775210, -1801950, 2997722, -3692238,
	3406838, -2280198, 1042982,
};

/* 20kHz cut-off frequency and Gain = 0.125 */
static const int32_t amic_20kHz_m15db_coeffs[] = {
	-514937, -1539061, -2731409, -2784693,
	-1211033, 1211035, 2784695, 2731411,
	1539063, 514939, 1938188, -6935811,
	775210, -1801950, 2997722, -3692238,
	3406838, -2280198, 1042982,
};

static struct abe_coeff_elem elems[] = {
	ABE_COEFF("20kHz LPF 0dB", amic_20kHz_0dB_coeffs),
	ABE_COEFF("20kHz LPF -12dB", amic_20kHz_m12db_coeffs),
	ABE_COEFF("20kHz LPF -15dB", amic_20kHz_m15db_coeffs),
};

struct abe_coeff coeffs = {
	.description	= "amic Equalizer",
	.count		= ARRAY_SIZE(elems),
	.coeff		= elems,
};
