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

#include <boot.h>
#include <io.h>
#include <omap4/hw.h>

#define PLL_STOP		1 /* PER & IVA */
#define PLL_MN_POWER_BYPASS	4
#define PLL_LOW_POWER_BYPASS	5 /* MPU, IVA & CORE */
#define PLL_FAST_RELOCK_BYPASS	6 /* CORE */
#define PLL_LOCK		7 /* MPU, IVA, CORE & PER */

/*
 * clk sel is 12M / 13M / 16.8M / 19.2M / 26M / 27M / 38.4M
 * only support 38.4M in boot
 */

struct dpll_param mpu_dpll_param_800mhz = {
	0x7d, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
};

struct dpll_param mpu_dpll_param_700mhz = {
	0x36b, 0x2f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
};

struct dpll_param mpu_dpll_param_600mhz = {
	0x7d, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const struct dpll_param per_dpll_param = {
	0x14, 0x00, 0x08, 0x06, 0x0c, 0x09, 0x04, 0x05,
};

struct dpll_param iva_dpll_param = {
	0x61, 0x03, 0x00, 0x00, 0x04, 0x07, 0x00, 0x00,
};

struct dpll_param core_dpll_param_ddr400mhz = {
	0x7d, 0x05, 0x01, 0x05, 0x08, 0x04, 0x06, 0x05,
};

struct dpll_param core_dpll_param_ddr466mhz = {
	0x36B, 0x23, 0x01, 0x06, 0x08, 0x04, 0x07, 0x05,
};

struct dpll_param abe_dpll_param = {
	0x40, 0x18, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0,
};

struct dpll_param usb_dpll_param = {
	0x32, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0,
};

static void
configure_mpu_dpll(struct dpll_param *dpll_param)
{
	int omap_rev;
	uint32_t emif_div_4, abe_div_8, dcc_en;

	/* Unlock the MPU dpll */
	clrsetbits(CM_CLKMODE_DPLL_MPU, 0x00000007, PLL_MN_POWER_BYPASS);
	poll(0x0, 0, CM_IDLEST_DPLL_MPU);

	omap_rev = get_omap_rev();
	if (omap_rev >= OMAP4470_ES1_0) {
		/*
		 * Same M, N as for 800 MHz from M2 output will
		 * give 1600 MHz from M3 output
		 */
		dpll_param = &mpu_dpll_param_800mhz;
	} else if (omap_rev >= OMAP4460_ES1_0) {
		/*
		 * Same M, N as for 700 MHz from M2 output will
		 * give 1400 MHz from M3 output
		 */
		dpll_param = &mpu_dpll_param_700mhz;

		emif_div_4 = 1;
		abe_div_8 = 1;

		clrsetbits(CM_MPU_MPU_CLKCTRL, 0x01000000, emif_div_4 << 24);
		clrsetbits(CM_MPU_MPU_CLKCTRL, 0x02000000, abe_div_8 << 25);

		dcc_en = 0;
		/* disable DCC on 4460 */
		clrsetbits(CM_CLKSEL_DPLL_MPU, 0x00400000, dcc_en << 22);
	}

	/* Disable DPLL autoidle */
	clrsetbits(CM_AUTOIDLE_DPLL_MPU, 0x00000007, 0x0);

	/* Set M,N,M2 values */
	clrsetbits(CM_CLKSEL_DPLL_MPU, 0x0007ff00, dpll_param->m << 8);
	clrsetbits(CM_CLKSEL_DPLL_MPU, 0x0000003f, dpll_param->n);
	clrsetbits(CM_DIV_M2_DPLL_MPU, 0x0000001f, dpll_param->m2);
	clrsetbits(CM_DIV_M2_DPLL_MPU, 0x00000100, 0x1 << 8);

	/* Lock the mpu dpll */
	clrsetbits(CM_CLKMODE_DPLL_MPU, 0x00000007, (PLL_LOCK | 10));
	poll(0x0, 1, CM_IDLEST_DPLL_MPU);
}

static void
configure_iva_dpll(struct dpll_param *dpll_param)
{
	/* Unlock the IVA dpll */
	clrsetbits(CM_CLKMODE_DPLL_IVA, 0x00000007, PLL_MN_POWER_BYPASS);
	poll(0x0, 0, CM_IDLEST_DPLL_IVA);

	/* CM_BYPCLK_DPLL_IVA = CORE_X2_CLK/2 */
	clrsetbits(CM_BYPCLK_DPLL_IVA, 0x00000003, 0x1);

	/* Disable DPLL autoidle */
	clrsetbits(CM_AUTOIDLE_DPLL_IVA, 0x00000007, 0x0);

	/* Set M,N,M4,M5 */
	clrsetbits(CM_CLKSEL_DPLL_IVA, 0x0007ff00, dpll_param->m << 8);
	clrsetbits(CM_CLKSEL_DPLL_IVA, 0x0000007f, dpll_param->n);
	clrsetbits(CM_DIV_M4_DPLL_IVA, 0x0000001f, dpll_param->m4);
	clrsetbits(CM_DIV_M4_DPLL_IVA, 0x00000100, 0x1 << 8);
	clrsetbits(CM_DIV_M5_DPLL_IVA, 0x0000001f, dpll_param->m5);
	clrsetbits(CM_DIV_M5_DPLL_IVA, 0x00000100, 0x1 << 8);

	/* Lock the iva dpll */
	clrsetbits(CM_CLKMODE_DPLL_IVA, 0x00000007, PLL_LOCK);
	poll(0x0, 1, CM_IDLEST_DPLL_IVA);
}

static void
configure_per_dpll(const struct dpll_param *dpll_param)
{
	/* Unlock the PER dpll */
	clrsetbits(CM_CLKMODE_DPLL_PER, 0x00000007, PLL_MN_POWER_BYPASS);
	poll(0x0, 0, CM_IDLEST_DPLL_PER);

	/* Disable autoidle */
	clrsetbits(CM_AUTOIDLE_DPLL_PER, 0x00000007, 0x0);
	clrsetbits(CM_CLKSEL_DPLL_PER, 0x0007ff00, dpll_param->m << 8);
	clrsetbits(CM_CLKSEL_DPLL_PER, 0x0000003f, dpll_param->n);
	clrsetbits(CM_DIV_M2_DPLL_PER, 0x0000001f, dpll_param->m2);
	clrsetbits(CM_DIV_M2_DPLL_PER, 0x00000100, 0x1 << 8);
	clrsetbits(CM_DIV_M3_DPLL_PER, 0x0000001f, dpll_param->m3);
	clrsetbits(CM_DIV_M3_DPLL_PER, 0x00000100, 0x1 << 8);
	clrsetbits(CM_DIV_M4_DPLL_PER, 0x0000001f, dpll_param->m4);
	clrsetbits(CM_DIV_M4_DPLL_PER, 0x00000100, 0x1 << 8);
	clrsetbits(CM_DIV_M5_DPLL_PER, 0x0000001f, dpll_param->m5);
	clrsetbits(CM_DIV_M5_DPLL_PER, 0x00000100, 0x1 << 8);
	clrsetbits(CM_DIV_M6_DPLL_PER, 0x0000001f, dpll_param->m6);
	clrsetbits(CM_DIV_M6_DPLL_PER, 0x00000100, 0x1 << 8);
	clrsetbits(CM_DIV_M7_DPLL_PER, 0x0000001f, dpll_param->m7);
	clrsetbits(CM_DIV_M7_DPLL_PER, 0x00000100, 0x1 << 8);

	/* Lock the per dpll */
	clrsetbits(CM_CLKMODE_DPLL_PER, 0x00000007, PLL_LOCK);
	poll(0x0, 1, CM_IDLEST_DPLL_PER);
}

static void
configure_abe_dpll(struct dpll_param *dpll_param)
{
	/* Select sys_clk as ref clk for ABE dpll */
	writel(0, CM_ABE_PLL_REF_CLKSEL);

	/* Unlock the ABE dpll */
	clrsetbits(CM_CLKMODE_DPLL_ABE, 0x00000007, PLL_MN_POWER_BYPASS);
	poll(0x0, 0, CM_IDLEST_DPLL_ABE);

	/* Disable autoidle */
	clrsetbits(CM_AUTOIDLE_DPLL_ABE, 0x00000007, 0x0);

	clrsetbits(CM_CLKSEL_DPLL_ABE, 0x0007ff00, dpll_param->m << 8);
	clrsetbits(CM_CLKSEL_DPLL_ABE, 0x0000002f, dpll_param->n);

	/* Force DPLL CLKOUTHIF to stay enabled */
	clrsetbits(CM_DIV_M2_DPLL_ABE, 0xffffffff, 0x500);
	clrsetbits(CM_DIV_M2_DPLL_ABE, 0x0000001f, dpll_param->m2);
	clrsetbits(CM_DIV_M2_DPLL_ABE, 0x00000100, 0x1 << 8);

	/* Force DPLL CLKOUTHIF to stay enabled */
	clrsetbits(CM_DIV_M3_DPLL_ABE, 0xffffffff, 0x100);
	clrsetbits(CM_DIV_M3_DPLL_ABE, 0x0000001f, dpll_param->m3);
	clrsetbits(CM_DIV_M3_DPLL_ABE, 0x00000100, 0x1 << 8);

	/* Lock the abe dpll */
	clrsetbits(CM_CLKMODE_DPLL_ABE, 0x00000007, PLL_LOCK);
	poll(0x0, 1, CM_IDLEST_DPLL_ABE);
}

static void
configure_usb_dpll(struct dpll_param *dpll_param)
{
	/* Select the 60Mhz clock 480/8 = 60*/
	clrsetbits(CM_CLKSEL_USB_60MHz, 0xffffffff, 0x1);

	/* Unlock the USB dpll */
	clrsetbits(CM_CLKMODE_DPLL_USB, 0x00000007, PLL_MN_POWER_BYPASS);
	poll(0x0, 0, CM_IDLEST_DPLL_USB);

	/* Disable autoidle */
	clrsetbits(CM_AUTOIDLE_DPLL_USB, 0x00000007, 0x0);
	clrsetbits(CM_CLKSEL_DPLL_USB, 0x0007ff00, dpll_param->m << 8);
	clrsetbits(CM_CLKSEL_DPLL_USB, 0x0000003f, dpll_param->n);

	/* Force DPLL CLKOUT to stay active */
	clrsetbits(CM_DIV_M2_DPLL_USB, 0xffffffff, 0x100);
	clrsetbits(CM_DIV_M2_DPLL_USB, 0x0000001f, dpll_param->m2);
	clrsetbits(CM_DIV_M2_DPLL_USB, 0x00000100, 0x1 << 8);
	clrsetbits(CM_CLKDCOLDO_DPLL_USB, 0x00000100, 0x1 << 8);

	/* Lock the usb dpll */
	clrsetbits(CM_CLKMODE_DPLL_USB, 0x00000007, PLL_LOCK);
	poll(0x0, 1, CM_IDLEST_DPLL_USB);

	/* force enable the CLKDCOLDO clock */
	clrsetbits(CM_CLKDCOLDO_DPLL_USB, 0xffffffff, 0x100);
}

void
configure_core_dpll_no_lock(void)
{
	int omap_rev;
	struct dpll_param *dpll_param;

	omap_rev = get_omap_rev();
	if (omap_rev >= OMAP4470_ES1_0)
	        dpll_param = &core_dpll_param_ddr466mhz;
	else
	        dpll_param = &core_dpll_param_ddr400mhz;

	/*
	 * Get the sysclk speed from cm_sys_clksel
	 * Set it to 38.4 MHz, in case ROM code is bypassed
	 */
	writel(0x7, CM_SYS_CLKSEL);

	/* CORE_CLK=CORE_X2_CLK, L3_CLK=CORE_CLK/2, L4_CLK=L3_CLK/2 */
	clrsetbits(CM_CLKSEL_CORE, 0xffffffff, 0x110);

	/* Unlock the CORE dpll */
	clrsetbits(CM_CLKMODE_DPLL_CORE, 0x7, PLL_MN_POWER_BYPASS);
	poll(0x0, 0, CM_IDLEST_DPLL_CORE);

	/* Disable autoidle */
	clrsetbits(CM_AUTOIDLE_DPLL_CORE, 0x7, 0x0);
	clrsetbits(CM_CLKSEL_DPLL_CORE, 0x7ff00, dpll_param->m << 8);
	clrsetbits(CM_CLKSEL_DPLL_CORE, 0x3f, dpll_param->n);
	clrsetbits(CM_DIV_M2_DPLL_CORE, 0x1f, dpll_param->m2);
	clrsetbits(CM_DIV_M3_DPLL_CORE, 0x1f, dpll_param->m3);
	clrsetbits(CM_DIV_M4_DPLL_CORE, 0x1f, dpll_param->m4);
	clrsetbits(CM_DIV_M5_DPLL_CORE, 0x1f, dpll_param->m5);
	clrsetbits(CM_DIV_M6_DPLL_CORE, 0x1f, dpll_param->m6);
	clrsetbits(CM_DIV_M7_DPLL_CORE, 0x1f, dpll_param->m7);
}

void
lock_core_dpll(void)
{
	/* Lock the core dpll */
	clrsetbits(CM_CLKMODE_DPLL_CORE, 0x7, PLL_LOCK);
	poll(0x0, 1, CM_IDLEST_DPLL_CORE);
}

void
lock_core_dpll_shadow(void)
{
	int omap_rev;
	struct dpll_param *dpll_param;

	/* Put EMIF clock domain in sw wakeup mode */
	clrsetbits(CM_MEMIF_CLKSTCTRL, 0x3, 0x2);
	while (readl(CM_MEMIF_EMIF_1_CLKCTRL) & 0x30000)
		;

	while (readl(CM_MEMIF_EMIF_2_CLKCTRL) & 0x30000)
		;

	omap_rev = get_omap_rev();
	if (omap_rev >= OMAP4470_ES1_0)
		dpll_param = &core_dpll_param_ddr466mhz;
	else
		dpll_param = &core_dpll_param_ddr400mhz;

	/* Lock the core dpll using freq update method */
	clrsetbits(CM_CLKMODE_DPLL_CORE, 0x7, PLL_FAST_RELOCK_BYPASS);

	/*
	 * CM_SHADOW_FREQ_CONFIG1: DLL_OVERRIDE = 1(hack), DLL_RESET = 1,
	 * DPLL_CORE_M2_DIV =1, DPLL_CORE_DPLL_EN = 0x7, FREQ_UPDATE = 1
	 */
	writel(0x70d | (dpll_param->m2 << 11), CM_SHADOW_FREQ_CONFIG1);

	/* Wait for freq update to get cleared: CM_SHADOW_FREQ_CONFIG1 */
	poll(0x0, 0, CM_SHADOW_FREQ_CONFIG1);

	/* Wait for DPLL to Lock : CM_IDLEST_DPLL_CORE */
	poll(0x0, 1, CM_IDLEST_DPLL_CORE);

	/* Put EMIF clock domain back in hw auto mode */
	clrsetbits(CM_MEMIF_CLKSTCTRL, 0x3, 0x3);
	while (readl(CM_MEMIF_EMIF_1_CLKCTRL) & 0x30000)
		;

	while (readl(CM_MEMIF_EMIF_2_CLKCTRL) & 0x30000)
		;

}

static void
enable_all_clocks(void)
{
	/* L4PER clocks */
	clrsetbits(CM_L4PER_CLKSTCTRL, 0x00000003, 0x2);
	clrsetbits(CM_L4PER_DMTIMER10_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_DMTIMER10_CLKCTRL);

	clrsetbits(CM_L4PER_DMTIMER11_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_DMTIMER11_CLKCTRL);

	clrsetbits(CM_L4PER_DMTIMER2_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_DMTIMER2_CLKCTRL);

	clrsetbits(CM_L4PER_DMTIMER3_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_DMTIMER3_CLKCTRL);

	clrsetbits(CM_L4PER_DMTIMER4_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_DMTIMER4_CLKCTRL);

	clrsetbits(CM_L4PER_DMTIMER9_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_DMTIMER9_CLKCTRL);

	/* GPIO clocks */
	clrsetbits(CM_L4PER_GPIO2_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_L4PER_GPIO2_CLKCTRL);

	clrsetbits(CM_L4PER_GPIO3_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_L4PER_GPIO3_CLKCTRL);

	clrsetbits(CM_L4PER_GPIO4_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_L4PER_GPIO4_CLKCTRL);

	clrsetbits(CM_L4PER_GPIO4_CLKCTRL, 0x00000100, 0x1 << 8);

	clrsetbits(CM_L4PER_GPIO5_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_L4PER_GPIO5_CLKCTRL);

	clrsetbits(CM_L4PER_GPIO6_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_L4PER_GPIO6_CLKCTRL);

	clrsetbits(CM_L4PER_HDQ1W_CLKCTRL, 0x00000003, 0x2);

	/* I2C clocks */
	clrsetbits(CM_L4PER_I2C1_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_I2C1_CLKCTRL);

	clrsetbits(CM_L4PER_I2C2_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_I2C2_CLKCTRL);

	clrsetbits(CM_L4PER_I2C3_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_I2C3_CLKCTRL);

	clrsetbits(CM_L4PER_I2C4_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_I2C4_CLKCTRL);

	clrsetbits(CM_L4PER_MCBSP4_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_MCBSP4_CLKCTRL);

	/* MCSPI clocks */
	clrsetbits(CM_L4PER_MCSPI1_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_MCSPI1_CLKCTRL);

	clrsetbits(CM_L4PER_MCSPI2_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_MCSPI2_CLKCTRL);

	clrsetbits(CM_L4PER_MCSPI3_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_MCSPI3_CLKCTRL);

	clrsetbits(CM_L4PER_MCSPI4_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_MCSPI4_CLKCTRL);

	/* MMC clocks */
	clrsetbits(CM_L3INIT_HSMMC1_CLKCTRL, 0x00000003, 0x2);
	clrsetbits(CM_L3INIT_HSMMC1_CLKCTRL, 0x01000000, 0x1 << 24);
	clrsetbits(CM_L3INIT_HSMMC2_CLKCTRL, 0x00000003, 0x2);
	clrsetbits(CM_L3INIT_HSMMC2_CLKCTRL, 0x01000000, 0x1 << 24);

	clrsetbits(CM_L4PER_MMCSD3_CLKCTRL, 0x00000003, 0x2);
	poll(0x70000, 0, CM_L4PER_MMCSD3_CLKCTRL);

	clrsetbits(CM_L4PER_MMCSD4_CLKCTRL, 0x00000003, 0x2);
	poll(0x70000, 0, CM_L4PER_MMCSD4_CLKCTRL);

	clrsetbits(CM_L4PER_MMCSD5_CLKCTRL, 0x00000003, 0x2);
	poll(0x70000, 0, CM_L4PER_MMCSD5_CLKCTRL);

	/* WKUP clocks */
	clrsetbits(CM_WKUP_GPIO1_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_WKUP_GPIO1_CLKCTRL);

	clrsetbits(CM_WKUP_TIMER1_CLKCTRL, 0x00000003, 0x01000002);
	poll(0x30000, 0, CM_WKUP_TIMER1_CLKCTRL);

	clrsetbits(CM_WKUP_KEYBOARD_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_WKUP_KEYBOARD_CLKCTRL);

	clrsetbits(CM_SDMA_CLKSTCTRL, 0x00000003, 0x0);
	clrsetbits(CM_MEMIF_CLKSTCTRL, 0x00000003, 0x3);

	clrsetbits(CM_MEMIF_EMIF_1_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_MEMIF_EMIF_1_CLKCTRL);

	clrsetbits(CM_MEMIF_EMIF_2_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_MEMIF_EMIF_2_CLKCTRL);

	clrsetbits(CM_D2D_CLKSTCTRL, 0x00000003, 0x3);

	clrsetbits(CM_L3_2_GPMC_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_L3_2_GPMC_CLKCTRL);

	clrsetbits(CM_L3INSTR_L3_3_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_L3INSTR_L3_3_CLKCTRL);

	clrsetbits(CM_L3INSTR_L3_INSTR_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_L3INSTR_L3_INSTR_CLKCTRL);

	clrsetbits(CM_L3INSTR_OCP_WP1_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_L3INSTR_OCP_WP1_CLKCTRL);

	/* WDT clocks */
	clrsetbits(CM_WKUP_WDT2_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_WKUP_WDT2_CLKCTRL);

	/* Select DPLL PER CLOCK as source for SGX FCLK */
	clrsetbits(CM_SGX_SGX_CLKCTRL, 0x01000000, 0x1 << 24);

	/* Enable clocks for USB fast boot to work */
	clrsetbits(CM_L3INIT_USBPHY_CLKCTRL, 0xffffffff, 0x301);
	clrsetbits(CM_L3INIT_HSUSBOTG_CLKCTRL, 0x00000003, 0x1);
}

void
enable_uart_clocks(void)
{
	clrsetbits(CM_L4PER_CLKSTCTRL, 0x00000003, 0x2);

	clrsetbits(CM_L4PER_UART1_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_UART1_CLKCTRL);

	clrsetbits(CM_L4PER_UART2_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_UART2_CLKCTRL);

	clrsetbits(CM_L4PER_UART3_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_UART3_CLKCTRL);

	clrsetbits(CM_L4PER_UART4_CLKCTRL, 0x00000003, 0x2);
	poll(0x30000, 0, CM_L4PER_UART4_CLKCTRL);

	clrsetbits(CM_L4PER_CLKSTCTRL, 0x00000003, 0x3);
}

void
clock_init(void)
{
	uint32_t clksel;

	/* SYS_CLK = 38.4MHz */
	writel(0x7, CM_SYS_CLKSEL);
	clksel = readl(CM_SYS_CLKSEL);

	if (!clksel)
		return;

	/* Configure all DPLL's at 100% OPP */
	configure_mpu_dpll(&mpu_dpll_param_600mhz);
	configure_iva_dpll(&iva_dpll_param);
	configure_per_dpll(&per_dpll_param);
	configure_abe_dpll(&abe_dpll_param);
	configure_usb_dpll(&usb_dpll_param);

	enable_all_clocks();
}

