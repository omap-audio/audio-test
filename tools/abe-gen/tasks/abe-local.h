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

#ifndef _ABE_H_
#define _ABE_H_

#include "../abe/abe_hal/abe_def.h"
#include "abe_typ.h"
#include "../abe/abe_hal/abe_ext.h"

/*
 * OS DEPENDENT MMU CONFIGURATION
 */
#define ABE_PMEM_BASE_OFFSET_MPU	0xe0000
#define ABE_CMEM_BASE_OFFSET_MPU	0xa0000
#define ABE_SMEM_BASE_OFFSET_MPU	0xc0000
#define ABE_DMEM_BASE_OFFSET_MPU	0x80000
#define ABE_ATC_BASE_OFFSET_MPU		0xf1000
/* default base address for io_base */
#define ABE_DEFAULT_BASE_ADDRESS_L3 0x49000000L
#define ABE_DEFAULT_BASE_ADDRESS_L4 0x40100000L
#define ABE_DEFAULT_BASE_ADDRESS_DEFAULT ABE_DEFAULT_BASE_ADDRESS_L3

/*
 * TODO: These structures, enums and port ID macros should be moved to the
 * new public ABE API header.
 */

/* Logical PORT IDs - Backend */
#define OMAP_ABE_BE_PORT_DMIC0			0
#define OMAP_ABE_BE_PORT_DMIC1			1
#define OMAP_ABE_BE_PORT_DMIC2			2
#define OMAP_ABE_BE_PORT_PDM_DL1		3
#define OMAP_ABE_BE_PORT_PDM_DL2		4
#define OMAP_ABE_BE_PORT_PDM_VIB		5
#define OMAP_ABE_BE_PORT_PDM_UL1		6
#define OMAP_ABE_BE_PORT_BT_VX_DL		7
#define OMAP_ABE_BE_PORT_BT_VX_UL		8
#define OMAP_ABE_BE_PORT_MM_EXT_UL		9
#define OMAP_ABE_BE_PORT_MM_EXT_DL		10

/* Logical PORT IDs - Frontend */
#define OMAP_ABE_FE_PORT_MM_DL1		11
#define OMAP_ABE_FE_PORT_MM_UL1		12
#define OMAP_ABE_FE_PORT_MM_UL2		13
#define OMAP_ABE_FE_PORT_VX_DL		14
#define OMAP_ABE_FE_PORT_VX_UL		15
#define OMAP_ABE_FE_PORT_VIB		16
#define OMAP_ABE_FE_PORT_TONES		17
#define OMAP_ABE_FE_PORT_MM_DL_LP	18

#define OMAP_ABE_MAX_PORT_ID	OMAP_ABE_FE_PORT_MM_DL_LP

/* ABE copy function IDs */
#define OMAP_AESS_COPY_FCT_NULL_ID			0
#define OMAP_AESS_COPY_FCT_S2D_STEREO_16_16_ID		1
#define OMAP_AESS_COPY_FCT_S2D_MONO_MSB_ID		2
#define OMAP_AESS_COPY_FCT_S2D_STEREO_MSB_ID		3
#define OMAP_AESS_COPY_FCT_S2D_STEREO_RSHIFTED_16_ID	4
#define OMAP_AESS_COPY_FCT_S2D_MONO_RSHIFTED_16_ID	5
#define OMAP_AESS_COPY_FCT_D2S_STEREO_16_16_ID		6
#define OMAP_AESS_COPY_FCT_D2S_MONO_MSB_ID		7
#define OMAP_AESS_COPY_FCT_D2S_MONO_RSHIFTED_16_ID	8
#define OMAP_AESS_COPY_FCT_D2S_STEREO_RSHIFTED_16_ID	9
#define OMAP_AESS_COPY_FCT_D2S_STEREO_MSB_ID		10
#define OMAP_AESS_COPY_FCT_DMIC_ID			11
#define OMAP_AESS_COPY_FCT_MCPDM_DL_ID			12
#define OMAP_AESS_COPY_FCT_MM_UL_ID			13
#define OMAP_AESS_COPY_FCT_SPLIT_SMEM_ID		14
#define OMAP_AESS_COPY_FCT_MERGE_SMEM_ID		15
#define OMAP_AESS_COPY_FCT_SPLIT_TDM_ID			16
#define OMAP_AESS_COPY_FCT_MERGE_TDM_ID			17
#define OMAP_AESS_COPY_FCT_ROUTE_MM_UL_ID		18
#define OMAP_AESS_COPY_FCT_IO_IP_ID			19
#define OMAP_AESS_COPY_FCT_COPY_UNDERFLOW_ID		20
#define OMAP_AESS_COPY_FCT_COPY_MCPDM_DL_HF_PDL1_ID	21
#define OMAP_AESS_COPY_FCT_COPY_MCPDM_DL_HF_PDL2_ID	22
#define OMAP_AESS_COPY_FCT_S2D_MONO_16_16_ID		23
#define OMAP_AESS_COPY_FCT_D2S_MONO_16_16_ID		24
#define OMAP_AESS_COPY_FCT_DMIC_NO_PRESCALE_ID		25

#define OMAP_AESS_COPY_FCT_ID_SIZE		(OMAP_AESS_COPY_FCT_DMIC_NO_PRESCALE_ID + 1)

/* ABE buffer IDs */
#define OMAP_AESS_BUFFER_ZERO_ID		0
#define OMAP_AESS_BUFFER_DMIC1_L_ID		1
#define OMAP_AESS_BUFFER_DMIC1_R_ID		2
#define OMAP_AESS_BUFFER_DMIC2_L_ID		3
#define OMAP_AESS_BUFFER_DMIC2_R_ID		4
#define OMAP_AESS_BUFFER_DMIC3_L_ID		5
#define OMAP_AESS_BUFFER_DMIC3_R_ID		6
#define OMAP_AESS_BUFFER_BT_UL_L_ID		7
#define OMAP_AESS_BUFFER_BT_UL_R_ID		8
#define OMAP_AESS_BUFFER_MM_EXT_IN_L_ID		9
#define OMAP_AESS_BUFFER_MM_EXT_IN_R_ID		10
#define OMAP_AESS_BUFFER_AMIC_L_ID		11
#define OMAP_AESS_BUFFER_AMIC_R_ID		12
#define OMAP_AESS_BUFFER_VX_REC_L_ID		13
#define OMAP_AESS_BUFFER_VX_REC_R_ID		14
#define OMAP_AESS_BUFFER_MCU_IRQ_FIFO_PTR_ID	15
#define OMAP_AESS_BUFFER_DMIC_ATC_PTR_ID	16
#define OMAP_AESS_BUFFER_MM_EXT_IN_ID		17

#define OMAP_AESS_BUFFER_ID_SIZE		(OMAP_AESS_BUFFER_MM_EXT_IN_ID + 1)

#define OMAP_ABE_D_MCUIRQFIFO_SIZE	0x40

#define ARRAY_SIZE(x)	(sizeof(x) / sizeof(x[0]))

/* ports can either be enabled or disabled */
enum port_state {
	PORT_DISABLED = 0,
	PORT_ENABLED,
};

struct omap_aess_mapping {
	const struct omap_aess_addr *map;
	u32 map_count;

	const int *fct_id;
	u32 fct_count;

	const int *label_id;
	u32 label_count;

	const struct omap_aess_init_task *init_table;
	u32 table_count;

	const struct omap_aess_port *port;
	u32 port_count;

	const struct omap_aess_port *ping_pong;
	const struct omap_aess_task *dl1_mono_mixer;
	const struct omap_aess_task *dl2_mono_mixer;
	const struct omap_aess_task *audul_mono_mixer;
};

struct omap_aess_seq {
	u32 write_pointer;
	u32 irq_pingpong_player_id;
};

/* main ABE structure */
struct omap_aess {
	int io_base[5];
	u32 firmware_version_number;
	u16 MultiFrame[25][8];
	u32 compensated_mixer_gain;
	u8  muted_gains_indicator[MAX_NBGAIN_CMEM];
	u32 desired_gains_decibel[MAX_NBGAIN_CMEM];
	u32 muted_gains_decibel[MAX_NBGAIN_CMEM];
	u32 desired_gains_linear[MAX_NBGAIN_CMEM];
	u32 desired_ramp_delay_ms[MAX_NBGAIN_CMEM];
	int pp_buf_id;
	int pp_buf_id_next;
	int pp_buf_addr[4];
	int pp_first_irq;
	u32 warm_boot;

	/* base addresses of the ping pong buffers in bytes addresses */
	u32 base_address_pingpong[MAX_PINGPONG_BUFFERS];
	/* size of each ping/pong buffers */
	u32 size_pingpong;
	/* number of ping/pong buffer being used */
	u32 nb_pingpong;

	u32 irq_dbg_read_ptr;
	u32 dbg_param;
	struct omap_aess_dbg *dbg;
	struct omap_aess_seq seq;
	struct omap_aess_mapping *fw_info;

};

struct omap_aess_equ {
	/* type of filter */
	u32 equ_type;
	/* filter length */
	u32 equ_length;
	union {
		/* parameters are the direct and recursive coefficients in */
		/* Q6.26 integer fixed-point format. */
		s32 type1[NBEQ1];
		struct {
			/* center frequency of the band [Hz] */
			s32 freq[NBEQ2];
			/* gain of each band. [dB] */
			s32 gain[NBEQ2];
			/* Q factor of this band [dB] */
			s32 q[NBEQ2];
		} type2;
	} coef;
	s32 equ_param3;
};


struct omap_aess_dma {
	/* OCP L3 pointer to the first address of the */
	void *data;
	/* destination buffer (either DMA or Ping-Pong read/write pointers). */
	/* address L3 when addressing the DMEM buffer instead of CBPr */
	void *l3_dmem;
	/* address L3 translated to L4 the ARM memory space */
	void *l4_dmem;
	/* number of iterations for the DMA data moves. */
	u32 iter;
};


//extern struct omap_aess_mapping aess_fw_init;
//extern struct omap_aess_addr omap_aess_map[];
//extern int omap_function_id[];
//extern int omap_label_id[];
//extern struct omap_aess_init_task aess_init_table;
//extern struct omap_aess_port abe_port_init[LAST_PORT_ID];
//extern struct omap_aess_port abe_port_init_pp;
//extern struct omap_aess_task aess_dl1_mono_mixer[2];
//extern struct omap_aess_task aess_dl2_mono_mixer[2];
//extern struct omap_aess_task aess_audul_mono_mixer[2];

extern int omap_aess_init_asrc_vx_ul(s32 *el, s32 dppm);
extern int omap_aess_init_asrc_vx_dl(s32 *el, s32 dppm);


#endif/* _ABE_H_ */
