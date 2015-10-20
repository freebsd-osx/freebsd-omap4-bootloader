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

#ifndef _OMAP4_CLOCK_H_
#define _OMAP4_CLOCK_H_

/*
 * Assuming a maximum of 1.5 GHz ARM speed and a minimum of 2 cycles per
 * loop, allow for a minimum of 2 ms wait (in reality the wait will be
 * much more than that)
 */
#define LDELAY		1000000

/* CM_DLL_CTRL */
#define CM_DLL_CTRL_OVERRIDE_SHIFT	0
#define CM_DLL_CTRL_OVERRIDE_MASK	(1 << 0)
#define CM_DLL_CTRL_NO_OVERRIDE		0

/* CM_CLKMODE_DPLL */
#define CM_CLKMODE_DPLL_REGM4XEN_SHIFT		11
#define CM_CLKMODE_DPLL_REGM4XEN_MASK		(1 << 11)
#define CM_CLKMODE_DPLL_LPMODE_EN_SHIFT		10
#define CM_CLKMODE_DPLL_LPMODE_EN_MASK		(1 << 10)
#define CM_CLKMODE_DPLL_RELOCK_RAMP_EN_SHIFT	9
#define CM_CLKMODE_DPLL_RELOCK_RAMP_EN_MASK	(1 << 9)
#define CM_CLKMODE_DPLL_DRIFTGUARD_EN_SHIFT	8
#define CM_CLKMODE_DPLL_DRIFTGUARD_EN_MASK	(1 << 8)
#define CM_CLKMODE_DPLL_RAMP_RATE_SHIFT		5
#define CM_CLKMODE_DPLL_RAMP_RATE_MASK		(0x7 << 5)
#define CM_CLKMODE_DPLL_EN_SHIFT		0
#define CM_CLKMODE_DPLL_EN_MASK			(0x7 << 0)

#define CM_CLKMODE_DPLL_DPLL_EN_SHIFT		0
#define CM_CLKMODE_DPLL_DPLL_EN_MASK		7

#define DPLL_EN_STOP			1
#define DPLL_EN_MN_BYPASS		4
#define DPLL_EN_LOW_POWER_BYPASS	5
#define DPLL_EN_FAST_RELOCK_BYPASS	6
#define DPLL_EN_LOCK			7

/* CM_IDLEST_DPLL fields */
#define ST_DPLL_CLK_MASK		1

/* CM_CLKSEL_DPLL */
#define CM_CLKSEL_DPLL_DPLL_SD_DIV_SHIFT	24
#define CM_CLKSEL_DPLL_DPLL_SD_DIV_MASK		(0xFF << 24)
#define CM_CLKSEL_DPLL_M_SHIFT			8
#define CM_CLKSEL_DPLL_M_MASK			(0x7FF << 8)
#define CM_CLKSEL_DPLL_N_SHIFT			0
#define CM_CLKSEL_DPLL_N_MASK			0x7F
#define CM_CLKSEL_DCC_EN_SHIFT			22
#define CM_CLKSEL_DCC_EN_MASK			(1 << 22)

/* CM_SYS_CLKSEL */
#define CM_SYS_CLKSEL_SYS_CLKSEL_MASK  7

/* CM_CLKSEL_CORE */
#define CLKSEL_CORE_SHIFT	0
#define CLKSEL_L3_SHIFT		4
#define CLKSEL_L4_SHIFT		8

#define CLKSEL_CORE_X2_DIV_1	0
#define CLKSEL_L3_CORE_DIV_2	1
#define CLKSEL_L4_L3_DIV_2	1

/* CM_ABE_PLL_REF_CLKSEL */
#define CM_ABE_PLL_REF_CLKSEL_CLKSEL_SHIFT	0
#define CM_ABE_PLL_REF_CLKSEL_CLKSEL_MASK	1
#define CM_ABE_PLL_REF_CLKSEL_CLKSEL_SYSCLK	0
#define CM_ABE_PLL_REF_CLKSEL_CLKSEL_32KCLK	1

/* CM_BYPCLK_DPLL_IVA */
#define CM_BYPCLK_DPLL_IVA_CLKSEL_SHIFT		0
#define CM_BYPCLK_DPLL_IVA_CLKSEL_MASK		3

#define DPLL_IVA_CLKSEL_CORE_X2_DIV_2		1

/* CM_SHADOW_FREQ_CONFIG1 */
#define SHADOW_FREQ_CONFIG1_FREQ_UPDATE_MASK	1
#define SHADOW_FREQ_CONFIG1_DLL_OVERRIDE_MASK	4
#define SHADOW_FREQ_CONFIG1_DLL_RESET_MASK	8

#define SHADOW_FREQ_CONFIG1_DPLL_EN_SHIFT	8
#define SHADOW_FREQ_CONFIG1_DPLL_EN_MASK	(7 << 8)

#define SHADOW_FREQ_CONFIG1_M2_DIV_SHIFT	11
#define SHADOW_FREQ_CONFIG1_M2_DIV_MASK		(0x1F << 11)

/*CM_<clock_domain>__CLKCTRL */
#define CD_CLKCTRL_CLKTRCTRL_SHIFT		0
#define CD_CLKCTRL_CLKTRCTRL_MASK		3

#define CD_CLKCTRL_CLKTRCTRL_NO_SLEEP		0
#define CD_CLKCTRL_CLKTRCTRL_SW_SLEEP		1
#define CD_CLKCTRL_CLKTRCTRL_SW_WKUP		2
#define CD_CLKCTRL_CLKTRCTRL_HW_AUTO		3


/* CM_<clock_domain>_<module>_CLKCTRL */
#define MODULE_CLKCTRL_MODULEMODE_SHIFT		0
#define MODULE_CLKCTRL_MODULEMODE_MASK		3
#define MODULE_CLKCTRL_IDLEST_SHIFT		16
#define MODULE_CLKCTRL_IDLEST_MASK		(3 << 16)

#define MODULE_CLKCTRL_MODULEMODE_SW_DISABLE		0
#define MODULE_CLKCTRL_MODULEMODE_HW_AUTO		1
#define MODULE_CLKCTRL_MODULEMODE_SW_EXPLICIT_EN	2

#define MODULE_CLKCTRL_IDLEST_FULLY_FUNCTIONAL	0
#define MODULE_CLKCTRL_IDLEST_TRANSITIONING	1
#define MODULE_CLKCTRL_IDLEST_IDLE		2
#define MODULE_CLKCTRL_IDLEST_DISABLED		3

/* CM_L4PER_GPIO4_CLKCTRL */
#define GPIO4_CLKCTRL_OPTFCLKEN_MASK		(1 << 8)

/* CM_L3INIT_HSMMCn_CLKCTRL */
#define HSMMC_CLKCTRL_CLKSEL_MASK		(1 << 24)

/* CM_WKUP_GPTIMER1_CLKCTRL */
#define GPTIMER1_CLKCTRL_CLKSEL_MASK		(1 << 24)

/* CM_CAM_ISS_CLKCTRL */
#define ISS_CLKCTRL_OPTFCLKEN_MASK		(1 << 8)

/* CM_DSS_DSS_CLKCTRL */
#define DSS_CLKCTRL_OPTFCLKEN_MASK		0xF00

/* CM_L3INIT_USBPHY_CLKCTRL */
#define USBPHY_CLKCTRL_OPTFCLKEN_PHY_48M_MASK	8

/* CM_MPU_MPU_CLKCTRL */
#define MPU_CLKCTRL_CLKSEL_EMIF_DIV_MODE_SHIFT	24
#define MPU_CLKCTRL_CLKSEL_EMIF_DIV_MODE_MASK	(1 << 24)
#define MPU_CLKCTRL_CLKSEL_ABE_DIV_MODE_SHIFT	25
#define MPU_CLKCTRL_CLKSEL_ABE_DIV_MODE_MASK	(1 << 25)

/* Clock frequencies */
#define OMAP_SYS_CLK_IND_38_4_MHZ	6

/* PRM_VC_VAL_BYPASS */
#define PRM_VC_I2C_CHANNEL_FREQ_KHZ	400

/* PMIC */
#define SMPS_I2C_SLAVE_ADDR	0x12
/* TWL6030 SMPS */
#define SMPS_REG_ADDR_VCORE1	0x55
#define SMPS_REG_ADDR_VCORE2	0x5B
#define SMPS_REG_ADDR_VCORE3	0x61
/* TWL6032 SMPS */
#define SMPS_REG_ADDR_SMPS1	0x55
#define SMPS_REG_ADDR_SMPS2	0x5B
#define SMPS_REG_ADDR_SMPS5	0x49

#define PHOENIX_SMPS_BASE_VOLT_STD_MODE_UV		607700
#define PHOENIX_SMPS_BASE_VOLT_STD_MODE_WITH_OFFSET_UV	709000

/* TPS */
#define TPS62361_I2C_SLAVE_ADDR		0x60
#define TPS62361_REG_ADDR_SET0		0x0
#define TPS62361_REG_ADDR_SET1		0x1
#define TPS62361_REG_ADDR_SET2		0x2
#define TPS62361_REG_ADDR_SET3		0x3
#define TPS62361_REG_ADDR_CTRL		0x4
#define TPS62361_REG_ADDR_TEMP		0x5
#define TPS62361_REG_ADDR_RMP_CTRL	0x6
#define TPS62361_REG_ADDR_CHIP_ID	0x8
#define TPS62361_REG_ADDR_CHIP_ID_2	0x9

#define TPS62361_BASE_VOLT_MV	500
#define TPS62361_VSEL0_GPIO	7

/* AUXCLKx reg fields */
#define AUXCLK_ENABLE_MASK		(1 << 8)
#define AUXCLK_SRCSELECT_SHIFT		1
#define AUXCLK_SRCSELECT_MASK		(3 << 1)
#define AUXCLK_CLKDIV_SHIFT		16
#define AUXCLK_CLKDIV_MASK		(0xF << 16)

#define AUXCLK_SRCSELECT_SYS_CLK	0
#define AUXCLK_SRCSELECT_CORE_DPLL	1
#define AUXCLK_SRCSELECT_PER_DPLL	2
#define AUXCLK_SRCSELECT_ALTERNATE	3

#define AUXCLK_CLKDIV_2			1
#define AUXCLK_CLKDIV_16		0xF

/* ALTCLKSRC */
#define ALTCLKSRC_MODE_MASK		3
#define ALTCLKSRC_ENABLE_INT_MASK	4
#define ALTCLKSRC_ENABLE_EXT_MASK	8

#define ALTCLKSRC_MODE_ACTIVE		1

#define DPLL_NO_LOCK	0
#define DPLL_LOCK	1

/* Clock Defines */
#define V_OSCK			38400000	/* Clock output from T2 */
#define V_SCLK			V_OSCK

struct omap4_scrm_regs {
	uint32_t revision;           /* 0x0000 */
	uint32_t pad00[63];
	uint32_t clksetuptime;       /* 0x0100 */
	uint32_t pmicsetuptime;      /* 0x0104 */
	uint32_t pad01[2];
	uint32_t altclksrc;          /* 0x0110 */
	uint32_t pad02[2];
	uint32_t c2cclkm;            /* 0x011c */
	uint32_t pad03[56];
	uint32_t extclkreq;          /* 0x0200 */
	uint32_t accclkreq;          /* 0x0204 */
	uint32_t pwrreq;             /* 0x0208 */
	uint32_t pad04[1];
	uint32_t auxclkreq0;         /* 0x0210 */
	uint32_t auxclkreq1;         /* 0x0214 */
	uint32_t auxclkreq2;         /* 0x0218 */
	uint32_t auxclkreq3;         /* 0x021c */
	uint32_t auxclkreq4;         /* 0x0220 */
	uint32_t auxclkreq5;         /* 0x0224 */
	uint32_t pad05[3];
	uint32_t c2cclkreq;          /* 0x0234 */
	uint32_t pad06[54];
	uint32_t auxclk0;            /* 0x0310 */
	uint32_t auxclk1;            /* 0x0314 */
	uint32_t auxclk2;            /* 0x0318 */
	uint32_t auxclk3;            /* 0x031c */
	uint32_t auxclk4;            /* 0x0320 */
	uint32_t auxclk5;            /* 0x0324 */
	uint32_t pad07[54];
	uint32_t rsttime_reg;        /* 0x0400 */
	uint32_t pad08[6];
	uint32_t c2crstctrl;         /* 0x041c */
	uint32_t extpwronrstctrl;    /* 0x0420 */
	uint32_t pad09[59];
	uint32_t extwarmrstst_reg;   /* 0x0510 */
	uint32_t apewarmrstst_reg;   /* 0x0514 */
	uint32_t pad10[1];
	uint32_t c2cwarmrstst_reg;   /* 0x051C */
};
#endif /* !_OMAP4_CLOCK_H_ */
