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

#include <io.h>
#include <cpu.h>
#include <omap4/omap4.h>
#include <omap4/emif.h>
#include <omap4/clock.h>
#include <omap4/ctrlreg.h>
#include <omap4/platform.h>

#define MR0_ADDR			0
#define MR1_ADDR			1
#define MR2_ADDR			2
#define MR4_ADDR			4
#define MR10_ADDR			10
#define MR16_ADDR			16
#define REF_EN				0x40000000

/* defines for MR1 */
#define MR1_BL4				2
#define MR1_BL8				3
#define MR1_BL16			4

#define MR1_BT_SEQ			0
#define BT_INT				1

#define MR1_WC				0
#define MR1_NWC				1

#define MR1_NWR3			1
#define MR1_NWR4			2
#define MR1_NWR5			3
#define MR1_NWR6			4
#define MR1_NWR7			5
#define MR1_NWR8			6

#define MR1_VALUE	(MR1_NWR3 << 5) | (MR1_WC << 4) | \
			(MR1_BT_SEQ << 3) | (MR1_BL8 << 0)

/* defines for MR2 */
#define MR2_RL3_WL1			1
#define MR2_RL4_WL2			2
#define MR2_RL5_WL2			3
#define MR2_RL6_WL3			4

/* defines for MR10 */
#define MR10_ZQINIT			0xff
#define MR10_ZQRESET			0xc3
#define MR10_ZQCL			0xab
#define MR10_ZQCS			0x56

/*
 * EMIF Needs to be configured@19.2 MHz and shadow registers
 * should be programmed for new OPP.
 */

/* Elpida 2x2Gbit */
#define SDRAM_CONFIG_INIT		0x80800eB1
#define DDR_PHY_CTRL_1_INIT		0x849ffff5
#define READ_IDLE_CTRL			0x000501ff
#define PWR_MGMT_CTRL			0x4000000f
#define PWR_MGMT_CTRL_OPP100		0x4000000f
#define ZQ_CONFIG			0x500b3215

#define CS1_MR(mr)	((mr) | 0x80000000)

void
reset_phy(uint32_t base)
{
	writel(readl(base + IODFT_TLGC) | (1 << 10), base + IODFT_TLGC);
}

static void
emif_config(uint32_t base, const struct ddr_regs *ddr_regs)
{
	uint32_t reg_value;

	/*
	 * Set SDRAM CONFIG register
	 * EMIF_SDRAM_CONFIG[31:29] REG_SDRAM_TYPE = 4 for LPDDR2-S4
	 * EMIF_SDRAM_CONFIG[28:27] REG_IBANK_POS = 0
	 * EMIF_SDRAM_CONFIG[13:10] REG_CL = 3
	 * EMIF_SDRAM_CONFIG[6:4] REG_IBANK = 3 - 8 banks
	 * EMIF_SDRAM_CONFIG[3] REG_EBANK = 0 - CS0
 	 * EMIF_SDRAM_CONFIG[2:0] REG_PAGESIZE = 2  - 512- 9 column
	 * JDEC specs - S4-2Gb --8 banks -- R0-R13, C0-c8
	 */
	writel(readl(base + EMIF_LPDDR2_NVM_CONFIG) & 0xbfffffff,
			base + EMIF_LPDDR2_NVM_CONFIG);
	writel(ddr_regs->config_init, base + EMIF_SDRAM_CONFIG);

	/* PHY control values */
	writel(DDR_PHY_CTRL_1_INIT, base + EMIF_DDR_PHY_CTRL_1);
	writel(ddr_regs->phy_ctrl_1, base + EMIF_DDR_PHY_CTRL_1_SHDW);

	/* EMIF_READ_IDLE_CTRL */
	writel(READ_IDLE_CTRL, base + EMIF_READ_IDLE_CTRL);
	writel(READ_IDLE_CTRL, base + EMIF_READ_IDLE_CTRL_SHDW);

	/* EMIF_SDRAM_TIM_1 */
	writel(ddr_regs->tim1, base + EMIF_SDRAM_TIM_1);
	writel(ddr_regs->tim1, base + EMIF_SDRAM_TIM_1_SHDW);

	/* EMIF_SDRAM_TIM_2 */
	writel(ddr_regs->tim2, base + EMIF_SDRAM_TIM_2);
	writel(ddr_regs->tim2, base + EMIF_SDRAM_TIM_2_SHDW);

	/* EMIF_SDRAM_TIM_3 */
	writel(ddr_regs->tim3, base + EMIF_SDRAM_TIM_3);
	writel(ddr_regs->tim3, base + EMIF_SDRAM_TIM_3_SHDW);

	/*
	 * Poll MR0 register (DAI bit)
	 * REG_CS[31] = 0 -- Mode register command to CS0
	 * REG_REFRESH_EN[30] = 1 -- Refresh enable after MRW
	 * REG_ADDRESS[7:0] = 00 -- Refresh enable after MRW
	 */

	writel(MR0_ADDR, base + EMIF_LPDDR2_MODE_REG_CFG);
	do {
		reg_value = readl(base + EMIF_LPDDR2_MODE_REG_DATA);
	} while ((reg_value & 0x1) != 0);

	writel(CS1_MR(MR0_ADDR), base + EMIF_LPDDR2_MODE_REG_CFG);
	do {
		reg_value = readl(base + EMIF_LPDDR2_MODE_REG_DATA);
	} while ((reg_value & 0x1) != 0);


	/* Set MR10 register */
	writel(MR10_ADDR, base + EMIF_LPDDR2_MODE_REG_CFG);
	writel(MR10_ZQINIT, base + EMIF_LPDDR2_MODE_REG_DATA);

	/* Wait for tZQINIT=1us */
	sdelay(2000); /* value for up to 2GHz MPU spin */

	writel(CS1_MR(MR10_ADDR), base + EMIF_LPDDR2_MODE_REG_CFG);
	writel(MR10_ZQINIT, base + EMIF_LPDDR2_MODE_REG_DATA);

	/* Wait for tZQINIT=1us  */
	sdelay(2000); /* value for up to 2GHz MPU spin */

	writel(ddr_regs->zq_config, base + EMIF_ZQ_CONFIG);

	/* Set MR1 register */
	writel(MR1_ADDR, base + EMIF_LPDDR2_MODE_REG_CFG);
	writel(ddr_regs->mr1, base + EMIF_LPDDR2_MODE_REG_DATA);
	writel(CS1_MR(MR1_ADDR), base + EMIF_LPDDR2_MODE_REG_CFG);
	writel(ddr_regs->mr1, base + EMIF_LPDDR2_MODE_REG_DATA);


	/* set MR2 register RL=6 for OPP100 */
	writel(MR2_ADDR, base + EMIF_LPDDR2_MODE_REG_CFG);
	writel(ddr_regs->mr2, base + EMIF_LPDDR2_MODE_REG_DATA);
	writel(CS1_MR(MR2_ADDR), base + EMIF_LPDDR2_MODE_REG_CFG);
	writel(ddr_regs->mr2, base + EMIF_LPDDR2_MODE_REG_DATA);

	/* Set SDRAM CONFIG register again here with final RL-WL value */
	writel(ddr_regs->config_final, base + EMIF_SDRAM_CONFIG);
	writel(ddr_regs->phy_ctrl_1, base + EMIF_DDR_PHY_CTRL_1);

	/*
	 * EMIF_SDRAM_REF_CTRL
	 * refresh rate = DDR_CLK / reg_refresh_rate
	 * 3.9 uS = (400MHz)	/ reg_refresh_rate
	 */
	writel(ddr_regs->ref_ctrl, base + EMIF_SDRAM_REF_CTRL);
	writel(ddr_regs->ref_ctrl, base + EMIF_SDRAM_REF_CTRL_SHDW);

	/* set MR16 register */
	writel(MR16_ADDR | REF_EN, base + EMIF_LPDDR2_MODE_REG_CFG);
	writel(0, base + EMIF_LPDDR2_MODE_REG_DATA);
	writel(CS1_MR(MR16_ADDR | REF_EN), base + EMIF_LPDDR2_MODE_REG_CFG);
	writel(0, base + EMIF_LPDDR2_MODE_REG_DATA);
	/* LPDDR2 init complete */
}

void
emif_init(const struct ddr_regs *emif1_ddr_regs,
		const struct ddr_regs *emif2_ddr_regs)
{
	uint32_t rev;
	rev = omap_revision();

	if (rev == OMAP4430_ES1_0) {
		/* 0x1c1c1c1c: slew 125ps drv8 pull down */
		writel(0x1c1c1c1c, CONTROL_LPDDR2IO1_0);
		writel(0x1c1c1c1c, CONTROL_LPDDR2IO1_1);
		writel(0x1c1c1c1c, CONTROL_LPDDR2IO1_2);
		writel(0x1c1c1c1c, CONTROL_LPDDR2IO2_0);
		writel(0x1c1c1c1c, CONTROL_LPDDR2IO2_1);
		writel(0x1c1c1c1c, CONTROL_LPDDR2IO2_2);
		/* LPDDR2IO set to NMOS PTV */
		writel(0x00ffc000, CONTROL_EFUSE_2);
	} else if (rev == OMAP4430_ES2_0) {
		/* 0x9e9e9e9e: slew 325ps drv8 gate keeper */
		writel(0x9e9e9e9e, CONTROL_LPDDR2IO1_0);
		writel(0x9e9e9e9e, CONTROL_LPDDR2IO1_1);
		writel(0x9e9e9e9e, CONTROL_LPDDR2IO1_2);
		writel(0x9e9e9e9e, CONTROL_LPDDR2IO2_0);
		writel(0x9e9e9e9e, CONTROL_LPDDR2IO2_1);
		writel(0x9e9e9e9e, CONTROL_LPDDR2IO2_2);
		/* LPDDR2IO set to NMOS PTV */
		writel(0x00ffc000, CONTROL_EFUSE_2);
	} else if (rev >= OMAP4430_ES2_1) {
		/* 0x7c7c7c7c: slew 315ps drv12 pull down */
		writel(0x7c7c7c7c, CONTROL_LPDDR2IO1_0);
		writel(0x7c7c7c7c, CONTROL_LPDDR2IO1_0);
		writel(0x7c787c00, CONTROL_LPDDR2IO1_2);
		writel(0x7c7c7c7c, CONTROL_LPDDR2IO2_0);
		writel(0x7c7c7c7c, CONTROL_LPDDR2IO2_1);
		writel(0x7c787c00, CONTROL_LPDDR2IO2_2);

		writel(0xa388bc03, CONTROL_LPDDR2IO1_3);
		writel(0xa388bc03, CONTROL_LPDDR2IO2_3);
	}

	/*
	 * DDR needs to be initialised @ 19.2 MHz
	 * So put core DPLL in bypass mode
	 * Configure the Core DPLL but don't lock it
	 */
	configure_core_dpll_no_lock();

	/* No IDLE: BUG in SDC */
	writel(0x0, EMIF1_BASE + EMIF_PWR_MGMT_CTRL);
	writel(0x0, EMIF2_BASE + EMIF_PWR_MGMT_CTRL);

	/* Configure EMIF1 */
	emif_config(EMIF1_BASE, emif1_ddr_regs);

	/* Configure EMIF2 */
	emif_config(EMIF2_BASE, emif2_ddr_regs);
	/* Lock Core using shadow CM_SHADOW_FREQ_CONFIG1 */
	lock_core_dpll_shadow();
	/* TODO: SDC needs few hacks to get DDR freq update working */

	/* Set DLL_OVERRIDE = 0 */
	writel(0x0, CM_DLL_CTRL);

	sdelay(200);

	/* Check for DDR PHY ready for EMIF1 & EMIF2 */
	while (((readl(EMIF1_BASE + EMIF_STATUS) & 0x04) != 0x04) ||
	       ((readl(EMIF2_BASE + EMIF_STATUS) & 0x04) != 0x04));

	/* Reprogram the DDR PYHY Control register */
	/* PHY control values */
	clrsetbits32(CM_MEMIF_EMIF_1_CLKCTRL, 0xffffffff, 0x1);
        clrsetbits32(CM_MEMIF_EMIF_2_CLKCTRL, 0xffffffff, 0x1);

	/* Put the Core Subsystem PD to ON State */

	/* No IDLE: BUG in SDC */
	writel(0x80000000, EMIF1_BASE + EMIF_PWR_MGMT_CTRL);
	writel(0x80000000, EMIF2_BASE + EMIF_PWR_MGMT_CTRL);

	if (omap_revision() >= OMAP4460_ES1_0) {
		writel(0x0a300000, EMIF1_BASE + EMIF_L3_CONFIG);
		writel(0x0a300000, EMIF2_BASE + EMIF_L3_CONFIG);
	} else {
		writel(0x0a0000ff, EMIF1_BASE + EMIF_L3_CONFIG);
		writel(0x0a0000ff, EMIF2_BASE + EMIF_L3_CONFIG);
	}

	reset_phy(EMIF1_BASE);
	reset_phy(EMIF2_BASE);
}
