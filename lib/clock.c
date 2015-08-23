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

#include <config.h>
#include <io.h>
#include <cpu.h>
#include <bitset.h>
#include <omap4/omap4.h>
#include <omap4/clock.h>
#include <omap4/platform.h>

/* This tables are generated only for OPP100 */

/* MPU parameters */
struct dpll_param mpu_dpll_param_1008mhz[7] = {
	/* 12M values */
	{0x54, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x3f0, 0xc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0x3c, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x69, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x1f8, 0xc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0x70, 0x2, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values */
	/* RUN MPU @ 1008 MHz */
	{0x69, 0x3, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00},
};

struct dpll_param mpu_dpll_param_920mhz[7] = {
	/* 12M values */
	{0xe6, 0x2, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x398, 0xc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0xdb, 0x3, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x23f, 0xb, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x1cc, 0xc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0x398, 0x1a, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values */
	/* RUN MPU @ 920 MHz */
	{0x23f, 0x17, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00},
};

struct dpll_param mpu_dpll_param_600mhz[7] = {
	/* 12M values */
	{0x32, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x258, 0xc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0xfa, 0x6, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x7d, 0x3, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x12c, 0xc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0xc8, 0x8, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values */
	/* RUN MPU @ 1.2 GHz */
	{0x7d, 0x07, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00},
};

struct dpll_param mpu_dpll_param_700mhz[7] = {
	/* 12M values */
	{0xaf, 0x2, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x2bc, 0xc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0x7d, 0x2, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x36b, 0x17, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x15e, 0xc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0x2bc, 0x1a, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values */
	/* RUN MPU @ 700 MHz */
	{0x36b, 0x2f, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
};

struct dpll_param mpu_dpll_param_800mhz[7] = {
	/* 12M values */
	{0xc8, 0x2, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x320, 0xc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0x3e8, 0x14, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x7d, 0x2, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x190, 0xc, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0x320, 0x1a, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values */
        /* RUN MPU @ 800 MHz */
	{0x7d, 0x5, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
};

struct dpll_param mpu_dpll_param_1_5ghz[7] = {
	/* 12M values */
	{0x7d, 0x1, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x2ee, 0xc, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0x271, 0xd, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x271, 0xf, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x177, 0xc, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0xfa, 0x8, 0x01, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values */
	/* RUN MPU @ 1.5 GHz */
	{0x271, 0x1f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
};

/* PER parameters */
const struct dpll_param per_dpll_param[7] = {
	/* 12M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values */
	{0x14, 0x00, 0x08, 0x06, 0x0c, 0x09, 0x04, 0x05},
};

/* IVA parameters */
struct dpll_param iva_dpll_param[7] = {
	/* 12M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values */
	{0x61, 0x03, 0x00, 0x00, 0x08, 0x0E, 0x00, 0x00},
};

/* CORE parameters */
struct dpll_param core_dpll_param[7] = {
	/* 12M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values - DDR@200MHz*/
	{0x7d, 0x05, 0x02, 0x05, 0x08, 0x04, 0x06, 0x05},
};

/* CORE parameters */
struct dpll_param core_dpll_param_ddr400[7] = {
	/* 12M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values - DDR@400MHz*/
	{0x7d, 0x05, 0x01, 0x05, 0x08, 0x04, 0x06, 0x05},
};

/* CORE parameters */
struct dpll_param core_dpll_param_ddr466[7] = {
	/* 12M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values - DDR@466MHz*/
	{0x36B, 0x23, 0x01, 0x06, 0x08, 0x04, 0x07, 0x05},
};

/* CORE parameters for L3 at 190 MHz - For ES1 only*/
struct dpll_param core_dpll_param_l3_190[7] = {
	/* 12M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values */
#ifdef CORE_190MHZ
	{0x1f0, 0x18, 0x01, 0x05, 0x08, 0x04, 0x06, 0x05},
#else /* Default CORE @166MHz */
	{0x1b0, 0x18, 0x01, 0x05, 0x08, 0x04, 0x06, 0x05},
#endif
};

/*
 * ABE parameters
 *
 * By default DPLL_ABE is driven from 32KHz clock.  To drive it from SYS_CK
 * set OMAP4_ABE_SYSCK_ENABLE
 */
struct dpll_param abe_dpll_param[7] = {
	/* 12M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values */
#ifdef OMAP4_ABE_SYSCK_ENABLE
	{0x40, 0x18, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0},
#else
	{0x2ee, 0x0, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0},
#endif
};

/* USB parameters */
struct dpll_param usb_dpll_param[7] = {
	/* 12M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 13M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 16.8M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 19.2M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 26M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 27M values */
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
	/* 38.4M values */
	{0x32, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4},
};

static void
configure_mpu_dpll(uint32_t sys_clksel)
{
	struct dpll_param *dpll_param;
	uint32_t rev;

	rev = omap_revision();

	/* Unlock the MPU dpll */
	clrsetbits32(CM_CLKMODE_DPLL_MPU, 0x00000003, PLL_MN_POWER_BYPASS);
	wait_on(BITSET0, 0, CM_IDLEST_DPLL_MPU, LDELAY);

	if (rev >= OMAP4470_ES1_0) {
		dpll_param = &mpu_dpll_param_800mhz[sys_clksel];
	} else if (rev >= OMAP4460_ES1_0) {
		uint32_t rbb_trimmed = readl(STD_FUSE_OPP_DPLL_1);
		if (rbb_trimmed & (1 << 19))
			dpll_param = &mpu_dpll_param_700mhz[sys_clksel];
		else
			dpll_param = &mpu_dpll_param_600mhz[sys_clksel];

		setbits32(CM_MPU_MPU_CLKCTRL, MPU_CLKCTRL_CLKSEL_EMIF_DIV_MODE_MASK);
		setbits32(CM_MPU_MPU_CLKCTRL, MPU_CLKCTRL_CLKSEL_ABE_DIV_MODE_MASK);
		clrbits32(CM_CLKSEL_DPLL_MPU, CM_CLKSEL_DCC_EN_MASK);
	} else {
		dpll_param = &mpu_dpll_param_600mhz[sys_clksel];
	}

	clrbits32(CM_AUTOIDLE_DPLL_MPU, 0x00000003); /* Disable DPLL autoidle */

	/* Set M,N,M2 values */
	clrsetbits32(CM_CLKSEL_DPLL_MPU, 0x0007ff00, dpll_param->m << 8);
	clrsetbits32(CM_CLKSEL_DPLL_MPU, 0x0000007f, dpll_param->n);
	clrsetbits32(CM_DIV_M2_DPLL_MPU, 0x0000001f, dpll_param->m2);
	clrsetbits32(CM_DIV_M2_DPLL_MPU, 0x00000100, 0x1 << 8);

	/* Lock the mpu dpll */
	clrsetbits32(CM_CLKMODE_DPLL_MPU, 0x00000003, PLL_LOCK | 0x10);
	wait_on(BITSET0, 1, CM_IDLEST_DPLL_MPU, LDELAY);

	return;
}

static void
configure_iva_dpll(uint32_t sys_clksel)
{
	struct dpll_param *dpll_param;

	/* Unlock the IVA dpll */
	clrsetbits32(CM_CLKMODE_DPLL_IVA, 0x00000003, PLL_MN_POWER_BYPASS);
	wait_on(BITSET0, 0, CM_IDLEST_DPLL_IVA, LDELAY);

	/* CM_BYPCLK_DPLL_IVA = CORE_X2_CLK/2 */
	clrsetbits32(CM_BYPCLK_DPLL_IVA, 0x00000003, 0x1);

	/* Program IVA DPLL */
	dpll_param = &iva_dpll_param[sys_clksel];

	clrbits32(CM_AUTOIDLE_DPLL_IVA, 0x00000003); /* Disable DPLL autoidle */

	/* Set M,N,M4,M5 */
	clrsetbits32(CM_CLKSEL_DPLL_IVA, 0x0007ff00, dpll_param->m << 8);
	clrsetbits32(CM_CLKSEL_DPLL_IVA, 0x0000007f, dpll_param->n);
	clrsetbits32(CM_DIV_M4_DPLL_IVA, 0x0000001f, dpll_param->m4);
	clrsetbits32(CM_DIV_M4_DPLL_IVA, 0x00000100, 0x1 << 8);
	clrsetbits32(CM_DIV_M5_DPLL_IVA, 0x0000001f, dpll_param->m5);
	clrsetbits32(CM_DIV_M5_DPLL_IVA, 0x00000100, 0x1 << 8);

	/* Lock the iva dpll */
	clrsetbits32(CM_CLKMODE_DPLL_IVA, 0x00000003, PLL_LOCK);
	wait_on(BITSET0, 1, CM_IDLEST_DPLL_IVA, LDELAY);

	return;
}

static void
configure_per_dpll(uint32_t sys_clksel)
{
	const struct dpll_param *dpll_param;

	/* Unlock the PER dpll */
	clrsetbits32(CM_CLKMODE_DPLL_PER, 0x00000003, PLL_MN_POWER_BYPASS);
	wait_on(BITSET0, 0, CM_IDLEST_DPLL_PER, LDELAY);

	/* Program PER DPLL */
	dpll_param = &per_dpll_param[sys_clksel];

	/* Disable autoidle */
	clrbits32(CM_AUTOIDLE_DPLL_PER, 0x00000003);

	clrsetbits32(CM_CLKSEL_DPLL_PER, 0x0007ff00, dpll_param->m << 8);
	clrsetbits32(CM_CLKSEL_DPLL_PER, 0x0000007f, dpll_param->n);
	clrsetbits32(CM_DIV_M2_DPLL_PER, 0x0000001f, dpll_param->m2);
	clrsetbits32(CM_DIV_M2_DPLL_PER, 0x00000100, 0x1 << 8);
	clrsetbits32(CM_DIV_M3_DPLL_PER, 0x0000001f, dpll_param->m3);
	clrsetbits32(CM_DIV_M3_DPLL_PER, 0x00000100, 0x1 << 8);
	clrsetbits32(CM_DIV_M4_DPLL_PER, 0x0000001f, dpll_param->m4);
	clrsetbits32(CM_DIV_M4_DPLL_PER, 0x00000100, 0x1 << 8);
	clrsetbits32(CM_DIV_M5_DPLL_PER, 0x0000001f, dpll_param->m5);
	clrsetbits32(CM_DIV_M5_DPLL_PER, 0x00000100, 0x1 << 8);
	clrsetbits32(CM_DIV_M6_DPLL_PER, 0x0000001f, dpll_param->m6);
	clrsetbits32(CM_DIV_M6_DPLL_PER, 0x00000100, 0x1 << 8);
	clrsetbits32(CM_DIV_M7_DPLL_PER, 0x0000001f, dpll_param->m7);
	clrsetbits32(CM_DIV_M7_DPLL_PER, 0x00000100, 0x1 << 8);

	/* Lock the per dpll */
	clrsetbits32(CM_CLKMODE_DPLL_PER, 0x00000003, PLL_LOCK);
	wait_on(BITSET0, 1, CM_IDLEST_DPLL_PER, LDELAY);

	return;
}

/* DPLL_ABE is driven by 32KHz timer by default */
static void
configure_abe_dpll(uint32_t sys_clksel)
{
	struct dpll_param *dpll_param;
	uint32_t clkmode_value;

#ifdef OMAP4_ABE_SYSCK_ENABLE
	clrits32(CM_ABE_PLL_REF_CLKSEL, 0xffffffff);
#endif

	/* Unlock the ABE dpll */
	clrsetbits32(CM_CLKMODE_DPLL_ABE, 0x00000003, PLL_MN_POWER_BYPASS);
	wait_on(BITSET0, 0, CM_IDLEST_DPLL_ABE, LDELAY);

	/* Program ABE DPLL */
	dpll_param = &abe_dpll_param[sys_clksel];

	/* Disable autoidle */
	clrbits32(CM_AUTOIDLE_DPLL_ABE, 0x00000003);

#ifndef OMAP4_ABE_SYSCK_ENABLE
	clkmode_value = (BITSET5 | BITSET8 | BITSET9 | BITSET10 | BITSET11);
	clrsetbits32(CM_CLKMODE_DPLL_ABE, 0x00001fff, clkmode_value);
#endif

	clrsetbits32(CM_CLKSEL_DPLL_ABE, 0x0007ff00, dpll_param->m << 8);
	clrsetbits32(CM_CLKSEL_DPLL_ABE, 0x0000007f, dpll_param->n);

	/* Force DPLL CLKOUTHIF to stay enabled */
	clrsetbits32(CM_DIV_M2_DPLL_ABE, 0xffffffff, 0x500);
	clrsetbits32(CM_DIV_M2_DPLL_ABE, 0x0000001f, dpll_param->m2);
	clrsetbits32(CM_DIV_M2_DPLL_ABE, 0x00000100, 0x1 << 8);

	/* Force DPLL CLKOUTHIF to stay enabled */
	clrsetbits32(CM_DIV_M3_DPLL_ABE, 0xffffffff, 0x100);
	clrsetbits32(CM_DIV_M3_DPLL_ABE, 0x0000001f, dpll_param->m3);
	clrsetbits32(CM_DIV_M3_DPLL_ABE, 0x00000100, 0x1 << 8);

	/* Lock the abe dpll */
	clrsetbits32(CM_CLKMODE_DPLL_ABE, 0x00000003, PLL_LOCK);
	wait_on(BITSET0, 1, CM_IDLEST_DPLL_ABE, LDELAY);

#ifndef OMAP4_ABE_SYSCK_ENABLE
	if (omap_revision() < OMAP4460_ES1_0) {
		/* Set M & N values again for DPLL_ABE in warm reset scenario.*/
		clrsetbits32(CM_CLKSEL_DPLL_ABE, 0x0007ff00, dpll_param->m << 8);
		clrsetbits32(CM_CLKSEL_DPLL_ABE, 0x0000007f, dpll_param->n);
	}
#endif

	return;
}

static void
configure_usb_dpll(uint32_t sys_clksel)
{
	struct dpll_param *dpll_param;

	/* Select the 60Mhz clock 480/8 = 60*/
	clrsetbits32(CM_CLKSEL_USB_60MHz, 0xffffffff, 0x1);

	/* Unlock the USB dpll */
	clrsetbits32(CM_CLKMODE_DPLL_USB, 0x00000003, PLL_MN_POWER_BYPASS);
	wait_on(BITSET0, 0, CM_IDLEST_DPLL_USB, LDELAY);

	/* Program USB DPLL */
	dpll_param = &usb_dpll_param[sys_clksel];

	/* Disable autoidle */
	clrbits32(CM_AUTOIDLE_DPLL_USB, 0x00000003);

	clrsetbits32(CM_CLKSEL_DPLL_USB, 0xff000000, dpll_param->sd_div << 24);
	clrsetbits32(CM_CLKSEL_DPLL_USB, 0x000fff00, dpll_param->m << 8);
	clrsetbits32(CM_CLKSEL_DPLL_USB, 0x000000ff, dpll_param->n);

	/* Force DPLL CLKOUT to stay active */
	clrsetbits32(CM_DIV_M2_DPLL_USB, 0xffffffff, 0x100);
	clrsetbits32(CM_DIV_M2_DPLL_USB, 0x0000003f, dpll_param->m2);
	clrsetbits32(CM_DIV_M2_DPLL_USB, 0x00000100, 0x1 << 8);
	clrsetbits32(CM_CLKDCOLDO_DPLL_USB, 0x00000100, 0x1 << 8);

	/* Lock the usb dpll */
	clrsetbits32(CM_CLKMODE_DPLL_USB, 0x00000003, PLL_LOCK);
	wait_on(BITSET0, 1, CM_IDLEST_DPLL_USB, LDELAY);

	/* force enable the CLKDCOLDO clock */
	clrsetbits32(CM_CLKDCOLDO_DPLL_USB, 0xffffffff, 0x100);

	return;
}

void
configure_core_dpll_no_lock(void)
{
	struct dpll_param *dpll_param = 0;
	uint32_t sys_clksel;

	/* Get the sysclk speed from cm_sys_clksel
	 * Set it to 38.4 MHz, in case ROM code is bypassed
	 */
	writel(0x7, CM_SYS_CLKSEL);
	sys_clksel = 7;
	sys_clksel = sys_clksel - 1;

	/* CORE_CLK=CORE_X2_CLK/1, L3_CLK=CORE_CLK/2, L4_CLK=L3_CLK/2 */
	clrsetbits32(CM_CLKSEL_CORE, 0xffffffff, 0x110);

	/* Unlock the CORE dpll */
	clrsetbits32(CM_CLKMODE_DPLL_CORE, 0x00000003, PLL_MN_POWER_BYPASS);
	wait_on(BITSET0, 0, CM_IDLEST_DPLL_CORE, LDELAY);

	/* Program Core DPLL */
#ifdef CORE_233MHZ
	if (omap_revision() >= OMAP4470_ES1_0)
		dpll_param = &core_dpll_param_ddr466[sys_clksel];
	else
#endif
	if (omap_revision() == OMAP4430_ES1_0)
		dpll_param = &core_dpll_param_l3_190[sys_clksel];
	else if (omap_revision() == OMAP4430_ES2_0)
		dpll_param = &core_dpll_param[sys_clksel];
	else if (omap_revision() >= OMAP4430_ES2_1)
		dpll_param = &core_dpll_param_ddr400[sys_clksel];

	/* Disable autoidle */
	clrbits32(CM_AUTOIDLE_DPLL_CORE, 0x00000003);

	clrsetbits32(CM_CLKSEL_DPLL_CORE, 0x0003ff00, dpll_param->m << 8);
	clrsetbits32(CM_CLKSEL_DPLL_CORE, 0x0000003f, dpll_param->n);
	clrsetbits32(CM_DIV_M2_DPLL_CORE, 0x0000001f, dpll_param->m2);
	clrsetbits32(CM_DIV_M3_DPLL_CORE, 0x0000001f, dpll_param->m3);
	clrsetbits32(CM_DIV_M4_DPLL_CORE, 0x0000001f, dpll_param->m4);
	clrsetbits32(CM_DIV_M5_DPLL_CORE, 0x0000001f, dpll_param->m5);
	clrsetbits32(CM_DIV_M6_DPLL_CORE, 0x0000001f, dpll_param->m6);
	clrsetbits32(CM_DIV_M7_DPLL_CORE, 0x0000001f, dpll_param->m7);

	if (omap_revision() == OMAP4430_ES1_0) {
		/* Do this only on ES1.0 */
		clrsetbits32(CM_DIV_M2_DPLL_CORE, 0x00000100, 0x100);
		clrsetbits32(CM_DIV_M3_DPLL_CORE, 0x00000100, 0x100);
		clrsetbits32(CM_DIV_M4_DPLL_CORE, 0x00000100, 0x100);
		clrsetbits32(CM_DIV_M5_DPLL_CORE, 0x00000100, 0x100);
		clrsetbits32(CM_DIV_M6_DPLL_CORE, 0x00000100, 0x100);
		clrsetbits32(CM_DIV_M7_DPLL_CORE, 0x00000100, 0x100);
	}

	return;
}

void
lock_core_dpll(void)
{
	/* Lock the core dpll */
	clrsetbits32(CM_CLKMODE_DPLL_CORE, 0x00000003, PLL_LOCK);
	wait_on(BITSET0, 1, CM_IDLEST_DPLL_CORE, LDELAY);

	return;
}

void
lock_core_dpll_shadow(void)
{
	struct dpll_param *dpll_param = 0;
	uint32_t sys_clksel;
	uint32_t temp;

	temp = readl(CM_MEMIF_CLKSTCTRL);
	temp &= (~3);
	temp |= 2;
	writel(temp, CM_MEMIF_CLKSTCTRL);

	while (readl(CM_MEMIF_EMIF_1_CLKCTRL) & 0x30000);
	while (readl(CM_MEMIF_EMIF_2_CLKCTRL) & 0x30000);

	/* Lock the core dpll using freq update method */
	writel(0x0A, CM_CLKMODE_DPLL_CORE);

	sys_clksel = 6;

#ifdef CORE_233MHZ
	if (omap_revision() >= OMAP4470_ES1_0)
		dpll_param_p = &core_dpll_param_ddr466[sys_clksel];
	else
#endif
	if (omap_revision() == OMAP4430_ES1_0)
		dpll_param = &core_dpll_param_l3_190[sys_clksel];
	else if (omap_revision() == OMAP4430_ES2_0)
		dpll_param = &core_dpll_param[sys_clksel];
	else if (omap_revision() >= OMAP4430_ES2_1)
		dpll_param = &core_dpll_param_ddr400[sys_clksel];

	/*
	 * CM_SHADOW_FREQ_CONFIG1: DLL_OVERRIDE = 1(hack), DLL_RESET = 1,
	 * DPLL_CORE_M2_DIV =1, DPLL_CORE_DPLL_EN = 0x7, FREQ_UPDATE = 1
	 */
	writel(0x70D | (dpll_param->m2 << 11), CM_SHADOW_FREQ_CONFIG1);

	/* Wait for freq_update to get cleared: CM_SHADOW_FREQ_CONFIG1 */
	while ((readl(CM_SHADOW_FREQ_CONFIG1) & 0x1) == 0x1);

	/* Wait for DPLL to Lock : CM_IDLEST_DPLL_CORE */
	wait_on(BITSET0, 1, CM_IDLEST_DPLL_CORE, LDELAY);

	while(readl(CM_MEMIF_EMIF_1_CLKCTRL) & 0x30000);
	while(readl(CM_MEMIF_EMIF_2_CLKCTRL) & 0x30000);

	writel(temp | 3, CM_MEMIF_CLKSTCTRL);
	return;
}

static void
enable_all_clocks(void)
{
	if (omap_revision() == OMAP4430_ES1_0) {
		/* Enable Ducati clocks */
		clrsetbits32(CM_DUCATI_DUCATI_CLKCTRL, 0xffffffff, 0x1);
		clrsetbits32(CM_DUCATI_CLKSTCTRL, 0xffffffff, 0x2);

		wait_on(BITSET8, BITSET8, CM_DUCATI_CLKSTCTRL, LDELAY);

		/* Enable ivahd and sl2 clocks */
		clrsetbits32(IVAHD_IVAHD_CLKCTRL, 0xffffffff, 0x1);
		clrsetbits32(IVAHD_SL2_CLKCTRL, 0xffffffff, 0x1);
		clrsetbits32(IVAHD_CLKSTCTRL, 0xffffffff, 0x2);

		wait_on(BITSET8, BITSET8, IVAHD_CLKSTCTRL, LDELAY);

		/* Enable Tesla clocks */
		clrsetbits32(DSP_DSP_CLKCTRL, 0xffffffff, 0x1);
		clrsetbits32(DSP_CLKSTCTRL, 0xffffffff, 0x2);

		wait_on(BITSET8, BITSET8, DSP_CLKSTCTRL, LDELAY);

		/* ABE clocks */
		clrsetbits32(CM1_ABE_CLKSTCTRL, 0xffffffff, 0x3);
		clrsetbits32(CM1_ABE_AESS_CLKCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM1_ABE_PDM_CLKCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM1_ABE_DMIC_CLKCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM1_ABE_MCASP_CLKCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM1_ABE_MCBSP1_CLKCTRL, 0xffffffff, 0x08000002);
		clrsetbits32(CM1_ABE_MCBSP2_CLKCTRL, 0xffffffff, 0x08000002);
		clrsetbits32(CM1_ABE_MCBSP3_CLKCTRL, 0xffffffff, 0x08000002);
		clrsetbits32(CM1_ABE_SLIMBUS_CLKCTRL, 0xffffffff, 0xf02);
		clrsetbits32(CM1_ABE_TIMER5_CLKCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM1_ABE_TIMER6_CLKCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM1_ABE_TIMER7_CLKCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM1_ABE_TIMER8_CLKCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM1_ABE_WDT3_CLKCTRL, 0xffffffff, 0x2);
		/* Disable sleep transitions */
		clrbits32(CM1_ABE_CLKSTCTRL, 0xffffffff);
	}

	/* L4PER clocks */
	clrsetbits32(CM_L4PER_CLKSTCTRL, 0xffffffff, 0x2);
	clrsetbits32(CM_L4PER_DMTIMER10_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_DMTIMER10_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_DMTIMER11_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_DMTIMER11_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_DMTIMER2_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_DMTIMER2_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_DMTIMER3_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_DMTIMER3_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_DMTIMER4_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_DMTIMER4_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_DMTIMER9_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_DMTIMER9_CLKCTRL, LDELAY);

	/* GPIO clocks */
	clrsetbits32(CM_L4PER_GPIO2_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_GPIO2_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_GPIO3_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_GPIO3_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_GPIO4_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_GPIO4_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_GPIO4_CLKCTRL, 0x00000100, 0x100);
	clrsetbits32(CM_L4PER_GPIO5_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_GPIO5_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_GPIO6_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_GPIO6_CLKCTRL, LDELAY);

	clrsetbits32(CM_L4PER_HDQ1W_CLKCTRL, 0xffffffff, 0x2);

	/* I2C clocks */
	clrsetbits32(CM_L4PER_I2C1_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_I2C1_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_I2C2_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_I2C2_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_I2C3_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_I2C3_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_I2C4_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_I2C4_CLKCTRL, LDELAY);

	clrsetbits32(CM_L4PER_MCBSP4_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_MCBSP4_CLKCTRL, LDELAY);

	/* MCSPI clocks */
	clrsetbits32(CM_L4PER_MCSPI1_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_MCSPI1_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_MCSPI2_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_MCSPI2_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_MCSPI3_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_MCSPI3_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_MCSPI4_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_MCSPI4_CLKCTRL, LDELAY);

	/* MMC clocks */
	clrsetbits32(CM_L3INIT_HSMMC1_CLKCTRL, 0x00000003, 0x2);
	clrsetbits32(CM_L3INIT_HSMMC1_CLKCTRL, 0x01000000, 0x1 << 24);
	clrsetbits32(CM_L3INIT_HSMMC2_CLKCTRL, 0x00000003, 0x2);
	clrsetbits32(CM_L3INIT_HSMMC2_CLKCTRL, 0x01000000, 0x1 << 24);
	clrsetbits32(CM_L4PER_MMCSD3_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET18 | BITSET17 | BITSET16, 0, CM_L4PER_MMCSD3_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_MMCSD4_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET18 | BITSET17 | BITSET16, 0, CM_L4PER_MMCSD4_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_MMCSD5_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_MMCSD5_CLKCTRL, LDELAY);

	/* UART clocks */
	clrsetbits32(CM_L4PER_UART1_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_UART1_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_UART2_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_UART2_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_UART3_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_UART3_CLKCTRL, LDELAY);
	clrsetbits32(CM_L4PER_UART4_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_L4PER_UART4_CLKCTRL, LDELAY);

	/* WKUP clocks */
	clrsetbits32(CM_WKUP_GPIO1_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_WKUP_GPIO1_CLKCTRL, LDELAY);
	clrsetbits32(CM_WKUP_TIMER1_CLKCTRL, 0xffffffff, 0x01000002);
	wait_on(BITSET17 | BITSET16, 0, CM_WKUP_TIMER1_CLKCTRL, LDELAY);

	clrsetbits32(CM_WKUP_KEYBOARD_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_WKUP_KEYBOARD_CLKCTRL, LDELAY);

	/* Enable fucntional clock of on-die temperature sensor */
	if (omap_revision() >= OMAP4460_ES1_0)
		clrsetbits32(CM_WKUP_BANDGAP_CLKCTRL, 0x00000100, 0x1 << 8);

	clrsetbits32(CM_SDMA_CLKSTCTRL, 0xffffffff, 0x0);
	clrsetbits32(CM_MEMIF_CLKSTCTRL, 0xffffffff, 0x3);
	clrsetbits32(CM_MEMIF_EMIF_1_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_MEMIF_EMIF_1_CLKCTRL, LDELAY);
	clrsetbits32(CM_MEMIF_EMIF_2_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_MEMIF_EMIF_2_CLKCTRL, LDELAY);
	clrsetbits32(CM_D2D_CLKSTCTRL, 0xffffffff, 0x3);
	clrsetbits32(CM_L3_2_GPMC_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_L3_2_GPMC_CLKCTRL, LDELAY);
	clrsetbits32(CM_L3INSTR_L3_3_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_L3INSTR_L3_3_CLKCTRL, LDELAY);
	clrsetbits32(CM_L3INSTR_L3_INSTR_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_L3INSTR_L3_INSTR_CLKCTRL, LDELAY);
	clrsetbits32(CM_L3INSTR_OCP_WP1_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_L3INSTR_OCP_WP1_CLKCTRL, LDELAY);

	/* WDT clocks */
	clrsetbits32(CM_WKUP_WDT2_CLKCTRL, 0xffffffff, 0x2);
	wait_on(BITSET17 | BITSET16, 0, CM_WKUP_WDT2_CLKCTRL, LDELAY);


	if (omap_revision() == OMAP4430_ES1_0) {
		/* Enable Camera clocks */
		clrsetbits32(CM_CAM_CLKSTCTRL, 0xffffffff, 0x3);
		clrsetbits32(CM_CAM_ISS_CLKCTRL, 0xffffffff, 0x102);
		clrsetbits32(CM_CAM_FDIF_CLKCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM_CAM_CLKSTCTRL, 0xffffffff, 0x0);

		/* Enable DSS clocks */
		/* PM_DSS_PWRSTCTRL ON State and LogicState = 1 (Retention) */
		writel(0x7, PM_DSS_PWRSTCTRL);
		clrsetbits32(CM_DSS_CLKSTCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM_DSS_DSS_CLKCTRL, 0xffffffff, 0xf02);
		clrsetbits32(CM_DSS_DEISS_CLKCTRL, 0xffffffff, 0x2);
		while ((readl(CM_DSS_CLKSTCTRL) & 0xf00) != 0xE00);
		/* Set HW_AUTO transition mode */
		clrsetbits32(CM_DSS_CLKSTCTRL, 0xffffffff, 0x3);

		/* Enable SGX clocks */
		clrsetbits32(CM_SGX_CLKSTCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM_SGX_SGX_CLKCTRL, 0xffffffff, 0x2);
		/* Check for SGX FCLK and ICLK */
		while (readl(CM_SGX_CLKSTCTRL) != 0x302);
		/* Enable hsi/unipro/usb clocks */
		clrsetbits32(CM_L3INIT_HSI_CLKCTRL, 0xffffffff, 0x1);
		clrsetbits32(CM_L3INIT_UNIPRO1_CLKCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM_L3INIT_HSUSBHOST_CLKCTRL, 0xffffffff, 0x2);
		clrsetbits32(CM_L3INIT_HSUSBOTG_CLKCTRL, 0xffffffff, 0x1);
		clrsetbits32(CM_L3INIT_HSUSBTLL_CLKCTRL, 0xffffffff, 0x1);
		clrsetbits32(CM_L3INIT_FSUSB_CLKCTRL, 0xffffffff, 0x2);
		/* enable the 32K, 48M optional clocks and enable the module */
		clrsetbits32(CM_L3INIT_USBPHY_CLKCTRL, 0xffffffff, 0x301);
	}

	/* Select DPLL PER CLOCK as source for SGX FCLK */
	clrsetbits32(CM_SGX_SGX_CLKCTRL, 0x01000000, 0x1 << 24);

	/* Enable clocks for USB fast boot to work */
	clrsetbits32(CM_L3INIT_USBPHY_CLKCTRL, 0xffffffff, 0x301);
	clrsetbits32(CM_L3INIT_HSUSBOTG_CLKCTRL, 0xffffffff, 0x1);

	/*
	 * Enable DSS clocks:
	 * In future we want to enable DSS in bootloader to show splash screen
	 */
	clrsetbits32(PM_DSS_PWRSTCTRL, 0x00000003, 0x3);
	clrsetbits32(CM_DSS_CLKSTCTRL, 0x00000003, 0x2);
	clrsetbits32(CM_DSS_DSS_CLKCTRL, 0x000007ff, 0x702);

	return;
}

void
prcm_init(void)
{
	uint32_t sys_clksel;

	/* Get the sysclk speed from cm_sys_clksel
	 * Set the CM_SYS_CLKSEL in case ROM code has not set
	 */
	writel(0x7, CM_SYS_CLKSEL);
	sys_clksel= readl(CM_SYS_CLKSEL);
	if (!sys_clksel)
		return;

	/* Configure all DPLL's at 100% OPP */
	configure_mpu_dpll(sys_clksel - 1);
	configure_iva_dpll(sys_clksel - 1);
	configure_per_dpll(sys_clksel - 1);
	configure_abe_dpll(sys_clksel - 1);
	configure_usb_dpll(sys_clksel - 1);

	/* Enable all clocks */
	enable_all_clocks();

	return;
}
