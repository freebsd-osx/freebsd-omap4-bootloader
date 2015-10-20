/*-
 * Copyright (c) 2015
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/types.h>
#include <sys/stddef.h>

#include <omap4/emif.h>
#include <omap4/omap4.h>
#include <omap4/omap_data.h>

/*
 * This file provides details of the LPDDR2 SDRAM parts used on OMAP4430
 * SDP and Panda. Since the parts used and geometry are identical for
 * SDP and Panda for a given OMAP4 revision, this information is kept
 * here instead of being in board directory. However the key functions
 * exported are weakly linked so that they can be over-ridden in the board
 * directory if there is a OMAP4 board in the future that uses a different
 * memory device or geometry.
 *
 * For any new board with different memory devices over-ride one or more
 * of the following functions as per the CONFIG flags you intend to enable:
 * - emif_get_reg_dump()
 * - emif_get_dmm_regs()
 * - emif_get_device_details()
 * - emif_get_device_timings()
 */

#ifdef EMIF_PRECALCULATED_TIMING_REGS

const struct emif_regs emif_regs_elpida_200_mhz_2cs = {
	.sdram_config_init		= 0x80000eb9,
	.sdram_config			= 0x80001ab9,
	.ref_ctrl			= 0x0000030c,
	.sdram_tim1			= 0x08648311,
	.sdram_tim2			= 0x101b06ca,
	.sdram_tim3			= 0x0048a19f,
	.read_idle_ctrl			= 0x000501ff,
	.zq_config			= 0x500b3214,
	.temp_alert_config		= 0xd8016893,
	.emif_ddr_phy_ctlr_1_init	= 0x049ffff5,
	.emif_ddr_phy_ctlr_1		= 0x049ff808
};

const struct emif_regs emif_regs_elpida_380_mhz_1cs = {
	.sdram_config_init		= 0x80000eb1,
	.sdram_config			= 0x80001ab1,
	.ref_ctrl			= 0x000005cd,
	.sdram_tim1			= 0x10cb0622,
	.sdram_tim2			= 0x20350d52,
	.sdram_tim3			= 0x00b1431f,
	.read_idle_ctrl			= 0x000501ff,
	.zq_config			= 0x500b3214,
	.temp_alert_config		= 0x58016893,
	.emif_ddr_phy_ctlr_1_init	= 0x049ffff5,
	.emif_ddr_phy_ctlr_1		= 0x049ff418
};

const struct emif_regs emif_regs_elpida_400_mhz_1cs = {
	.sdram_config_init		= 0x80800eb2,
	.sdram_config			= 0x80801ab2,
	.ref_ctrl			= 0x00000618,
	.sdram_tim1			= 0x10eb0662,
	.sdram_tim2			= 0x20370dd2,
	.sdram_tim3			= 0x00b1c33f,
	.read_idle_ctrl			= 0x000501ff,
	.zq_config			= 0x500b3215,
	.temp_alert_config		= 0x58016893,
	.emif_ddr_phy_ctlr_1_init	= 0x049ffff5,
	.emif_ddr_phy_ctlr_1		= 0x049ff418
};

const struct emif_regs emif_regs_elpida_400_mhz_2cs = {
	.sdram_config_init		= 0x80000eb9,
	.sdram_config			= 0x80001ab9,
	.ref_ctrl			= 0x00000618,
	.sdram_tim1			= 0x10eb0662,
	.sdram_tim2			= 0x20370dd2,
	.sdram_tim3			= 0x00b1c33f,
	.read_idle_ctrl			= 0x000501ff,
	.zq_config			= 0xd00b3214,
	.temp_alert_config		= 0xd8016893,
	.emif_ddr_phy_ctlr_1_init	= 0x049ffff5,
	.emif_ddr_phy_ctlr_1		= 0x049ff418
};

const struct dmm_lisa_map_regs lisa_map_2G_x_1_x_2 = {
	.dmm_lisa_map_0 = 0xFF020100,
	.dmm_lisa_map_1 = 0,
	.dmm_lisa_map_2 = 0,
	.dmm_lisa_map_3 = 0x80540300,
	.is_ma_present	= 0x0
};

const struct dmm_lisa_map_regs lisa_map_2G_x_2_x_2 = {
	.dmm_lisa_map_0 = 0xFF020100,
	.dmm_lisa_map_1 = 0,
	.dmm_lisa_map_2 = 0,
	.dmm_lisa_map_3 = 0x80640300,
	.is_ma_present	= 0x0
};

const struct dmm_lisa_map_regs ma_lisa_map_2G_x_2_x_2 = {
	.dmm_lisa_map_0 = 0xFF020100,
	.dmm_lisa_map_1 = 0,
	.dmm_lisa_map_2 = 0,
	.dmm_lisa_map_3 = 0x80640300,
	.is_ma_present	= 0x1
};

void
emif_get_reg_dump(uint32_t emif_nr, const struct emif_regs **regs)
{
	uint32_t rev = omap_revision();

	/* Same devices and geometry on both EMIFs */
	if (rev == OMAP4430_ES1_0)
		*regs = &emif_regs_elpida_380_mhz_1cs;
	else if (rev == OMAP4430_ES2_0)
		*regs = &emif_regs_elpida_200_mhz_2cs;
	else if (rev == OMAP4430_ES2_3)
		*regs = &emif_regs_elpida_400_mhz_1cs;
	else if (rev < OMAP4470_ES1_0)
		*regs = &emif_regs_elpida_400_mhz_2cs;
	else
		*regs = &emif_regs_elpida_400_mhz_1cs;
}

void
emif_get_dmm_regs(const struct dmm_lisa_map_regs
						**dmm_lisa_regs)
{
	uint32_t rev = omap_revision();

	if (rev == OMAP4430_ES1_0)
		*dmm_lisa_regs = &lisa_map_2G_x_1_x_2;
	else if (rev == OMAP4430_ES2_3)
		*dmm_lisa_regs = &lisa_map_2G_x_2_x_2;
	else if (rev < OMAP4460_ES1_0)
		*dmm_lisa_regs = &lisa_map_2G_x_2_x_2;
	else
		*dmm_lisa_regs = &ma_lisa_map_2G_x_2_x_2;
}

#else

static const struct lpddr2_device_details elpida_2G_S4_details = {
	.type		= LPDDR2_TYPE_S4,
	.density	= LPDDR2_DENSITY_2Gb,
	.io_width	= LPDDR2_IO_WIDTH_32,
	.manufacturer	= LPDDR2_MANUFACTURER_ELPIDA
};

static const struct lpddr2_device_details elpida_4G_S4_details = {
	.type		= LPDDR2_TYPE_S4,
	.density	= LPDDR2_DENSITY_4Gb,
	.io_width	= LPDDR2_IO_WIDTH_32,
	.manufacturer	= LPDDR2_MANUFACTURER_ELPIDA
};

struct lpddr2_device_details *
emif_get_device_details(uint32_t emif_nr, uint8_t cs,
			struct lpddr2_device_details *lpddr2_dev_details)
{
	uint32_t rev = omap_revision();

	/* EMIF1 & EMIF2 have identical configuration */
	if (((rev == OMAP4430_ES1_0) || (rev == OMAP4470_ES1_0))
		&& (cs == CS1)) {
		/* Nothing connected on CS1 for 4430/4470 ES1.0 */
		return NULL;
	} else if (rev < OMAP4470_ES1_0) {
		/* In all other 4430/4460 cases Elpida 2G device */
		*lpddr2_dev_details = elpida_2G_S4_details;
	} else {
		/* 4470: 4G device */
		*lpddr2_dev_details = elpida_4G_S4_details;
	}
	return lpddr2_dev_details;
}

#endif /* EMIF_PRECALCULATED_TIMING_REGS */

#ifndef DEFAULT_LPDDR2_TIMINGS
static const struct lpddr2_ac_timings timings_elpida_400_mhz = {
	.max_freq	= 400000000,
	.RL		= 6,
	.tRPab		= 21,
	.tRCD		= 18,
	.tWR		= 15,
	.tRASmin	= 42,
	.tRRD		= 10,
	.tWTRx2		= 15,
	.tXSR		= 140,
	.tXPx2		= 15,
	.tRFCab		= 130,
	.tRTPx2		= 15,
	.tCKE		= 3,
	.tCKESR		= 15,
	.tZQCS		= 90,
	.tZQCL		= 360,
	.tZQINIT	= 1000,
	.tDQSCKMAXx2	= 11,
	.tRASmax	= 70,
	.tFAW		= 50
};

static const struct lpddr2_ac_timings timings_elpida_333_mhz = {
	.max_freq	= 333000000,
	.RL		= 5,
	.tRPab		= 21,
	.tRCD		= 18,
	.tWR		= 15,
	.tRASmin	= 42,
	.tRRD		= 10,
	.tWTRx2		= 15,
	.tXSR		= 140,
	.tXPx2		= 15,
	.tRFCab		= 130,
	.tRTPx2		= 15,
	.tCKE		= 3,
	.tCKESR		= 15,
	.tZQCS		= 90,
	.tZQCL		= 360,
	.tZQINIT	= 1000,
	.tDQSCKMAXx2	= 11,
	.tRASmax	= 70,
	.tFAW		= 50
};

static const struct lpddr2_ac_timings timings_elpida_200_mhz = {
	.max_freq	= 200000000,
	.RL		= 3,
	.tRPab		= 21,
	.tRCD		= 18,
	.tWR		= 15,
	.tRASmin	= 42,
	.tRRD		= 10,
	.tWTRx2		= 20,
	.tXSR		= 140,
	.tXPx2		= 15,
	.tRFCab		= 130,
	.tRTPx2		= 15,
	.tCKE		= 3,
	.tCKESR		= 15,
	.tZQCS		= 90,
	.tZQCL		= 360,
	.tZQINIT	= 1000,
	.tDQSCKMAXx2	= 11,
	.tRASmax	= 70,
	.tFAW		= 50
};

static const struct lpddr2_min_tck min_tck_elpida = {
	.tRL		= 3,
	.tRP_AB		= 3,
	.tRCD		= 3,
	.tWR		= 3,
	.tRAS_MIN	= 3,
	.tRRD		= 2,
	.tWTR		= 2,
	.tXP		= 2,
	.tRTP		= 2,
	.tCKE		= 3,
	.tCKESR		= 3,
	.tFAW		= 8
};

static const struct lpddr2_ac_timings *elpida_ac_timings[MAX_NUM_SPEEDBINS] = {
		&timings_elpida_200_mhz,
		&timings_elpida_333_mhz,
		&timings_elpida_400_mhz
};

static const struct lpddr2_device_timings elpida_2G_S4_timings = {
	.ac_timings	= elpida_ac_timings,
	.min_tck	= &min_tck_elpida,
};

void
emif_get_device_timings(uint32_t emif_nr,
		const struct lpddr2_device_timings **cs0_device_timings,
		const struct lpddr2_device_timings **cs1_device_timings)
{
	uint32_t rev = omap_revision();

	/* Identical devices on EMIF1 & EMIF2 */
	*cs0_device_timings = &elpida_2G_S4_timings;

	if ((rev == OMAP4430_ES1_0) || (rev == OMAP4470_ES1_0))
		*cs1_device_timings = NULL;
	else
		*cs1_device_timings = &elpida_2G_S4_timings;
}

#endif /* CONFIG_SYS_DEFAULT_LPDDR2_TIMINGS */

const struct lpddr2_mr_regs mr_regs = {
	.mr1	= MR1_BL_8_BT_SEQ_WRAP_EN_NWR_3,
	.mr2	= 0x4,
	.mr3	= -1,
	.mr10	= MR10_ZQ_ZQINIT,
	.mr16	= MR16_REF_FULL_ARRAY
};

void get_lpddr2_mr_regs(const struct lpddr2_mr_regs **regs)
{
	*regs = &mr_regs;
}

const struct read_write_regs *
get_bug_regs(uint32_t *iterations)
{
	return 0;
}
