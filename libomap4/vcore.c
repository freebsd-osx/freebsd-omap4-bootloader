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

#include <boot.h>
#include <io.h>

#include <omap4/hw.h>

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

	val = hscll << PRM_VC_CFG_I2C_CLK_HSCLL_SHIFT |
	      hsclh << PRM_VC_CFG_I2C_CLK_HSCLH_SHIFT |
	      scll << PRM_VC_CFG_I2C_CLK_SCLL_SHIFT |
	      sclh << PRM_VC_CFG_I2C_CLK_SCLH_SHIFT;
	writel(val, PRM_VC_CFG_I2C_CLK);
}

/**
 * omap_vc_bypass_send_value() - Send a data using VC Bypass command
 * addr:	7 bit I2C slave address of the PMIC
 * reg_addr:	I2C register address(8 bit) address in PMIC
 * reg_data:	what 8 bit data to write
 */
static int
omap_vc_bypass_send_value(uint8_t addr, uint8_t reg_addr, uint8_t reg_data)
{
	/*
	 * Unfortunately we need to loop here instead of a defined time
	 * use arbitary large value
	 */
	uint32_t timeout = 0xFFFF;
	uint32_t reg_val;

	addr &= PRM_VC_VAL_BYPASS_SLAVEADDR_MASK;
	reg_addr &= PRM_VC_VAL_BYPASS_REGADDR_MASK;
	reg_data &= PRM_VC_VAL_BYPASS_DATA_MASK;

	/* program VC to send data */
	reg_val = addr << PRM_VC_VAL_BYPASS_SLAVEADDR_SHIFT |
		  reg_addr << PRM_VC_VAL_BYPASS_REGADDR_SHIFT |
		  reg_data << PRM_VC_VAL_BYPASS_DATA_SHIFT;
	writel(reg_val, PRM_VC_VAL_BYPASS);

	/* Signal VC to send data */
	writel(reg_val | PRM_VC_VAL_BYPASS_VALID_BIT, PRM_VC_VAL_BYPASS);

	/* Wait on VC to complete transmission */
	do {
		reg_val = readl(PRM_VC_VAL_BYPASS) &
				PRM_VC_VAL_BYPASS_VALID_BIT;
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

	/* All good.. */
	return (0);
}

static void
scale_tps62361(uint32_t reg, uint32_t val)
{
	/*
	 * Select SET1 in TPS62361:
	 * VSEL1 is grounded on board. So the following selects
	 * VSEL1 = 0 and VSEL0 = 1
	 */

	/* set GPIO-7 data-out 0 */
	gpio_set_value(TPS62361_VSEL0_GPIO, 0);

	omap_vc_bypass_send_value(TPS62361_I2C_SLAVE_ADDR, reg, val);

	/* set GPIO-7 data-out 1 */
	gpio_set_value(TPS62361_VSEL0_GPIO, 1);
}

/**
 * scale_vcore_omap4430() - Scale for OMAP4430
 * rev:	OMAP chip revision
 *
 * PMIC assumed to be used is TWL6030
 */
static void
scale_vcore_omap4430(unsigned int rev)
{
	uint8_t vsel;

	/* vdd_core - VCORE 3 - OPP100 - ES2+: 1.127 */
	vsel = (rev == OMAP4430_ES1_0) ? 0x31 : 0x22;
	omap_vc_bypass_send_value(TWL6030_SRI2C_SLAVE_ADDR,
				  TWL6030_SRI2C_REG_ADDR_VCORE3, vsel);

	/* vdd_mpu - VCORE 1 - OPP100 - ES2+: 1.2027 */
	vsel = (rev == OMAP4430_ES1_0) ? 0x3b : 0x28;
	omap_vc_bypass_send_value(TWL6030_SRI2C_SLAVE_ADDR,
				  TWL6030_SRI2C_REG_ADDR_VCORE1, vsel);

	/* vdd_iva - VCORE 2 - OPP50 - ES2+: 0.950V */
	vsel = (rev == OMAP4430_ES1_0) ? 0x31 : 0x14;
	omap_vc_bypass_send_value(TWL6030_SRI2C_SLAVE_ADDR,
				  TWL6030_SRI2C_REG_ADDR_VCORE2, vsel);
}

/**
 * scale_vcore_omap4460() - Scale for OMAP4460
 * rev:	OMAP chip revision
 *
 * PMIC assumed to be used is TWL6030 + TPS62361
 */
static void
scale_vcore_omap4460(unsigned int rev)
{
	uint32_t volt;

	/* vdd_core - TWL6030 VCORE 1 - OPP100 - 1.127V */
	omap_vc_bypass_send_value(TWL6030_SRI2C_SLAVE_ADDR,
				TWL6030_SRI2C_REG_ADDR_VCORE1, 0x22);

	/* WKUP clocks */
	clrsetbits(CM_WKUP_GPIO1_CLKCTRL, 0x00000003, 0x1);
	poll(0x30000, 0, CM_WKUP_GPIO1_CLKCTRL);

	/* vdd_mpu - TPS62361 - OPP100 - 1.210V (roundup from 1.2V) */
	volt = 1210;
	volt -= TPS62361_BASE_VOLT_MV;
	volt /= 10;
	scale_tps62361(TPS62361_REG_ADDR_SET1, volt);

	/* vdd_iva - TWL6030 VCORE 2 - OPP50  - 0.950V */
	omap_vc_bypass_send_value(TWL6030_SRI2C_SLAVE_ADDR,
				TWL6030_SRI2C_REG_ADDR_VCORE2, 0x14);
}

/**
 * scale_vcore_omap4470() - Scale for OMAP4470
 * rev:	OMAP chip revision
 *
 * PMIC assumed to be used is TWL6032
 */
static void
scale_vcore_omap4470(unsigned int rev)
{
	/* vdd_core - SMPS 2 - OPP100-OV - 1.25V */
	omap_vc_bypass_send_value(TWL6032_SRI2C_SLAVE_ADDR,
				TWL6032_SRI2C_REG_ADDR_SMPS2, 0x2C);

	/* vdd_mpu - SMPS 1 - OPP100 - 1.2027V */
	omap_vc_bypass_send_value(TWL6032_SRI2C_SLAVE_ADDR,
				TWL6032_SRI2C_REG_ADDR_SMPS1, 0x28);

	/* vdd_iva - SMPS 5 - OPP50 - 0.950V */
	omap_vc_bypass_send_value(TWL6032_SRI2C_SLAVE_ADDR,
				TWL6032_SRI2C_REG_ADDR_SMPS5, 0x14);
}

void
scale_vcores(void)
{
	unsigned int rev;

	rev = get_omap_rev();

	/*
	 * Dont use HSMODE, scll=0x60, sclh=0x26
	 * Note on HSMODE = 0:
	 * This allows us to allow a voltage domain to scale while we do i2c
	 * operation for the next domain - Please verify to ensure
	 * adequate delays are present in the case of slower ramp time for PMIC.
	 * This settings allow upto ~100Usec latency covered while i2c operation
	 * is in progress with the above configuration.
	 * Note #2: this latency will also depend on i2c_clk configuration as
	 * well.
	 */
	omap_vc_init(0x00, 0x00, 0x60, 0x26);

	if (rev >= OMAP4470_ES1_0)
		scale_vcore_omap4470(rev);
	else if (rev >= OMAP4460_ES1_0)
		scale_vcore_omap4460(rev);
	else	/* Default OMAP4430 */
		scale_vcore_omap4430(rev);
}
