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
#include <sizes.h>

#include <omap4/boot.h>
#include <omap4/emif.h>
#include <omap4/omap4.h>
#include <omap4/omap_gpio.h>
#include <omap4/omap_data.h>
#include <omap4/watchdog.h>

struct omap_boot_parameters *boot_params  =
		(struct omap_boot_parameters *)OMAP44XX_SCRATCH_BOOT_PARAMS;
uint32_t *const omap_rev = (uint32_t *)OMAP44XX_SCRATCH_OMAP_REV;

static const struct gpio_bank gpio_bank_44xx[6] = {
	{ (void *)OMAP44XX_GPIO1_BASE, METHOD_GPIO_24XX },
	{ (void *)OMAP44XX_GPIO2_BASE, METHOD_GPIO_24XX },
	{ (void *)OMAP44XX_GPIO3_BASE, METHOD_GPIO_24XX },
	{ (void *)OMAP44XX_GPIO4_BASE, METHOD_GPIO_24XX },
	{ (void *)OMAP44XX_GPIO5_BASE, METHOD_GPIO_24XX },
	{ (void *)OMAP44XX_GPIO6_BASE, METHOD_GPIO_24XX },
};

const struct gpio_bank *const omap_gpio_bank = gpio_bank_44xx;

void
do_io_settings(void)
{
	uint32_t lpddr2io;

	uint32_t omap4_rev = omap_revision();

	if (omap4_rev == OMAP4430_ES1_0)
		lpddr2io = CONTROL_LPDDR2IO_SLEW_125PS_DRV8_PULL_DOWN;
	else if (omap4_rev == OMAP4430_ES2_0)
		lpddr2io = CONTROL_LPDDR2IO_SLEW_325PS_DRV8_GATE_KEEPER;
	else
		lpddr2io = CONTROL_LPDDR2IO_SLEW_315PS_DRV12_PULL_DOWN;

	/* EMIF1 */
	writel(lpddr2io, (*ctrl)->control_lpddr2io1_0);
	writel(lpddr2io, (*ctrl)->control_lpddr2io1_1);
	/* No pull for GR10 as per hw team's recommendation */
	writel(lpddr2io & ~LPDDR2IO_GR10_WD_MASK,
		(*ctrl)->control_lpddr2io1_2);
	writel(CONTROL_LPDDR2IO_3_VAL, (*ctrl)->control_lpddr2io1_3);

	/* EMIF2 */
	writel(lpddr2io, (*ctrl)->control_lpddr2io2_0);
	writel(lpddr2io, (*ctrl)->control_lpddr2io2_1);
	/* No pull for GR10 as per hw team's recommendation */
	writel(lpddr2io & ~LPDDR2IO_GR10_WD_MASK,
		(*ctrl)->control_lpddr2io2_2);
	writel(CONTROL_LPDDR2IO_3_VAL, (*ctrl)->control_lpddr2io2_3);

	/*
	 * Some of these settings (TRIM values) come from eFuse and are
	 * in turn programmed in the eFuse at manufacturing time after
	 * calibration of the device. Do the software over-ride only if
	 * the device is not correctly trimmed
	 */
	if (!(readl((*ctrl)->control_std_fuse_opp_bgap) & 0xFFFF)) {

		writel(LDOSRAM_VOLT_CTRL_OVERRIDE,
			(*ctrl)->control_ldosram_iva_voltage_ctrl);

		writel(LDOSRAM_VOLT_CTRL_OVERRIDE,
			(*ctrl)->control_ldosram_mpu_voltage_ctrl);

		writel(LDOSRAM_VOLT_CTRL_OVERRIDE,
			(*ctrl)->control_ldosram_core_voltage_ctrl);
	}

	/*
	 * Over-ride the register
	 *	i. unconditionally for all 4430
	 *	ii. only if un-trimmed for 4460
	 */
	if (!readl((*ctrl)->control_efuse_1))
		writel(CONTROL_EFUSE_1_OVERRIDE, (*ctrl)->control_efuse_1);

	if ((omap4_rev < OMAP4460_ES1_0) || !readl((*ctrl)->control_efuse_2))
		writel(CONTROL_EFUSE_2_OVERRIDE, (*ctrl)->control_efuse_2);
}

static uint32_t
cortex_rev(void)
{
	unsigned int rev;

	/* Read Main ID Register (MIDR) */
	asm("mrc p15, 0, %0, c0, c0, 0" : "=r" (rev));

	return rev;
}

void
omap_revision_init(void)
{
	uint32_t arm_rev = cortex_rev();

	switch (arm_rev) {
	case MIDR_CORTEX_A9_R0P1:
		*omap_rev = OMAP4430_ES1_0;
		break;
	case MIDR_CORTEX_A9_R1P2:
        	switch (readl(CONTROL_ID_CODE)) {
		case OMAP4430_CONTROL_ID_CODE_ES2_0:
			*omap_rev = OMAP4430_ES2_0;
			break;
		case OMAP4430_CONTROL_ID_CODE_ES2_1:
			*omap_rev = OMAP4430_ES2_1;
			break;
		case OMAP4430_CONTROL_ID_CODE_ES2_2:
			*omap_rev = OMAP4430_ES2_2;
			break;
		default:
			*omap_rev = OMAP4430_ES2_0;
        		break;
		}
		break;
	case MIDR_CORTEX_A9_R1P3:
		*omap_rev = OMAP4430_ES2_3;
		break;
	case MIDR_CORTEX_A9_R2P10:
		switch (readl(CONTROL_ID_CODE)) {
		case OMAP4470_CONTROL_ID_CODE_ES1_0:
			*omap_rev = OMAP4470_ES1_0;
			break;
		case OMAP4460_CONTROL_ID_CODE_ES1_1:
			*omap_rev = OMAP4460_ES1_1;
			break;
		case OMAP4460_CONTROL_ID_CODE_ES1_0:
		default:
			*omap_rev = OMAP4460_ES1_0;
			break;
		}
		break;
	default:
		*omap_rev = OMAP4430_ID_INVALID;
		break;
	}
}

void
wait_for_command_complete(struct watchdog *wd_base)
{
	int pending = 1;
	do {
		pending = readl(&wd_base->wwps);
	} while (pending);
}

void
watchdog_init(void)
{
	struct watchdog *wd2_base = (struct watchdog *)WDT2_BASE;

	writel(WD_UNLOCK1, &wd2_base->wspr);
	wait_for_command_complete(wd2_base);
	writel(WD_UNLOCK2, &wd2_base->wspr);
}

/* dummy fuction for omap4 */
void
config_data_eye_leveling_samples(uint32_t emif_base)
{
}

uint32_t
omap_sdram_size(void)
{
	uint32_t section, i, valid;
	uint64_t sdram_start = 0, sdram_end = 0, addr,
	    size, total_size = 0, trap_size = 0, trap_start = 0;

	for (i = 0; i < 4; i++) {
		section	= __raw_readl(DMM_BASE + i*4);
		valid = (section & EMIF_SDRC_ADDRSPC_MASK) >>
			(EMIF_SDRC_ADDRSPC_SHIFT);
		addr = section & EMIF_SYS_ADDR_MASK;

		/* See if the address is valid */
		if ((addr >= TI_ARMV7_DRAM_ADDR_SPACE_START) &&
		    (addr < TI_ARMV7_DRAM_ADDR_SPACE_END)) {
			size = ((section & EMIF_SYS_SIZE_MASK) >>
				   EMIF_SYS_SIZE_SHIFT);
			size = 1 << size;
			size *= SZ_16M;

			if (valid != DMM_SDRC_ADDR_SPC_INVALID) {
				if (!sdram_start || (addr < sdram_start))
					sdram_start = addr;
				if (!sdram_end || ((addr + size) > sdram_end))
					sdram_end = addr + size;
			} else {
				trap_size = size;
				trap_start = addr;
			}
		}
	}

	if ((trap_start >= sdram_start) && (trap_start < sdram_end))
		total_size = (sdram_end - sdram_start) - (trap_size);
	else
		total_size = sdram_end - sdram_start;

	return total_size;
}
