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

#ifndef _OMAP4_H_
#define _OMAP4_H_

#define OMAP44XX_L4_CORE_BASE	0x4a000000
#define OMAP44XX_L4_WKUP_BASE	0x4a300000
#define OMAP44XX_L4_PER_BASE	0x48000000

/* CONTROL */
#define OMAP44XX_CTRL_BASE		(OMAP44XX_L4_CORE_BASE + 0x2000)
#define OMAP44XX_CTRL_PADCONF_CORE_BASE	0x4a100000
#define OMAP44XX_CTRL_PADCONF_WKUP_BASE	(OMAP44XX_L4_CORE_BASE + 0x31e000)

#define CONTROL_ID_CODE		(OMAP44XX_CTRL_BASE + 0x204)
#define CONTROL_STATUS		(OMAP44XX_CTRL_BASE + 0x2c4)

/* WatchDog Timers (1 secure, 3 GP) */
#define WD1_BASE		(0x4a322000)
#define WD2_BASE		(0x4a314000)
#define WD3_BASE		(0x40130000)

#define WWPS			0x34     /* r */
#define WSPR			0x48     /* rw */
#define WD_UNLOCK1		0xaaaa
#define WD_UNLOCK2		0x5555

/* OMAP4460 on-die TEMPERATURE SENSOR */
#define CORE_BANDGAP_COUNTER	(OMAP44XX_L4_CORE_BASE + 0x237c)
#define CORE_BANDGAP_CTRL	(OMAP44XX_L4_CORE_BASE + 0x2378)
#define CORE_TEMP_SENSOR	(OMAP44XX_L4_CORE_BASE + 0x232c)
#define CORE_TSHUT_THRESHOLD	(OMAP44XX_L4_CORE_BASE + 0x2384)
#define STD_FUSE_OPP_BGAP	(OMAP44XX_L4_CORE_BASE + 0x2260)
#define STD_FUSE_OPP_DPLL_1	(OMAP44XX_L4_CORE_BASE + 0x2268)

/* PRCM */
#define CM_SYS_CLKSEL		0x4a306110

/* PRM */
#define PRM_BASE			0x4a306000
#define PRM_DEVICE_BASE			(PRM_BASE + 0x1b00)

#define PRM_RSTST			(PRM_DEVICE_BASE + 0x4)
#define PRM_RSTST_WARM_RESET_MASK	0x07ea

/* PRM.WKUP_CM Register */
#define CM_WKUP_CLKSTCTRL		0x4a307800
#define CM_WKUP_L4WKUP_CLKCTRL		0x4a307820
#define CM_WKUP_WDT1_CLKCTRL		0x4a307828
#define CM_WKUP_WDT2_CLKCTRL		0x4a307830
#define CM_WKUP_GPIO1_CLKCTRL		0x4a307838
#define CM_WKUP_TIMER1_CLKCTRL		0x4a307840
#define CM_WKUP_TIMER12_CLKCTRL		0x4a307848
#define CM_WKUP_SYNCTIMER_CLKCTRL	0x4a307850
#define CM_WKUP_USIM_CLKCTRL		0x4a307858
#define CM_WKUP_SARRAM_CLKCTRL		0x4a307860
#define CM_WKUP_KEYBOARD_CLKCTRL	0x4a307878
#define CM_WKUP_RTC_CLKCTRL		0x4a307880
#define CM_WKUP_BANDGAP_CLKCTRL		0x4a307888

/* DEVICE_PRM Register */
#define PRM_VC_VAL_BYPASS               0x4a307ba0
#define PRM_VC_CFG_CHANNEL              0x4a307ba4
#define PRM_VC_CFG_I2C_MODE             0x4a307ba8
#define PRM_VC_CFG_I2C_CLK              0x4a307bac
#define PRM_IRQSTATUS_MPU		0x4a306010

/* SYSCTRL_GENERAL_CORE Register */
#define LDOSRAM_IVA_VOLTAGE_CTRL	0x4a002320
#define LDOSRAM_MPU_VOLTAGE_CTRL	0x4a002324
#define LDOSRAM_CORE_VOLTAGE_CTRL	0x4a002328

/* CM1.CKGEN module Register */
#define CM_CLKSEL_CORE				0x4a004100
#define CM_CLKSEL_ABE				0x4a004108
#define CM_DLL_CTRL				0x4a004110
#define CM_CLKMODE_DPLL_CORE			0x4a004120
#define CM_IDLEST_DPLL_CORE			0x4a004124
#define CM_AUTOIDLE_DPLL_CORE			0x4a004128
#define CM_CLKSEL_DPLL_CORE			0x4a00412c
#define CM_DIV_M2_DPLL_CORE			0x4a004130
#define CM_DIV_M3_DPLL_CORE			0x4a004134
#define CM_DIV_M4_DPLL_CORE			0x4a004138
#define CM_DIV_M5_DPLL_CORE			0x4a00413c
#define CM_DIV_M6_DPLL_CORE			0x4a004140
#define CM_DIV_M7_DPLL_CORE			0x4a004144
#define CM_SSC_DELTAMSTEP_DPLL_CORE		0x4a004148
#define CM_SSC_MODFREQDIV_DPLL_CORE		0x4a00414c
#define CM_EMU_OVERRIDE_DPLL_CORE		0x4a004150
#define CM_CLKMODE_DPLL_MPU			0x4a004160
#define CM_IDLEST_DPLL_MPU			0x4a004164
#define CM_AUTOIDLE_DPLL_MPU			0x4a004168
#define CM_CLKSEL_DPLL_MPU			0x4a00416c
#define CM_DIV_M2_DPLL_MPU			0x4a004170
#define CM_SSC_DELTAMSTEP_DPLL_MPU		0x4a004188
#define CM_SSC_MODFREQDIV_DPLL_MPU		0x4a00418c
#define CM_BYPCLK_DPLL_MPU			0x4a00419c
#define CM_CLKMODE_DPLL_IVA			0x4a0041a0
#define CM_IDLEST_DPLL_IVA			0x4a0041a4
#define CM_AUTOIDLE_DPLL_IVA			0x4a0041a8
#define CM_CLKSEL_DPLL_IVA			0x4a0041ac
#define CM_DIV_M4_DPLL_IVA			0x4a0041b8
#define CM_DIV_M5_DPLL_IVA			0x4a0041bc
#define CM_SSC_DELTAMSTEP_DPLL_IVA		0x4a0041c8
#define CM_SSC_MODFREQDIV_DPLL_IVA		0x4a0041cc
#define CM_BYPCLK_DPLL_IVA			0x4a0041dc
#define CM_CLKMODE_DPLL_ABE			0x4a0041e0
#define CM_IDLEST_DPLL_ABE			0x4a0041e4
#define CM_AUTOIDLE_DPLL_ABE			0x4a0041e8
#define CM_CLKSEL_DPLL_ABE			0x4a0041ec
#define CM_DIV_M2_DPLL_ABE			0x4a0041f0
#define CM_DIV_M3_DPLL_ABE			0x4a0041f4
#define CM_SSC_DELTAMSTEP_DPLL_ABE		0x4a004208
#define CM_SSC_MODFREQDIV_DPLL_ABE		0x4a00420c
#define CM_CLKMODE_DPLL_DDRPHY			0x4a004220
#define CM_IDLEST_DPLL_DDRPHY			0x4a004224
#define CM_AUTOIDLE_DPLL_DDRPHY			0x4a004228
#define CM_CLKSEL_DPLL_DDRPHY			0x4a00422c
#define CM_DIV_M2_DPLL_DDRPHY			0x4a004230
#define CM_DIV_M4_DPLL_DDRPHY			0x4a004238
#define CM_DIV_M5_DPLL_DDRPHY			0x4a00423c
#define CM_DIV_M6_DPLL_DDRPHY			0x4a004240
#define CM_SSC_DELTAMSTEP_DPLL_DDRPHY		0x4a004248
#define CM_SHADOW_FREQ_CONFIG1			0x4a004260
#define CM_MPU_MPU_CLKCTRL			0x4a004320

/* CM1.ABE register offsets */
#define CM1_ABE_CLKSTCTRL		0x4a004500
#define CM1_ABE_L4ABE_CLKCTRL		0x4a004520
#define CM1_ABE_AESS_CLKCTRL		0x4a004528
#define CM1_ABE_PDM_CLKCTRL		0x4a004530
#define CM1_ABE_DMIC_CLKCTRL		0x4a004538
#define CM1_ABE_MCASP_CLKCTRL		0x4a004540
#define CM1_ABE_MCBSP1_CLKCTRL		0x4a004548
#define CM1_ABE_MCBSP2_CLKCTRL		0x4a004550
#define CM1_ABE_MCBSP3_CLKCTRL		0x4a004558
#define CM1_ABE_SLIMBUS_CLKCTRL		0x4a004560
#define CM1_ABE_TIMER5_CLKCTRL		0x4a004568
#define CM1_ABE_TIMER6_CLKCTRL		0x4a004570
#define CM1_ABE_TIMER7_CLKCTRL		0x4a004578
#define CM1_ABE_TIMER8_CLKCTRL		0x4a004580
#define CM1_ABE_WDT3_CLKCTRL		0x4a004588

/* CM1.DSP register offsets */
#define DSP_CLKSTCTRL			0x4a004400
#define	DSP_DSP_CLKCTRL			0x4a004420

/* CM2.CKGEN module registers */
#define CM_CLKSEL_DUCATI_ISS_ROOT		0x4a008100
#define CM_CLKSEL_USB_60MHz			0x4a008104
#define CM_SCALE_FCLK				0x4a008108
#define CM_CORE_DVFS_PERF1			0x4a008110
#define CM_CORE_DVFS_PERF2			0x4a008114
#define CM_CORE_DVFS_PERF3			0x4a008118
#define CM_CORE_DVFS_PERF4			0x4a00811c
#define CM_CORE_DVFS_CURRENT			0x4a008124
#define CM_IVA_DVFS_PERF_TESLA			0x4a008128
#define CM_IVA_DVFS_PERF_IVAHD			0x4a00812c
#define CM_IVA_DVFS_PERF_ABE			0x4a008130
#define CM_IVA_DVFS_CURRENT			0x4a008138
#define CM_CLKMODE_DPLL_PER			0x4a008140
#define CM_IDLEST_DPLL_PER			0x4a008144
#define CM_AUTOIDLE_DPLL_PER			0x4a008148
#define CM_CLKSEL_DPLL_PER			0x4a00814c
#define CM_DIV_M2_DPLL_PER			0x4a008150
#define CM_DIV_M3_DPLL_PER			0x4a008154
#define CM_DIV_M4_DPLL_PER			0x4a008158
#define CM_DIV_M5_DPLL_PER			0x4a00815c
#define CM_DIV_M6_DPLL_PER			0x4a008160
#define CM_DIV_M7_DPLL_PER			0x4a008164
#define CM_SSC_DELTAMSTEP_DPLL_PER		0x4a008168
#define CM_SSC_MODFREQDIV_DPLL_PER		0x4a00816c
#define CM_EMU_OVERRIDE_DPLL_PER		0x4a008170
#define CM_CLKMODE_DPLL_USB			0x4a008180
#define CM_IDLEST_DPLL_USB			0x4a008184
#define CM_AUTOIDLE_DPLL_USB			0x4a008188
#define CM_CLKSEL_DPLL_USB			0x4a00818c
#define CM_DIV_M2_DPLL_USB			0x4a008190
#define CM_SSC_DELTAMSTEP_DPLL_USB		0x4a0081a8
#define CM_SSC_MODFREQDIV_DPLL_USB		0x4a0081ac
#define CM_CLKDCOLDO_DPLL_USB			0x4a0081b4
#define CM_CLKMODE_DPLL_UNIPRO			0x4a0081c0
#define CM_IDLEST_DPLL_UNIPRO			0x4a0081c4
#define CM_AUTOIDLE_DPLL_UNIPRO			0x4a0081c8
#define CM_CLKSEL_DPLL_UNIPRO			0x4a0081cc
#define CM_DIV_M2_DPLL_UNIPRO			0x4a0081d0
#define CM_SSC_DELTAMSTEP_DPLL_UNIPRO		0x4a0081e8
#define CM_SSC_MODFREQDIV_DPLL_UNIPRO		0x4a0081ec

/* CM2.CORE module registers */
#define CM_L3_1_CLKSTCTRL		0x4a008700
#define CM_L3_1_DYNAMICDEP		0x4a008708
#define CM_L3_1_L3_1_CLKCTRL		0x4a008720
#define CM_L3_2_CLKSTCTRL		0x4a008800
#define CM_L3_2_DYNAMICDEP		0x4a008808
#define CM_L3_2_L3_2_CLKCTRL		0x4a008820
#define CM_L3_2_GPMC_CLKCTRL		0x4a008828
#define CM_L3_2_OCMC_RAM_CLKCTRL	0x4a008830
#define CM_DUCATI_CLKSTCTRL		0x4a008900
#define CM_DUCATI_STATICDEP		0x4a008904
#define CM_DUCATI_DYNAMICDEP		0x4a008908
#define CM_DUCATI_DUCATI_CLKCTRL	0x4a008920
#define CM_SDMA_CLKSTCTRL		0x4a008a00
#define CM_SDMA_STATICDEP		0x4a008a04
#define CM_SDMA_DYNAMICDEP		0x4a008a08
#define CM_SDMA_SDMA_CLKCTRL		0x4a008a20
#define CM_MEMIF_CLKSTCTRL		0x4a008b00
#define CM_MEMIF_DMM_CLKCTRL		0x4a008b20
#define CM_MEMIF_EMIF_FW_CLKCTRL	0x4a008b28
#define CM_MEMIF_EMIF_1_CLKCTRL		0x4a008b30
#define CM_MEMIF_EMIF_2_CLKCTRL		0x4a008b38
#define CM_MEMIF_DLL_CLKCTRL		0x4a008b40
#define CM_MEMIF_EMIF_H1_CLKCTRL	0x4a008b50
#define CM_MEMIF_EMIF_H2_CLKCTRL	0x4a008b58
#define CM_MEMIF_DLL_H_CLKCTRL		0x4a008b60
#define CM_D2D_CLKSTCTRL		0x4a008c00
#define CM_D2D_STATICDEP		0x4a008c04
#define CM_D2D_DYNAMICDEP		0x4a008c08
#define CM_D2D_SAD2D_CLKCTRL		0x4a008c20
#define CM_D2D_MODEM_ICR_CLKCTRL	0x4a008c28
#define CM_D2D_SAD2D_FW_CLKCTRL		0x4a008c30
#define CM_L4CFG_CLKSTCTRL		0x4a008d00
#define CM_L4CFG_DYNAMICDEP		0x4a008d08
#define CM_L4CFG_L4_CFG_CLKCTRL		0x4a008d20
#define CM_L4CFG_HW_SEM_CLKCTRL		0x4a008d28
#define CM_L4CFG_MAILBOX_CLKCTRL	0x4a008d30
#define CM_L4CFG_SAR_ROM_CLKCTRL	0x4a008d38
#define CM_L3INSTR_CLKSTCTRL		0x4a008e00
#define CM_L3INSTR_L3_3_CLKCTRL		0x4a008e20
#define CM_L3INSTR_L3_INSTR_CLKCTRL	0x4a008e28
#define CM_L3INSTR_OCP_WP1_CLKCTRL	0x4a008e40

/* CM2.L4PER register offsets */
#define CM_L4PER_CLKSTCTRL		0x4a009400
#define CM_L4PER_DYNAMICDEP		0x4a009408
#define CM_L4PER_ADC_CLKCTRL		0x4a009420
#define CM_L4PER_DMTIMER10_CLKCTRL	0x4a009428
#define CM_L4PER_DMTIMER11_CLKCTRL	0x4a009430
#define CM_L4PER_DMTIMER2_CLKCTRL	0x4a009438
#define CM_L4PER_DMTIMER3_CLKCTRL	0x4a009440
#define CM_L4PER_DMTIMER4_CLKCTRL	0x4a009448
#define CM_L4PER_DMTIMER9_CLKCTRL	0x4a009450
#define CM_L4PER_ELM_CLKCTRL		0x4a009458
#define CM_L4PER_GPIO2_CLKCTRL		0x4a009460
#define CM_L4PER_GPIO3_CLKCTRL		0x4a009468
#define CM_L4PER_GPIO4_CLKCTRL		0x4a009470
#define CM_L4PER_GPIO5_CLKCTRL		0x4a009478
#define CM_L4PER_GPIO6_CLKCTRL		0x4a009480
#define CM_L4PER_HDQ1W_CLKCTRL		0x4a009488
#define CM_L4PER_HECC1_CLKCTRL		0x4a009490
#define CM_L4PER_HECC2_CLKCTRL		0x4a009498
#define CM_L4PER_I2C1_CLKCTRL		0x4a0094a0
#define CM_L4PER_I2C2_CLKCTRL		0x4a0094a8
#define CM_L4PER_I2C3_CLKCTRL		0x4a0094b0
#define CM_L4PER_I2C4_CLKCTRL		0x4a0094b8
#define CM_L4PER_L4PER_CLKCTRL		0x4a0094c0
#define CM_L4PER_MCASP2_CLKCTRL		0x4a0094d0
#define CM_L4PER_MCASP3_CLKCTRL		0x4a0094d8
#define CM_L4PER_MCBSP4_CLKCTRL		0x4a0094e0
#define CM_L4PER_MGATE_CLKCTRL		0x4a0094e8
#define CM_L4PER_MCSPI1_CLKCTRL		0x4a0094f0
#define CM_L4PER_MCSPI2_CLKCTRL		0x4a0094f8
#define CM_L4PER_MCSPI3_CLKCTRL		0x4a009500
#define CM_L4PER_MCSPI4_CLKCTRL		0x4a009508
#define CM_L4PER_MMCSD3_CLKCTRL		0x4a009520
#define CM_L4PER_MMCSD4_CLKCTRL		0x4a009528
#define CM_L4PER_MSPROHG_CLKCTRL	0x4a009530
#define CM_L4PER_SLIMBUS2_CLKCTRL	0x4a009538
#define CM_L4PER_UART1_CLKCTRL		0x4a009540
#define CM_L4PER_UART2_CLKCTRL		0x4a009548
#define CM_L4PER_UART3_CLKCTRL		0x4a009550
#define CM_L4PER_UART4_CLKCTRL		0x4a009558
#define CM_L4PER_MMCSD5_CLKCTRL		0x4a009560
#define CM_L4PER_I2C5_CLKCTRL		0x4a009568
#define CM_L4SEC_CLKSTCTRL		0x4a009580
#define CM_L4SEC_STATICDEP		0x4a009584
#define CM_L4SEC_DYNAMICDEP		0x4a009588
#define CM_L4SEC_AES1_CLKCTRL		0x4a0095a0
#define CM_L4SEC_AES2_CLKCTRL		0x4a0095a8
#define CM_L4SEC_DES3DES_CLKCTRL	0x4a0095b0
#define CM_L4SEC_PKAEIP29_CLKCTRL	0x4a0095b8
#define CM_L4SEC_RNG_CLKCTRL		0x4a0095c0
#define CM_L4SEC_SHA2MD51_CLKCTRL	0x4a0095c8
#define CM_L4SEC_CRYPTODMA_CLKCTRL	0x4a0095d8

/* CM2.IVAHD */
#define IVAHD_CLKSTCTRL			0x4a008f00
#define IVAHD_IVAHD_CLKCTRL		0x4a008f20
#define IVAHD_SL2_CLKCTRL		0x4a008f28

/* CM2.L3INIT */
#define CM_L3INIT_HSMMC1_CLKCTRL	0x4a009328
#define CM_L3INIT_HSMMC2_CLKCTRL	0x4a009330
#define CM_L3INIT_HSI_CLKCTRL           0x4a009338
#define CM_L3INIT_UNIPRO1_CLKCTRL       0x4a009340
#define CM_L3INIT_HSUSBHOST_CLKCTRL     0x4a009358
#define CM_L3INIT_HSUSBOTG_CLKCTRL      0x4a009360
#define CM_L3INIT_HSUSBTLL_CLKCTRL      0x4a009368
#define CM_L3INIT_P1500_CLKCTRL         0x4a009378
#define CM_L3INIT_FSUSB_CLKCTRL         0x4a0093d0
#define CM_L3INIT_USBPHY_CLKCTRL        0x4a0093e0

/* CM2.CAM */
#define CM_CAM_CLKSTCTRL                0x4a009000
#define CM_CAM_ISS_CLKCTRL              0x4a009020
#define CM_CAM_FDIF_CLKCTRL             0x4a009028

/* CM2.DSS */
#define CM_DSS_CLKSTCTRL                0x4a009100
#define CM_DSS_DSS_CLKCTRL              0x4a009120
#define CM_DSS_DEISS_CLKCTRL            0x4a009128

/* PM.DSS */
#define PM_DSS_PWRSTCTRL		0x4a307100

/* CM2.SGX */
#define CM_SGX_CLKSTCTRL                0x4a009200
#define CM_SGX_SGX_CLKCTRL              0x4a009220

/* SCRM */
#define ALTCLKSRC	0x4a30a110
#define AUXCLK1		0x4a30a314
#define AUXCLK3		0x4a30a31c

/* DMM registers */
#define DMM_BASE		0x4e000000
#define MA_BASE			0x482af000

#define DMM_LISA_MAP_0		0x0040
#define DMM_LISA_MAP_1		0x0044
#define DMM_LISA_MAP_2		0x0048
#define DMM_LISA_MAP_3		0x004c

/* PRM_VC_VAL_BYPASS */
#define PRM_VC_I2C_CHANNEL_FREQ_KHZ     400

#define PRM_VC_VAL_BYPASS_VALID_BIT     0x1000000
#define PRM_VC_VAL_BYPASS_SLAVEADDR_SHIFT       0
#define PRM_VC_VAL_BYPASS_SLAVEADDR_MASK        0x7f
#define PRM_VC_VAL_BYPASS_REGADDR_SHIFT         8
#define PRM_VC_VAL_BYPASS_REGADDR_MASK          0xff
#define PRM_VC_VAL_BYPASS_DATA_SHIFT            16
#define PRM_VC_VAL_BYPASS_DATA_MASK             0xff

/* PRM_VC_CFG_I2C_MODE */
#define PRM_VC_CFG_I2C_MODE_DFILTEREN_BIT	(0x1 << 6)
#define PRM_VC_CFG_I2C_MODE_SRMODEEN_BIT	(0x1 << 4)
#define PRM_VC_CFG_I2C_MODE_HSMODEEN_BIT	(0x1 << 3)
#define PRM_VC_CFG_I2C_MODE_HSMCODE_SHIFT	0x0
#define PRM_VC_CFG_I2C_MODE_HSMCODE_MASK	0x3

/* PRM_VC_CFG_I2C_CLK */
#define PRM_VC_CFG_I2C_CLK_HSCLL_SHIFT		24
#define PRM_VC_CFG_I2C_CLK_HSCLL_MASK		0xff
#define PRM_VC_CFG_I2C_CLK_HSCLH_SHIFT		16
#define PRM_VC_CFG_I2C_CLK_HSCLH_MASK		0xff
#define PRM_VC_CFG_I2C_CLK_SCLL_SHIFT		8
#define PRM_VC_CFG_I2C_CLK_SCLL_MASK		0xff
#define PRM_VC_CFG_I2C_CLK_SCLH_SHIFT		0
#define PRM_VC_CFG_I2C_CLK_SCLH_MASK		0xff

/* UART */
#define OMAP44XX_UART1			(OMAP44XX_L4_PER_BASE+0x6a000)
#define OMAP44XX_UART2			(OMAP44XX_L4_PER_BASE+0x6c000)
#define OMAP44XX_UART3			(OMAP44XX_L4_PER_BASE+0x20000)
#define OMAP44XX_UART4			0x4806e000
#endif /* _OMAP4_H_ */
