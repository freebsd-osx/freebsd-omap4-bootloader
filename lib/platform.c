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

#include <bitset.h>
#include <board.h>
#include <cpu.h>
#include <io.h>
#include <tps62361.h>
#include <twl.h>
#include <omap4/clock.h>
#include <omap4/ctrlreg.h>
#include <omap4/emif.h>
#include <omap4/omap4.h>
#include <omap4/platform.h>

void
sdelay(unsigned long loops)
{
	__asm__ volatile ("1:\n" "subs %0, %1, #1\n"
			  "bne 1b" : "=r" (loops) : "0"(loops));
}

uint32_t
wait_on(uint32_t mask, uint32_t value, uint32_t addr, uint32_t bound)
{
	uint32_t val;
	uint32_t i = 0;

	do {
		++i;
		val = readl(addr) & mask;
		if (val == value)
			return (1);
		if (i == bound)
			return (0);
	} while (1);
}

uint32_t
cortex_a9_rev(void)
{
	uint32_t rev;

	/* Read Main ID Register (MIDR) */
	asm ("mrc p15, 0, %0, c0, c0, 0" : "=r" (rev));

	return (rev);
}

uint32_t
omap_revision(void)
{
	uint32_t rev = cortex_a9_rev();

	switch (rev) {
	case CORTEX_A9_R0P1:
		return (OMAP4430_ES1_0);
	case CORTEX_A9_R1P2:
		rev = readl(CONTROL_ID_CODE);
		switch (rev) {
		case OMAP4430_CONTROL_ID_CODE_ES2_2:
			return (OMAP4430_ES2_2);
		case OMAP4430_CONTROL_ID_CODE_ES2_1:
			return (OMAP4430_ES2_1);
		case OMAP4430_CONTROL_ID_CODE_ES2_0:
			return (OMAP4430_ES2_0);
		default:
			return (OMAP4430_ES2_0);
		}
	case CORTEX_A9_R1P3:
		return (OMAP4430_ES2_3);
	case CORTEX_A9_R2P10:
		rev = readl(CONTROL_ID_CODE);
		switch (rev) {
		case OMAP4460_CONTROL_ID_CODE_ES1_0:
			return (OMAP4460_ES1_0);
		case OMAP4460_CONTROL_ID_CODE_ES1_1:
			return (OMAP4460_ES1_1);
		case OMAP4470_CONTROL_ID_CODE_ES1_0:
			return (OMAP4470_ES1_0);
		default:
			return (OMAP44XX_INVALID);
		}
	default:
		return (OMAP44XX_INVALID);
	}
}

uint32_t
get_device_type(void)
{
	/* GP/EMU/HS/TST stored in CONTROL_STATUS */
	return ((readl(CONTROL_STATUS) & DEVICE_MASK) >> 8);
}

unsigned int
get_boot_mode(void)
{
	/* The boot mode stored in scratchpad */
	return ((*(volatile unsigned int *)(0x4A326004)) & 0xf);
}

unsigned int
get_boot_device(void)
{
	/* The boot device stored in scratchpad */
	return ((*(volatile unsigned int *)(0x4A326000)) & 0xff);
}

unsigned int
raw_boot(void)
{
	if (get_boot_mode() == 1)
		return (1);
	else
		return (0);
}

unsigned int
fat_boot(void)
{
	if (get_boot_mode() == 2)
		return (1);
	else
		return (0);
}

static void
wait_for_command_complete(uint32_t wd_base)
{
	int pending = 1;
	do {
		pending = readl(wd_base + WWPS);
	} while (pending);
}

static void
watchdog_init(void)
{
        writel(WD_UNLOCK1, WD2_BASE + WSPR);
        wait_for_command_complete(WD2_BASE);
        writel(WD_UNLOCK2, WD2_BASE + WSPR);
}

static void
force_emif_self_refresh(void)
{
	unsigned long reg;

	/* Set EMIF1 ddr self refresh mode and clear self refresh timer */
	reg = readl(EMIF1_BASE + EMIF_PWR_MGMT_CTRL);
	reg &= ~EMIF_PWR_MGMT_CTRL_LP_MODE_MASK;
	reg |= EMIF_PWR_MGMT_CTRL_LP_MODE_REFRESH;
	reg &= ~EMIF_PWR_MGMT_CTRL_SR_TIM_MASK;
	writel(reg, EMIF1_BASE + EMIF_PWR_MGMT_CTRL);

	/* Set EMIF2 ddr self refresh mode and clear self refresh timer */
	reg = readl(EMIF2_BASE + EMIF_PWR_MGMT_CTRL);
	reg &= ~EMIF_PWR_MGMT_CTRL_LP_MODE_MASK;
	reg |= EMIF_PWR_MGMT_CTRL_LP_MODE_REFRESH;
	reg &= ~EMIF_PWR_MGMT_CTRL_SR_TIM_MASK;
	writel(reg, EMIF2_BASE + EMIF_PWR_MGMT_CTRL);

	/* dummy read commands to make changes above take effect */
	readl(EMIF1_BASE + EMIF_PWR_MGMT_CTRL);
	readl(EMIF2_BASE + EMIF_PWR_MGMT_CTRL);
}

static uint32_t
warm_reset(void)
{
	return (readl(PRM_RSTST) & PRM_RSTST_WARM_RESET_MASK);
}

static int
omap_vc_bypass_send_value(uint8_t sa, uint8_t reg_addr, uint8_t reg_data)
{
	uint32_t timeout = 0xFFFF;
	uint32_t reg_val;

	sa &= PRM_VC_VAL_BYPASS_SLAVEADDR_MASK;
	reg_addr &= PRM_VC_VAL_BYPASS_REGADDR_MASK;
	reg_data &= PRM_VC_VAL_BYPASS_DATA_MASK;

	/* program VC to send data */
	reg_val = sa << PRM_VC_VAL_BYPASS_SLAVEADDR_SHIFT
			| reg_addr << PRM_VC_VAL_BYPASS_REGADDR_SHIFT
			| reg_data << PRM_VC_VAL_BYPASS_DATA_SHIFT;
	writel(reg_val, PRM_VC_VAL_BYPASS);

	/* Signal VC to send data */
	writel(reg_val | PRM_VC_VAL_BYPASS_VALID_BIT, PRM_VC_VAL_BYPASS);

	/* Wait on VC to complete transmission */
	do {
		reg_val = readl(PRM_VC_VAL_BYPASS) & PRM_VC_VAL_BYPASS_VALID_BIT;
		if (!reg_val)
			break;

		sdelay(100);
	} while (--timeout);

	/* Cleanup PRM int status reg to leave no traces of interrupts */
	reg_val = readl(PRM_IRQSTATUS_MPU);
	writel(reg_val, PRM_IRQSTATUS_MPU);

	/* In case we can do something about it in future.. */
	if (!timeout)
		return (-1);

	return (0);
}

static void
do_scale_tps62361(uint32_t reg, uint32_t val)
{
	uint32_t l = 0;

	/*
	 * Select SET1 in TPS62361:
	 * VSEL1 is grounded on board. So the following selects
	 * VSEL1 = 0 and VSEL0 = 1
	 */

	/* set GPIO-7 direction as output */
	l = readl(0x4A310134);
	l &= ~(1 << TPS62361_VSEL0_GPIO);
	writel(l, 0x4A310134);

	omap_vc_bypass_send_value(TPS62361_I2C_SLAVE_ADDR, reg, val);

	/* set GPIO-7 data-out */
	l = 1 << TPS62361_VSEL0_GPIO;
	writel(l, 0x4A310194);

}

static void
scale_vcore_omap4430(unsigned int rev)
{
	uint8_t vsel;

	/* vdd_core - VCORE 3 - OPP100 - ES2+: 1.127 */
	vsel = (rev == OMAP4430_ES1_0) ? 0x31 : 0x22;
	omap_vc_bypass_send_value(TWL6030_SRI2C_SLAVE_ADDR,
				  TWL6030_SRI2C_REG_ADDR_VCORE3, vsel);

	/* vdd_mpu - VCORE 1 - OPP100 - ES2+: 1.2027 */
	vsel = (rev == OMAP4430_ES1_0) ? 0x3B : 0x28;
	omap_vc_bypass_send_value(TWL6030_SRI2C_SLAVE_ADDR,
				  TWL6030_SRI2C_REG_ADDR_VCORE1, vsel);

	/* vdd_iva - VCORE 2 - OPP50 - ES2+: 0.950V */
	vsel = (rev == OMAP4430_ES1_0) ? 0x31 : 0x14;
	omap_vc_bypass_send_value(TWL6030_SRI2C_SLAVE_ADDR,
				  TWL6030_SRI2C_REG_ADDR_VCORE2, vsel);
}

static void
scale_vcore_omap4460(unsigned int rev)
{
	uint32_t volt;

	/* vdd_core - TWL6030 VCORE 1 - OPP100 - 1.127V */
	omap_vc_bypass_send_value(TWL6030_SRI2C_SLAVE_ADDR,
				  TWL6030_SRI2C_REG_ADDR_VCORE1, 0x22);

	/* vdd_mpu - TPS62361 - OPP100 - 1.210V (roundup from 1.2V) */
	volt = 1210;
	volt -= TPS62361_BASE_VOLT_MV;
	volt /= 10;
	do_scale_tps62361(TPS62361_REG_ADDR_SET1, volt);

	/* vdd_iva - TWL6030 VCORE 2 - OPP50  - 0.950V */
	omap_vc_bypass_send_value(TWL6030_SRI2C_SLAVE_ADDR,
				  TWL6030_SRI2C_REG_ADDR_VCORE2, 0x14);
}

static void
scale_vcore_omap4470(unsigned int rev)
{
#ifdef CORE_233MHZ
        /* vdd_core - SMPS 2 - OPP100-OV - 1.25V */
        omap_vc_bypass_send_value(TWL6032_SRI2C_SLAVE_ADDR,
                                  TWL6032_SRI2C_REG_ADDR_SMPS2, 0x2C);
#else
	/* vdd_core - SMPS 2 - OPP100 - 1.1268V */
	omap_vc_bypass_send_value(TWL6032_SRI2C_SLAVE_ADDR,
				  TWL6032_SRI2C_REG_ADDR_SMPS2, 0x22);
#endif

	/* vdd_mpu - SMPS 1 - OPP100 - 1.2027V */
	omap_vc_bypass_send_value(TWL6032_SRI2C_SLAVE_ADDR,
				  TWL6032_SRI2C_REG_ADDR_SMPS1, 0x28);

	/* vdd_iva - SMPS 5 - OPP50 - 0.950V */
	omap_vc_bypass_send_value(TWL6032_SRI2C_SLAVE_ADDR,
				  TWL6032_SRI2C_REG_ADDR_SMPS5, 0x14);
}

static void
omap_vc_init(uint8_t hscll, uint8_t hsclh, uint8_t scll, uint8_t sclh)
{
	uint32_t val;

	val = 0x00 << PRM_VC_CFG_I2C_MODE_HSMCODE_SHIFT;
	if (hscll || hsclh)
		val |= PRM_VC_CFG_I2C_MODE_HSMODEEN_BIT;

	writel(val, PRM_VC_CFG_I2C_MODE);

	hscll &= PRM_VC_CFG_I2C_CLK_HSCLL_MASK;
	hsclh &= PRM_VC_CFG_I2C_CLK_HSCLH_MASK;

	scll &= PRM_VC_CFG_I2C_CLK_SCLL_MASK;
	sclh &= PRM_VC_CFG_I2C_CLK_SCLH_MASK;

	val = hscll << PRM_VC_CFG_I2C_CLK_HSCLL_SHIFT
		| hsclh << PRM_VC_CFG_I2C_CLK_HSCLH_SHIFT
		| scll << PRM_VC_CFG_I2C_CLK_SCLL_SHIFT
		| sclh << PRM_VC_CFG_I2C_CLK_SCLH_SHIFT;
	writel(val, PRM_VC_CFG_I2C_CLK);
}

static void
scale_vcores(void)
{
	uint32_t rev = omap_revision();

	/* Set VCORE1 = 1.3 V, VCORE2 = VCORE3 = 1.21V */
	omap_vc_init(0x00, 0x00, 0x60, 0x26);
	if (rev >= OMAP4470_ES1_0 && rev <= OMAP4470_ES1_0)
		scale_vcore_omap4470(rev);
	else if (rev >= OMAP4460_ES1_0 && rev <= OMAP4460_ES1_1)
		scale_vcore_omap4460(rev);
	else
		scale_vcore_omap4430(rev);
}

static void
cpu_late_init(void)
{
	uint32_t rev;

	rev = omap_revision();
	if (rev < OMAP4470_ES1_0)
		writel(0x00084000, CONTROL_EFUSE_2);

	int omap4430_condition = ((rev >= OMAP4460_ES1_0)
				&& ((readl(LDOSRAM_IVA_VOLTAGE_CTRL) &  ~(0x3e0)) == 0x0));
	int omap4460_condition = ((rev >= OMAP4430_ES2_2) && (rev < OMAP4460_ES1_0)
				&& (!(readl(LDOSRAM_IVA_VOLTAGE_CTRL))));
	if (omap4430_condition || omap4460_condition) {
		/* Set M factor to max (2.7) */
		writel(0x0401040f, LDOSRAM_IVA_VOLTAGE_CTRL);
		writel(0x0401040f, LDOSRAM_MPU_VOLTAGE_CTRL);
		writel(0x0401040f, LDOSRAM_CORE_VOLTAGE_CTRL);
		if (rev < OMAP4470_ES1_0)
			writel(0x000001c0, CONTROL_EFUSE_1);
	}
}

void
platform_init(void)
{
	if (warm_reset())
		force_emif_self_refresh();

	watchdog_init();
	set_muxconf_regs();

	sdelay(100);

	clrsetbits32(CM_WKUP_GPIO1_CLKCTRL, 0xffffffff, 0x1);
	wait_on(BITSET17 | BITSET16, 0, CM_WKUP_GPIO1_CLKCTRL, LDELAY);

	scale_vcores();

	prcm_init();
	ddr_init();

	cpu_late_init();
}
