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

#ifndef _EMIF_H_
#define _EMIF_H_

/* EMIF and DMM registers */
#define EMIF1_BASE			0x4c000000
#define EMIF2_BASE			0x4d000000

/* EMIF */
#define EMIF_MOD_ID_REV			0x0000
#define EMIF_STATUS			0x0004
#define EMIF_SDRAM_CONFIG		0x0008
#define EMIF_LPDDR2_NVM_CONFIG		0x000c
#define EMIF_SDRAM_REF_CTRL		0x0010
#define EMIF_SDRAM_REF_CTRL_SHDW	0x0014
#define EMIF_SDRAM_TIM_1		0x0018
#define EMIF_SDRAM_TIM_1_SHDW		0x001c
#define EMIF_SDRAM_TIM_2		0x0020
#define EMIF_SDRAM_TIM_2_SHDW		0x0024
#define EMIF_SDRAM_TIM_3		0x0028
#define EMIF_SDRAM_TIM_3_SHDW		0x002c
#define EMIF_LPDDR2_NVM_TIM		0x0030
#define EMIF_LPDDR2_NVM_TIM_SHDW	0x0034
#define EMIF_PWR_MGMT_CTRL		0x0038
#define EMIF_PWR_MGMT_CTRL_SHDW		0x003c
#define EMIF_LPDDR2_MODE_REG_DATA	0x0040
#define EMIF_LPDDR2_MODE_REG_CFG	0x0050
#define EMIF_L3_CONFIG			0x0054
#define EMIF_L3_CFG_VAL_1		0x0058
#define EMIF_L3_CFG_VAL_2		0x005c
#define IODFT_TLGC			0x0060
#define EMIF_PERF_CNT_1			0x0080
#define EMIF_PERF_CNT_2			0x0084
#define EMIF_PERF_CNT_CFG		0x0088
#define EMIF_PERF_CNT_SEL		0x008c
#define EMIF_PERF_CNT_TIM		0x0090
#define EMIF_READ_IDLE_CTRL		0x0098
#define EMIF_READ_IDLE_CTRL_SHDW	0x009c
#define EMIF_ZQ_CONFIG			0x00c8
#define EMIF_DDR_PHY_CTRL_1		0x00e4
#define EMIF_DDR_PHY_CTRL_1_SHDW	0x00e8
#define EMIF_DDR_PHY_CTRL_2		0x00ec

#define EMIF_PWR_MGMT_CTRL_LP_MODE_MASK		0x00000700
#define EMIF_PWR_MGMT_CTRL_LP_MODE_REFRESH	0x00000200
#define EMIF_PWR_MGMT_CTRL_SR_TIM_MASK		0x000000f0

/* structure for ddr timings */
struct ddr_regs{
	uint32_t tim1;
	uint32_t tim2;
	uint32_t tim3;
	uint32_t phy_ctrl_1;
	uint32_t ref_ctrl;
	uint32_t config_init;
	uint32_t config_final;
	uint32_t zq_config;
	uint8_t mr1;
	uint8_t mr2;
};

void emif_init(const struct ddr_regs*, const struct ddr_regs*);
#endif
