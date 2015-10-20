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
#include <omap4/clock.h>
#include <omap4/omap_data.h>
#include <omap4/platform.h>

/*
 * Define Master code if there are multiple masters on the I2C_SR bus.
 * Normally not required
 */
#ifndef CONFIG_OMAP_VC_I2C_HS_MCODE
#define CONFIG_OMAP_VC_I2C_HS_MCODE 0x0
#endif

/* Register defines and masks for VC IP Block */
/* PRM_VC_CFG_I2C_MODE */
#define PRM_VC_CFG_I2C_MODE_DFILTEREN_BIT	(0x1 << 6)
#define PRM_VC_CFG_I2C_MODE_SRMODEEN_BIT	(0x1 << 4)
#define PRM_VC_CFG_I2C_MODE_HSMODEEN_BIT	(0x1 << 3)
#define PRM_VC_CFG_I2C_MODE_HSMCODE_SHIFT	0x0
#define PRM_VC_CFG_I2C_MODE_HSMCODE_MASK	0x3

/* PRM_VC_CFG_I2C_CLK */
#define PRM_VC_CFG_I2C_CLK_HSCLL_SHIFT		24
#define PRM_VC_CFG_I2C_CLK_HSCLL_MASK		0xFF
#define PRM_VC_CFG_I2C_CLK_HSCLH_SHIFT		16
#define PRM_VC_CFG_I2C_CLK_HSCLH_MASK		0xFF
#define PRM_VC_CFG_I2C_CLK_SCLH_SHIFT		0
#define PRM_VC_CFG_I2C_CLK_SCLH_MASK		0xFF
#define PRM_VC_CFG_I2C_CLK_SCLL_SHIFT		8
#define PRM_VC_CFG_I2C_CLK_SCLL_MASK		(0xFF << 8)

/* PRM_VC_VAL_BYPASS */
#define PRM_VC_VAL_BYPASS_VALID_BIT		(0x1 << 24)
#define PRM_VC_VAL_BYPASS_SLAVEADDR_SHIFT	0
#define PRM_VC_VAL_BYPASS_SLAVEADDR_MASK	0x7F
#define PRM_VC_VAL_BYPASS_REGADDR_SHIFT		8
#define PRM_VC_VAL_BYPASS_REGADDR_MASK		0xFF
#define PRM_VC_VAL_BYPASS_DATA_SHIFT		16
#define PRM_VC_VAL_BYPASS_DATA_MASK		0xFF

/**
 * omap_vc_init() - Initialization for Voltage controller
 * @speed_khz: I2C buspeed in KHz
 */
static void
omap_vc_init(uint16_t speed_khz)
{
	uint32_t val;
	uint32_t sys_clk_khz, cycles_hi, cycles_low;

	sys_clk_khz = get_sys_clk_freq() / 1000;

	if (speed_khz > 400) {
	//	puts("higher speed requested - throttle to 400Khz\n");
		speed_khz = 400;
	}

	/*
	 * Setup the dedicated I2C controller for Voltage Control
	 * I2C clk - high period 40% low period 60%
	 */
	speed_khz /= 10;
	cycles_hi = sys_clk_khz * 4 / speed_khz;
	cycles_low = sys_clk_khz * 6 / speed_khz;
	/* values to be set in register - less by 5 & 7 respectively */
	cycles_hi -= 5;
	cycles_low -= 7;
	val = (cycles_hi << PRM_VC_CFG_I2C_CLK_SCLH_SHIFT) |
	       (cycles_low << PRM_VC_CFG_I2C_CLK_SCLL_SHIFT);
	writel(val, (*prcm)->prm_vc_cfg_i2c_clk);

	val = CONFIG_OMAP_VC_I2C_HS_MCODE <<
		PRM_VC_CFG_I2C_MODE_HSMCODE_SHIFT;
	/* No HS mode for now */
	val &= ~PRM_VC_CFG_I2C_MODE_HSMODEEN_BIT;
	writel(val, (*prcm)->prm_vc_cfg_i2c_mode);
}

/**
 * omap_vc_bypass_send_value() - Send a data using VC Bypass command
 * @sa:		7 bit I2C slave address of the PMIC
 * @reg_addr:	I2C register address(8 bit) address in PMIC
 * @reg_data:	what 8 bit data to write
 */
int
omap_vc_bypass_send_value(uint8_t sa, uint8_t reg_addr, uint8_t reg_data)
{
	/*
	 * Unfortunately we need to loop here instead of a defined time
	 * use arbitary large value
	 */
	uint32_t timeout = 0xFFFF;
	uint32_t reg_val;

	sa &= PRM_VC_VAL_BYPASS_SLAVEADDR_MASK;
	reg_addr &= PRM_VC_VAL_BYPASS_REGADDR_MASK;
	reg_data &= PRM_VC_VAL_BYPASS_DATA_MASK;

	/* program VC to send data */
	reg_val = sa << PRM_VC_VAL_BYPASS_SLAVEADDR_SHIFT |
	    reg_addr << PRM_VC_VAL_BYPASS_REGADDR_SHIFT |
	    reg_data << PRM_VC_VAL_BYPASS_DATA_SHIFT;
	writel(reg_val, (*prcm)->prm_vc_val_bypass);

	/* Signal VC to send data */
	writel(reg_val | PRM_VC_VAL_BYPASS_VALID_BIT,
				(*prcm)->prm_vc_val_bypass);

	/* Wait on VC to complete transmission */
	do {
		reg_val = readl((*prcm)->prm_vc_val_bypass) &
				PRM_VC_VAL_BYPASS_VALID_BIT;
		if (!reg_val)
			break;

		sdelay(100);
	} while (--timeout);

	/* Optional: cleanup PRM_IRQSTATUS_Ax */
	/* In case we can do something about it in future.. */
	if (!timeout)
		return -1;

	/* All good.. */
	return 0;
}

void
sri2c_init(void)
{
	static int sri2c = 1;

	if (sri2c) {
		omap_vc_init(PRM_VC_I2C_CHANNEL_FREQ_KHZ);
		sri2c = 0;
	}
	return;
}
