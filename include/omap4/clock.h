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

#define LDELAY	12000000

#define PLL_STOP		1 /* PER & IVA */
#define PLL_MN_POWER_BYPASS	4
#define PLL_LOW_POWER_BYPASS	5 /* MPU, IVA & CORE */
#define PLL_FAST_RELOCK_BYPASS	6 /* CORE */
#define PLL_LOCK		7/* MPU, IVA, CORE & PER */

/* CM_CLKSEL_DPLL */
#define CM_CLKSEL_DPLL_DPLL_SD_DIV_SHIFT	24
#define CM_CLKSEL_DPLL_DPLL_SD_DIV_MASK		(0xFF << 24)
#define CM_CLKSEL_DPLL_M_SHIFT			8
#define CM_CLKSEL_DPLL_M_MASK			(0x7FF << 8)
#define CM_CLKSEL_DPLL_N_SHIFT			0
#define CM_CLKSEL_DPLL_N_MASK			0x7F
#define CM_CLKSEL_DCC_EN_SHIFT			22
#define CM_CLKSEL_DCC_EN_MASK			(1 << 22)

/* CM_MPU_MPU_CLKCTRL */
#define MPU_CLKCTRL_CLKSEL_EMIF_DIV_MODE_SHIFT	24
#define MPU_CLKCTRL_CLKSEL_EMIF_DIV_MODE_MASK	(1 << 24)
#define MPU_CLKCTRL_CLKSEL_ABE_DIV_MODE_SHIFT	25
#define MPU_CLKCTRL_CLKSEL_ABE_DIV_MODE_MASK	(1 << 25)

/* Used to index into DPLL parameter tables */
struct dpll_param {
	unsigned int m;
	unsigned int n;
	unsigned int m2;
	unsigned int m3;
	unsigned int m4;
	unsigned int m5;
	unsigned int m6;
	unsigned int m7;
	unsigned int sd_div;
};

void configure_core_dpll_no_lock(void);
void lock_core_dpll(void);
void lock_core_dpll_shadow(void);
void prcm_init(void);
