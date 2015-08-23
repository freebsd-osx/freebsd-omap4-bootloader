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

#include <io.h>
#include <cpu.h>
#include <omap4/emif.h>
#include <omap4/omap4.h>
#include <omap4/ctrlreg.h>
#include <omap4/platform.h>

/* Timing regs for Elpida */
const struct ddr_regs elpida2G_400_mhz = {
	.tim1		= 0x10eb065a,
	.tim2		= 0x20370dd2,
	.tim3		= 0x00b1c33f,
	.phy_ctrl_1	= 0x849ff408,
	.ref_ctrl	= 0x00000618,
	.config_init	= 0x80000eb1,
	.config_final	= 0x80001ab1,
	.zq_config	= 0x500b3215,
	.mr1		= 0x83,
	.mr2		= 0x4
};

/*
 * 400 MHz + 2 CS = 1 GB
 */
const struct ddr_regs elpida2G_400_mhz_2cs = {
	/* tRRD changed from 10ns to 12.5ns because of the tFAW requirement*/
	.tim1		= 0x10eb0662,
	.tim2		= 0x20370dd2,
	.tim3		= 0x00b1c33f,
	.phy_ctrl_1	= 0x049ff408,
	.ref_ctrl	= 0x00000618,
	.config_init	= 0x80800eb9,
	.config_final	= 0x80801ab9,
	.zq_config	= 0xd00b3215,
	.mr1		= 0x83,
	.mr2		= 0x4
};

const struct ddr_regs elpida4G_400_mhz_1cs = {
	.tim1		= 0x10eb0662,
	.tim2		= 0x20370dd2,
	.tim3		= 0x00b1c33f,
	.phy_ctrl_1	= 0x449ff379,
	.ref_ctrl	= 0x00000618,
	.config_init	= 0x80800eb2,
	.config_final	= 0x80801ab2,
	.zq_config	= 0x500b3215,
	.mr1		= 0x83,
	.mr2		= 0x4
};

/*
 * Set Read Latency value to 0xB and DLL delay to 0x37
 * according to OMAP4470 LPDDR interface configuration
 * update for 466 MHz
 */
const struct ddr_regs elpida4G_466_mhz_1cs = {
	.tim1		= 0x130f376b,
	.tim2		= 0x3041105a,
	.tim3		= 0x00f563cf,
#ifdef CORE_233MHZ
	.phy_ctrl_1	= 0x449ff37b,
#else
	.phy_ctrl_1	= 0x449ff408,
#endif
	.ref_ctrl	= 0x0000071b,
	.config_init	= 0x80800eb2,
	.config_final	= 0x80801eb2,
	.zq_config	= 0x500b3215,
	.mr1		= 0x83,
	.mr2		= 0x5
};

const struct ddr_regs elpida2G_380_mhz = {
	.tim1		= 0x10cb061a,
	.tim2		= 0x20350d52,
	.tim3		= 0x00b1431f,
	.phy_ctrl_1	= 0x049ff408,
	.ref_ctrl	= 0x000005ca,
	.config_init	= 0x80800eb1,
	.config_final	= 0x80801ab1,
	.zq_config	= 0x500b3215,
	.mr1		= 0x83,
	.mr2		= 0x4
};

const struct ddr_regs elpida2G_200_mhz = {
	.tim1		= 0x08648309,
	.tim2		= 0x101b06ca,
	.tim3		= 0x0048a19f,
	.phy_ctrl_1	= 0x849ff405,
	.ref_ctrl	= 0x0000030c,
	.config_init	= 0x80000eb1,
	.config_final	= 0x80000eb1,
	.zq_config	= 0x500b3215,
	.mr1		= 0x23,
	.mr2		= 0x1
};

const struct ddr_regs elpida2G_200_mhz_2cs = {
	.tim1		= 0x08648309,
	.tim2		= 0x101b06ca,
	.tim3		= 0x0048a19f,
	.phy_ctrl_1	= 0x049ff405,
	.ref_ctrl	= 0x0000030c,
	.config_init	= 0x80800eb9,
	.config_final	= 0x80800eb9,
	.zq_config	= 0xd00b3215,
	.mr1		= 0x23,
	.mr2		= 0x1
};

void
ddr_init(void)
{
	uint32_t rev;
	const struct ddr_regs *ddr_regs = 0;

	rev = omap_revision();

	if (rev == OMAP4430_ES1_0)
		ddr_regs = &elpida2G_380_mhz;
	else if (rev == OMAP4430_ES2_0)
		ddr_regs = &elpida2G_200_mhz_2cs;
	else if (rev >= OMAP4430_ES2_1 && rev < OMAP4470_ES1_0)
		ddr_regs = &elpida2G_400_mhz_2cs;
	else if (rev >= OMAP4470_ES1_0)
#ifdef CORE_233MHZ
		ddr_regs = &elpida4G_466_mhz_1cs;
#else
		ddr_regs = &elpida4G_400_mhz_1cs;
#endif
	/*
	 * DMM DMM_LISA_MAP_i registers fields description
	 * [31:24] SYS_ADDR
	 * [22:20] SYS_SIZE
	 * [19:18] SDRC_INTLDMM
	 * [17:16] SDRC_ADDRSPC
	 * [9:8] SDRC_MAP
	 * [7:0] SDRC_ADDR
	 */

	/* TRAP for catching accesses to the umapped memory */
	writel(0x80720100, DMM_BASE + DMM_LISA_MAP_0);

	writel(0x00000000, DMM_BASE + DMM_LISA_MAP_2);
	/* TRAP for catching accesses to the memory actually used by TILER */
	writel(0xff020100, DMM_BASE + DMM_LISA_MAP_1);

	if (rev == OMAP4430_ES1_0)
		/* - 512 MB, 128 byte interleaved, EMIF1&2, SDRC_ADDRSPC=0 */
		writel(0x80540300, DMM_BASE + DMM_LISA_MAP_3);
	else if (rev < OMAP4460_ES1_0)
		/* - 1024 MB, 128 byte interleaved, EMIF1&2, SDRC_ADDRSPC=0 */
		writel(0x80640300, DMM_BASE + DMM_LISA_MAP_3);
	else {
		/* - 1024 MB, 128 byte interleaved, EMIF1&2, SDRC_ADDRSPC=0 */
		writel(0x80640300, DMM_BASE + DMM_LISA_MAP_3);

		writel(0x80720100, MA_BASE + DMM_LISA_MAP_0);
		writel(0xff020100, MA_BASE + DMM_LISA_MAP_1);
		writel(0x00000000, MA_BASE + DMM_LISA_MAP_2);
		writel(0x80640300, MA_BASE + DMM_LISA_MAP_3);
	}

	/* Same memory part on both EMIFs */
	emif_init(ddr_regs, ddr_regs);

	/*
	 * Pull Dn enabled for "Weak driver control" on LPDDR
	 * Interface.
	 */
	if (rev >= OMAP4460_ES1_0) {
		writel(0x9c9c9c9c, CONTROL_LPDDR2IO1_0);
		writel(0x9c9c9c9c, CONTROL_LPDDR2IO1_1);
		writel(0x9c989c00, CONTROL_LPDDR2IO1_2);
		writel(0xa0888c03, CONTROL_LPDDR2IO1_3);
		writel(0x9c9c9c9c, CONTROL_LPDDR2IO2_0);
		writel(0x9c9c9c9c, CONTROL_LPDDR2IO2_1);
		writel(0x9c989c00, CONTROL_LPDDR2IO2_2);
		writel(0xa0888c03, CONTROL_LPDDR2IO2_3);
	}

#ifdef CORE_233MHZ
	/*
	 * Slew Rate should be set to "FASTEST" and
	 * Impedance Control to "Drv12":
	 * CONTROL_LPDDR2IOx_2[LPDDR2IO1_GR10_SR] = 0
	 * CONTROL_LPDDR2IOx_2[LPDDR2IO1_GR10_I] = 7
	 * where x=[1-2]
	 */
	if (rev >= OMAP4470_ES1_0) {
		writel(0x9c3c9c00, CONTROL_LPDDR2IO1_2);
		writel(0x9c3c9c00, CONTROL_LPDDR2IO2_2);
	}
#endif

}
