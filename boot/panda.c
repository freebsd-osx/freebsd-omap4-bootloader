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

#include <boot.h>
#include <io.h>
#include <mux.h>

#include <omap4/hw.h>
#include <omap4/padconf.h>

#include "util.h"

unsigned console = OMAP44XX_UART3;

static struct storage stor;

void
mux_init(void)
{
	mux(CONTROL_PADCONF_GPMC_AD0, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* sdmmc2_dat0 */
	mux(CONTROL_PADCONF_GPMC_AD1, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* sdmmc2_dat1 */
	mux(CONTROL_PADCONF_GPMC_AD2, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* sdmmc2_dat2 */
	mux(CONTROL_PADCONF_GPMC_AD3, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* sdmmc2_dat3 */
	mux(CONTROL_PADCONF_GPMC_AD4, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* sdmmc2_dat4 */
	mux(CONTROL_PADCONF_GPMC_AD5, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* sdmmc2_dat5 */
	mux(CONTROL_PADCONF_GPMC_AD6, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* sdmmc2_dat6 */
	mux(CONTROL_PADCONF_GPMC_AD7, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* sdmmc2_dat7 */
	mux(CONTROL_PADCONF_GPMC_AD8, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M3));	/* gpio_32 */
	mux(CONTROL_PADCONF_GPMC_AD9, (PTU | IEN | M3));	/* gpio_33 */
	mux(CONTROL_PADCONF_GPMC_AD10, (PTU | IEN | M3));	/* gpio_34 */
	mux(CONTROL_PADCONF_GPMC_AD11, (PTU | IEN | M3));	/* gpio_35 */
	mux(CONTROL_PADCONF_GPMC_AD12, (PTU | IEN | M3));	/* gpio_36 */
	mux(CONTROL_PADCONF_GPMC_AD13, (PTD | OFF_EN | OFF_PD | OFF_OUT_PTD | M3));	/* gpio_37 */
	mux(CONTROL_PADCONF_GPMC_AD14, (PTD | OFF_EN | OFF_PD | OFF_OUT_PTD | M3));	/* gpio_38 */
	mux(CONTROL_PADCONF_GPMC_AD15, (PTD | OFF_EN | OFF_PD | OFF_OUT_PTD | M3));	/* gpio_39 */
	mux(CONTROL_PADCONF_GPMC_A16, (M3));		/* gpio_40 */
	mux(CONTROL_PADCONF_GPMC_A17, (PTD | M3));	/* gpio_41 */
	mux(CONTROL_PADCONF_GPMC_A18, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* kpd_row6 */
	mux(CONTROL_PADCONF_GPMC_A19, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* kpd_row7 */
	mux(CONTROL_PADCONF_GPMC_A20, (IEN | M3));	/* gpio_44 */
	mux(CONTROL_PADCONF_GPMC_A21, (M3));		/* gpio_45 */
	mux(CONTROL_PADCONF_GPMC_A22, (M3));		/* gpio_46 */
	mux(CONTROL_PADCONF_GPMC_A23, (OFF_EN | OFF_PD | OFF_IN | M1));	/* kpd_col7 */
	mux(CONTROL_PADCONF_GPMC_A24, (PTD | M3));	/* gpio_48 */
	mux(CONTROL_PADCONF_GPMC_A25, (PTD | M3));	/* gpio_49 */
	mux(CONTROL_PADCONF_GPMC_NCS0, (M3));		/* gpio_50 */
	mux(CONTROL_PADCONF_GPMC_NCS1, (IEN | M3));	/* gpio_51 */
	mux(CONTROL_PADCONF_GPMC_NCS2, (IEN | M3));	/* gpio_52 */
	mux(CONTROL_PADCONF_GPMC_NCS3, (IEN | M3));	/* gpio_53 */
	mux(CONTROL_PADCONF_GPMC_NWP, (M3));		/* gpio_54 */
	mux(CONTROL_PADCONF_GPMC_CLK, (PTD | M3));	/* gpio_55 */
	mux(CONTROL_PADCONF_GPMC_NADV_ALE, (M3));	/* gpio_56 */
	mux(CONTROL_PADCONF_GPMC_NOE, (PTU | IEN | OFF_EN | OFF_OUT_PTD | M1));		/* sdmmc2_clk */
	mux(CONTROL_PADCONF_GPMC_NWE, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* sdmmc2_cmd */
	mux(CONTROL_PADCONF_GPMC_NBE0_CLE, (M3));		/* gpio_59 */
	mux(CONTROL_PADCONF_GPMC_NBE1, (PTD | M3));		/* gpio_60 */
	mux(CONTROL_PADCONF_GPMC_WAIT0, (PTU | IEN | M3));	/* gpio_61 */
	mux(CONTROL_PADCONF_GPMC_WAIT1, (PTD | OFF_EN | OFF_PD | OFF_OUT_PTD | M3));	/* gpio_62 */
	mux(CONTROL_PADCONF_C2C_DATA11, (PTD | M3));		/* gpio_100 */
	mux(CONTROL_PADCONF_C2C_DATA12, (PTU | IEN | M3));	/* gpio_101 */
	mux(CONTROL_PADCONF_C2C_DATA13, (PTD | M3));		/* gpio_102 */
	mux(CONTROL_PADCONF_C2C_DATA14, (M1));			/* dsi2_te0 */
	mux(CONTROL_PADCONF_C2C_DATA15, (PTD | M3));		/* gpio_104 */
	mux(CONTROL_PADCONF_HDMI_HPD, (M0));	/* hdmi_hpd */
	mux(CONTROL_PADCONF_HDMI_CEC, (M0));	/* hdmi_cec */
	mux(CONTROL_PADCONF_HDMI_DDC_SCL, (PTU | M0));		/* hdmi_ddc_scl */
	mux(CONTROL_PADCONF_HDMI_DDC_SDA, (PTU | IEN | M0));	/* hdmi_ddc_sda */
	mux(CONTROL_PADCONF_CSI21_DX0, (IEN | M0));	/* csi21_dx0 */
	mux(CONTROL_PADCONF_CSI21_DY0, (IEN | M0));	/* csi21_dy0 */
	mux(CONTROL_PADCONF_CSI21_DX1, (IEN | M0));	/* csi21_dx1 */
	mux(CONTROL_PADCONF_CSI21_DY1, (IEN | M0));	/* csi21_dy1 */
	mux(CONTROL_PADCONF_CSI21_DX2, (IEN | M0));	/* csi21_dx2 */
	mux(CONTROL_PADCONF_CSI21_DY2, (IEN | M0));	/* csi21_dy2 */
	mux(CONTROL_PADCONF_CSI21_DX3, (PTD | M7));	/* csi21_dx3 */
	mux(CONTROL_PADCONF_CSI21_DY3, (PTD | M7));	/* csi21_dy3 */
	mux(CONTROL_PADCONF_CSI21_DX4, (PTD | OFF_EN | OFF_PD | OFF_IN | M7));	/* csi21_dx4 */
	mux(CONTROL_PADCONF_CSI21_DY4, (PTD | OFF_EN | OFF_PD | OFF_IN | M7));	/* csi21_dy4 */
	mux(CONTROL_PADCONF_CSI22_DX0, (IEN | M0));	/* csi22_dx0 */
	mux(CONTROL_PADCONF_CSI22_DY0, (IEN | M0));	/* csi22_dy0 */
	mux(CONTROL_PADCONF_CSI22_DX1, (IEN | M0));	/* csi22_dx1 */
	mux(CONTROL_PADCONF_CSI22_DY1, (IEN | M0));	/* csi22_dy1 */
	mux(CONTROL_PADCONF_CAM_SHUTTER, (OFF_EN | OFF_PD | OFF_OUT_PTD | M0));	/* cam_shutter */
	mux(CONTROL_PADCONF_CAM_STROBE, (OFF_EN | OFF_PD | OFF_OUT_PTD | M0));	/* cam_strobe */
	mux(CONTROL_PADCONF_CAM_GLOBALRESET, (PTD | OFF_EN | OFF_PD | OFF_OUT_PTD | M3));	/* gpio_83 */
	mux(CONTROL_PADCONF_USBB1_ULPITLL_CLK, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M4));	/* usbb1_ulpiphy_clk */
	mux(CONTROL_PADCONF_USBB1_ULPITLL_STP, (OFF_EN | OFF_OUT_PTD | M4));		/* usbb1_ulpiphy_stp */
	mux(CONTROL_PADCONF_USBB1_ULPITLL_DIR, (IEN | OFF_EN | OFF_PD | OFF_IN | M4));	/* usbb1_ulpiphy_dir */
	mux(CONTROL_PADCONF_USBB1_ULPITLL_NXT, (IEN | OFF_EN | OFF_PD | OFF_IN | M4));	/* usbb1_ulpiphy_nxt */
	mux(CONTROL_PADCONF_USBB1_ULPITLL_DAT0, (IEN | OFF_EN | OFF_PD | OFF_IN | M4));	/* usbb1_ulpiphy_dat0 */
	mux(CONTROL_PADCONF_USBB1_ULPITLL_DAT1, (IEN | OFF_EN | OFF_PD | OFF_IN | M4));	/* usbb1_ulpiphy_dat1 */
	mux(CONTROL_PADCONF_USBB1_ULPITLL_DAT2, (IEN | OFF_EN | OFF_PD | OFF_IN | M4));	/* usbb1_ulpiphy_dat2 */
	mux(CONTROL_PADCONF_USBB1_ULPITLL_DAT3, (IEN | OFF_EN | OFF_PD | OFF_IN | M4));	/* usbb1_ulpiphy_dat3 */
	mux(CONTROL_PADCONF_USBB1_ULPITLL_DAT4, (IEN | OFF_EN | OFF_PD | OFF_IN | M4));	/* usbb1_ulpiphy_dat4 */
	mux(CONTROL_PADCONF_USBB1_ULPITLL_DAT5, (IEN | OFF_EN | OFF_PD | OFF_IN | M4));	/* usbb1_ulpiphy_dat5 */
	mux(CONTROL_PADCONF_USBB1_ULPITLL_DAT6, (IEN | OFF_EN | OFF_PD | OFF_IN | M4));	/* usbb1_ulpiphy_dat6 */
	mux(CONTROL_PADCONF_USBB1_ULPITLL_DAT7, (IEN | OFF_EN | OFF_PD | OFF_IN | M4));	/* usbb1_ulpiphy_dat7 */
	mux(CONTROL_PADCONF_USBB1_HSIC_DATA, (IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* usbb1_hsic_data */
	mux(CONTROL_PADCONF_USBB1_HSIC_STROBE, (IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* usbb1_hsic_strobe */
	mux(CONTROL_PADCONF_USBC1_ICUSB_DP, (IEN | M0));	/* usbc1_icusb_dp */
	mux(CONTROL_PADCONF_USBC1_ICUSB_DM, (IEN | M0));	/* usbc1_icusb_dm */
	mux(CONTROL_PADCONF_SDMMC1_CLK, (PTU | OFF_EN | OFF_OUT_PTD | M0));		/* sdmmc1_clk */
	mux(CONTROL_PADCONF_SDMMC1_CMD, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc1_cmd */
	mux(CONTROL_PADCONF_SDMMC1_DAT0, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc1_dat0 */
	mux(CONTROL_PADCONF_SDMMC1_DAT1, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc1_dat1 */
	mux(CONTROL_PADCONF_SDMMC1_DAT2, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc1_dat2 */
	mux(CONTROL_PADCONF_SDMMC1_DAT3, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc1_dat3 */
	mux(CONTROL_PADCONF_SDMMC1_DAT4, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc1_dat4 */
	mux(CONTROL_PADCONF_SDMMC1_DAT5, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc1_dat5 */
	mux(CONTROL_PADCONF_SDMMC1_DAT6, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc1_dat6 */
	mux(CONTROL_PADCONF_SDMMC1_DAT7, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc1_dat7 */
	mux(CONTROL_PADCONF_ABE_MCBSP2_CLKX, (PTU | IEN | M3));	/* gpio_110 */
	mux(CONTROL_PADCONF_ABE_MCBSP2_DR, (IEN | OFF_EN | OFF_OUT_PTD | M0));		/* abe_mcbsp2_dr */
	mux(CONTROL_PADCONF_ABE_MCBSP2_DX, (OFF_EN | OFF_OUT_PTD | M0));		/* abe_mcbsp2_dx */
	mux(CONTROL_PADCONF_ABE_MCBSP2_FSX, (PTU | IEN | M3));	/* gpio_113 */
	mux(CONTROL_PADCONF_ABE_MCBSP1_CLKX, ( IEN | OFF_EN | OFF_PD | OFF_IN | M0))	/* abe_mcbsp1_clock */
	mux(CONTROL_PADCONF_ABE_MCBSP1_DR, ( IEN | OFF_EN | OFF_OUT_PTD | M0))		/* abe_mcbsp1_dx */
	mux(CONTROL_PADCONF_ABE_MCBSP1_DX, (OFF_EN | OFF_OUT_PTD | M0));		/* abe_mcbsp1_dx */
	mux(CONTROL_PADCONF_ABE_MCBSP1_FSX, (IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* abe_mcbsp1_fsx */
	mux(CONTROL_PADCONF_ABE_PDM_UL_DATA, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* abe_pdm_ul_data */
	mux(CONTROL_PADCONF_ABE_PDM_DL_DATA, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* abe_pdm_dl_data */
	mux(CONTROL_PADCONF_ABE_PDM_FRAME, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* abe_pdm_frame */
	mux(CONTROL_PADCONF_ABE_PDM_LB_CLK, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* abe_pdm_lb_clk */
	mux(CONTROL_PADCONF_ABE_CLKS, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M0));		/* abe_clks */
	mux(CONTROL_PADCONF_ABE_DMIC_CLK1, (M0));	/* abe_dmic_clk1 */
	mux(CONTROL_PADCONF_ABE_DMIC_DIN1, (IEN | M0));	/* abe_dmic_din1 */
	mux(CONTROL_PADCONF_ABE_DMIC_DIN2, (PTU | IEN | M3));	/* gpio_121 */
	mux(CONTROL_PADCONF_ABE_DMIC_DIN3, (IEN | M0));		/* abe_dmic_din3 */
	mux(CONTROL_PADCONF_UART2_CTS, (PTU | IEN | M0));	/* uart2_cts */
	mux(CONTROL_PADCONF_UART2_RTS, (M0));			/* uart2_rts */
	mux(CONTROL_PADCONF_UART2_RX, (PTU | IEN | M0));	/* uart2_rx */
	mux(CONTROL_PADCONF_UART2_TX, (M0));			/* uart2_tx */
	mux(CONTROL_PADCONF_HDQ_SIO, (M3));	/* gpio_127 */
	mux(CONTROL_PADCONF_I2C1_SCL, (PTU | IEN | M0));	/* i2c1_scl */
	mux(CONTROL_PADCONF_I2C1_SDA, (PTU | IEN | M0));	/* i2c1_sda */
	mux(CONTROL_PADCONF_I2C2_SCL, (PTU | IEN | M0));	/* i2c2_scl */
	mux(CONTROL_PADCONF_I2C2_SDA, (PTU | IEN | M0));	/* i2c2_sda */
	mux(CONTROL_PADCONF_I2C3_SCL, (PTU | IEN | M0));	/* i2c3_scl */
	mux(CONTROL_PADCONF_I2C3_SDA, (PTU | IEN | M0));	/* i2c3_sda */
	mux(CONTROL_PADCONF_I2C4_SCL, (PTU | IEN | M0));	/* i2c4_scl */
	mux(CONTROL_PADCONF_I2C4_SDA, (PTU | IEN | M0));	/* i2c4_sda */
	mux(CONTROL_PADCONF_MCSPI1_CLK, (IEN | OFF_EN | OFF_PD | OFF_IN | M0));		/* mcspi1_clk */
	mux(CONTROL_PADCONF_MCSPI1_SOMI, (IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* mcspi1_somi */
	mux(CONTROL_PADCONF_MCSPI1_SIMO, (IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* mcspi1_simo */
	mux(CONTROL_PADCONF_MCSPI1_CS0, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* mcspi1_cs0 */
	mux(CONTROL_PADCONF_MCSPI1_CS1, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M3));	/* mcspi1_cs1 */
	mux(CONTROL_PADCONF_MCSPI1_CS2, (PTU | OFF_EN | OFF_OUT_PTU | M3));	/* gpio_139 */
	mux(CONTROL_PADCONF_MCSPI1_CS3, (PTU | IEN | M3));	/* gpio_140 */
	mux(CONTROL_PADCONF_UART3_CTS_RCTX, (PTU | IEN | M0));	/* uart3_tx */
	mux(CONTROL_PADCONF_UART3_RTS_SD, (M0));	/* uart3_rts_sd */
	mux(CONTROL_PADCONF_UART3_RX_IRRX, (IEN | M0));	/* uart3_rx */
	mux(CONTROL_PADCONF_UART3_TX_IRTX, (M0));	/* uart3_tx */
	mux(CONTROL_PADCONF_SDMMC5_CLK, (PTU | IEN | OFF_EN | OFF_OUT_PTD | M0));	/* sdmmc5_clk */
	mux(CONTROL_PADCONF_SDMMC5_CMD, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc5_cmd */
	mux(CONTROL_PADCONF_SDMMC5_DAT0, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc5_dat0 */
	mux(CONTROL_PADCONF_SDMMC5_DAT1, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc5_dat1 */
	mux(CONTROL_PADCONF_SDMMC5_DAT2, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc5_dat2 */
	mux(CONTROL_PADCONF_SDMMC5_DAT3, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* sdmmc5_dat3 */
	mux(CONTROL_PADCONF_MCSPI4_CLK, (IEN | OFF_EN | OFF_PD | OFF_IN | M0));		/* mcspi4_clk */
	mux(CONTROL_PADCONF_MCSPI4_SIMO, (IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* mcspi4_simo */
	mux(CONTROL_PADCONF_MCSPI4_SOMI, (IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* mcspi4_somi */
	mux(CONTROL_PADCONF_MCSPI4_CS0, (PTD | IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* mcspi4_cs0 */
	mux(CONTROL_PADCONF_UART4_RX, (IEN | M0));	/* uart4_rx */
	mux(CONTROL_PADCONF_UART4_TX, (M0));		/* uart4_tx */
	mux(CONTROL_PADCONF_USBB2_ULPITLL_CLK, (IEN | M3));	/* gpio_157 */
	mux(CONTROL_PADCONF_USBB2_ULPITLL_STP, (IEN | M5));	/* dispc2_data23 */
	mux(CONTROL_PADCONF_USBB2_ULPITLL_DIR, (IEN | M5));	/* dispc2_data22 */
	mux(CONTROL_PADCONF_USBB2_ULPITLL_NXT, (IEN | M5));	/* dispc2_data21 */
	mux(CONTROL_PADCONF_USBB2_ULPITLL_DAT0, (IEN | M5));	/* dispc2_data20 */
	mux(CONTROL_PADCONF_USBB2_ULPITLL_DAT1, (IEN | M5));	/* dispc2_data19 */
	mux(CONTROL_PADCONF_USBB2_ULPITLL_DAT2, (IEN | M5));	/* dispc2_data18 */
	mux(CONTROL_PADCONF_USBB2_ULPITLL_DAT3, (IEN | M5));	/* dispc2_data15 */
	mux(CONTROL_PADCONF_USBB2_ULPITLL_DAT4, (IEN | M5));	/* dispc2_data14 */
	mux(CONTROL_PADCONF_USBB2_ULPITLL_DAT5, (IEN | M5));	/* dispc2_data13 */
	mux(CONTROL_PADCONF_USBB2_ULPITLL_DAT6, (IEN | M5));	/* dispc2_data12 */
	mux(CONTROL_PADCONF_USBB2_ULPITLL_DAT7, (IEN | M5));	/* dispc2_data11 */
	mux(CONTROL_PADCONF_USBB2_HSIC_DATA, (PTD | OFF_EN | OFF_OUT_PTU | M3));	/* gpio_169 */
	mux(CONTROL_PADCONF_USBB2_HSIC_STROBE, (PTD | OFF_EN | OFF_OUT_PTU | M3));	/* gpio_170 */
	mux(CONTROL_PADCONF_UNIPRO_TX0, (IEN | M3));	/* gpio_171 */
	mux(CONTROL_PADCONF_UNIPRO_TY0, (OFF_EN | OFF_PD | OFF_IN | M1));	/* kpd_col1 */
	mux(CONTROL_PADCONF_UNIPRO_TX1, (OFF_EN | OFF_PD | OFF_IN | M1));	/* kpd_col2 */
	mux(CONTROL_PADCONF_UNIPRO_TY1, (OFF_EN | OFF_PD | OFF_IN | M1));	/* kpd_col3 */
	mux(CONTROL_PADCONF_UNIPRO_TX2, (PTU | IEN | M3));	/* gpio_0 */
	mux(CONTROL_PADCONF_UNIPRO_TY2, (PTU | IEN | M3));	/* gpio_1 */
	mux(CONTROL_PADCONF_UNIPRO_RX0, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* kpd_row0 */
	mux(CONTROL_PADCONF_UNIPRO_RY0, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* kpd_row1 */
	mux(CONTROL_PADCONF_UNIPRO_RX1, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* kpd_row2 */
	mux(CONTROL_PADCONF_UNIPRO_RY1, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* kpd_row3 */
	mux(CONTROL_PADCONF_UNIPRO_RX2, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* kpd_row4 */
	mux(CONTROL_PADCONF_UNIPRO_RY2, (PTU | IEN | OFF_EN | OFF_PD | OFF_IN | M1));	/* kpd_row5 */
	mux(CONTROL_PADCONF_USBA0_OTG_CE, (PTD | OFF_EN | OFF_PD | OFF_OUT_PTD | M0));	/* usba0_otg_ce */
	mux(CONTROL_PADCONF_USBA0_OTG_DP, (IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* usba0_otg_dp */
	mux(CONTROL_PADCONF_USBA0_OTG_DM, (IEN | OFF_EN | OFF_PD | OFF_IN | M0));	/* usba0_otg_dm */
	mux(CONTROL_PADCONF_FREF_CLK1_OUT, (M0));	/* fref_clk1_out */
	mux(CONTROL_PADCONF_FREF_CLK2_OUT, (PTU | IEN | M3));	/* gpio_182 */
	mux(CONTROL_PADCONF_SYS_NIRQ1, (PTU | IEN | M0));	/* sys_nirq1 */
	mux(CONTROL_PADCONF_SYS_NIRQ2, (PTU | IEN | M0));	/* sys_nirq2 */
	mux(CONTROL_PADCONF_SYS_BOOT0, (PTU | IEN | M3));	/* gpio_184 */
	mux(CONTROL_PADCONF_SYS_BOOT1, (M3));			/* gpio_185 */
	mux(CONTROL_PADCONF_SYS_BOOT2, (PTD | IEN | M3));	/* gpio_186 */
	mux(CONTROL_PADCONF_SYS_BOOT3, (M3));			/* gpio_187 */
	mux(CONTROL_PADCONF_SYS_BOOT4, (M3));			/* gpio_188 */
	mux(CONTROL_PADCONF_SYS_BOOT5, (PTD | IEN | M3));	/* gpio_189 */
	mux(CONTROL_PADCONF_DPM_EMU0, (IEN | M0));	/* dpm_emu0 */
	mux(CONTROL_PADCONF_DPM_EMU1, (IEN | M0));	/* dpm_emu1 */
	mux(CONTROL_PADCONF_DPM_EMU2, (IEN | M0));	/* dpm_emu2 */
	mux(CONTROL_PADCONF_DPM_EMU3, (IEN | M5));	/* dispc2_data10 */
	mux(CONTROL_PADCONF_DPM_EMU4, (IEN | M5));	/* dispc2_data9 */
	mux(CONTROL_PADCONF_DPM_EMU5, (IEN | M5));	/* dispc2_data16 */
	mux(CONTROL_PADCONF_DPM_EMU6, (IEN | M5));	/* dispc2_data17 */
	mux(CONTROL_PADCONF_DPM_EMU7, (IEN | M5));	/* dispc2_hsync */
	mux(CONTROL_PADCONF_DPM_EMU8, (IEN | M5));	/* dispc2_pclk */
	mux(CONTROL_PADCONF_DPM_EMU9, (IEN | M5));	/* dispc2_vsync */
	mux(CONTROL_PADCONF_DPM_EMU10, (IEN | M5));	/* dispc2_de */
	mux(CONTROL_PADCONF_DPM_EMU11, (IEN | M5));	/* dispc2_data8 */
	mux(CONTROL_PADCONF_DPM_EMU12, (IEN | M5));	/* dispc2_data7 */
	mux(CONTROL_PADCONF_DPM_EMU13, (IEN | M5));	/* dispc2_data6 */
	mux(CONTROL_PADCONF_DPM_EMU14, (IEN | M5));	/* dispc2_data5 */
	mux(CONTROL_PADCONF_DPM_EMU15, (IEN | M5));	/* dispc2_data4 */
	mux(CONTROL_PADCONF_DPM_EMU16, (M3));		/* gpio_27 */
	mux(CONTROL_PADCONF_DPM_EMU17, (IEN | M5));	/* dispc2_data2 */
	mux(CONTROL_PADCONF_DPM_EMU18, (IEN | M5));	/* dispc2_data1 */
	mux(CONTROL_PADCONF_DPM_EMU19, (IEN | M5));	/* dispc2_data0 */
	mux(CONTROL_WKUP_PAD0_SIM_IO, (IEN | M0));	/* sim_io */
	mux(CONTROL_WKUP_PAD1_SIM_CLK, (M0));		/* sim_clk */
	mux(CONTROL_WKUP_PAD0_SIM_RESET, (M0));		/* sim_reset */
	mux(CONTROL_WKUP_PAD1_SIM_CD, (PTU | IEN | M0));/* sim_cd */
	mux(CONTROL_WKUP_PAD0_SIM_PWRCTRL, (M0));	/* sim_pwrctrl */
	mux(CONTROL_WKUP_PAD1_SR_SCL, (PTU | IEN | M0));/* sr_scl */
	mux(CONTROL_WKUP_PAD0_SR_SDA, (PTU | IEN | M0));/* sr_sda */
	mux(CONTROL_WKUP_PAD1_FREF_XTAL_IN, (M0));	/* # */
	mux(CONTROL_WKUP_PAD0_FREF_SLICER_IN, (M0));	/* fref_slicer_in */
	mux(CONTROL_WKUP_PAD1_FREF_CLK_IOREQ, (M0));	/* fref_clk_ioreq */
	mux(CONTROL_WKUP_PAD0_FREF_CLK0_OUT, (M2));	/* sys_drm_msecure */
	mux(CONTROL_WKUP_PAD1_FREF_CLK3_REQ, (M3));	/* gpio_wk30 */
	mux(CONTROL_WKUP_PAD0_FREF_CLK3_OUT, (M0));	/* fref_clk3_out */
	mux(CONTROL_WKUP_PAD1_FREF_CLK4_REQ, (M3));	/* gpio_wk7 */
	mux(CONTROL_WKUP_PAD0_FREF_CLK4_OUT, (M3));	/* gpio_wk8 */
	mux(CONTROL_WKUP_PAD1_SYS_32K, (IEN | M0));	/* sys_32k */
	mux(CONTROL_WKUP_PAD0_SYS_NRESPWRON, (M0));	/* sys_nrespwron */
	mux(CONTROL_WKUP_PAD1_SYS_NRESWARM, (M0));	/* sys_nreswarm */
	mux(CONTROL_WKUP_PAD0_SYS_PWR_REQ, (PTU | M0));	/* sys_pwr_req */
	mux(CONTROL_WKUP_PAD1_SYS_PWRON_RESET, (M3));	/* gpio_wk29 */
	mux(CONTROL_WKUP_PAD0_SYS_BOOT6, (IEN | M3));	/* gpio_wk9 */
	mux(CONTROL_WKUP_PAD1_SYS_BOOT7, (IEN | M3));	/* gpio_wk10 */
}

static struct ddr_regs elpida2G_400_mhz_1cs = {
	.config_init	= 0x80800eb2,
	.config		= 0x80801ab2,
	.tim1		= 0x10eb0662,
	.tim2		= 0x20370dd2,
	.tim3		= 0x00b1c33f,
	.phy_ctrl_1	= 0x849ff408,
	.ref_ctrl	= 0x00000618,
	.zq_config	= 0xd00b3215,
	.mr1		= 0x83,
	.mr2		= 0x4
};

static struct ddr_regs elpida2G_400_mhz_2cs = {
	/* tRRD changed from 10ns to 12.5ns because of the tFAW requirement*/
	.config_init	= 0x80000eb9,
	.config		= 0x80001ab9,
	.tim1		= 0x10eb0662,
	.tim2		= 0x20370dd2,
	.tim3		= 0x00b1c33f,
	.phy_ctrl_1	= 0x849ff408,
	.ref_ctrl	= 0x00000618,
	.zq_config	= 0xd00b3215,
	.mr1		= 0x83,
	.mr2		= 0x4
};

static struct ddr_regs elpida4G_466_mhz_1cs = {
	.config_init	= 0x80800eb2,
	.config		= 0x80801eb2,
	.tim1		= 0x130f376b,
	.tim2		= 0x3041105a,
	.tim3		= 0x00f543cf,
	.phy_ctrl_1	= 0x449ff37b,
	.ref_ctrl	= 0x0000071b,
	.zq_config	= 0x500b3215,
	.mr1		= 0x83,
	.mr2		= 0x5
};

int
is_panda_es_rev_b3(void)
{
	int ret = 0;
	uint32_t rev = get_omap_rev();
	if (rev >= OMAP4460_ES1_0 &&
	    rev <= OMAP4460_ES1_1) {
		writew((IEN | M3), CONTROL_PADCONF_UNIPRO_TX0);
		ret = gpio_get_value(171);
	}
	return (ret);
}

void
sdram_init(void)
{
	uint32_t rev;
	const struct ddr_regs *ddr_regs = 0;

	/* 1GB, 128B interleaved */
	writel(0x80640300, DMM_BASE + DMM_LISA_MAP_0);
	writel(0x00000000, DMM_BASE + DMM_LISA_MAP_2);
	writel(0xff020100, DMM_BASE + DMM_LISA_MAP_3);

	rev = get_omap_rev();
	switch (rev) {
	case OMAP4430_ES2_2:
	case OMAP4430_ES2_3:
		ddr_regs = &elpida2G_400_mhz_2cs;
		break;
	case OMAP4460_ES1_0:
	case OMAP4460_ES1_1:
		writel(0x80640300, MA_BASE + DMM_LISA_MAP_0);
		elpida2G_400_mhz_2cs.phy_ctrl_1	= 0x449ff408;
		if (is_panda_es_rev_b3())
			ddr_regs = &elpida2G_400_mhz_1cs;
		else
			ddr_regs = &elpida2G_400_mhz_2cs;
		break;
	case OMAP4470_ES1_0:
		writel(0x80640300, MA_BASE + DMM_LISA_MAP_3);
		ddr_regs = &elpida4G_466_mhz_1cs;
		break;
	case REV_INVALID:
	default:
		printf("unsupported OMAP4 revision %d", rev);
	}

	ddr_init(ddr_regs, ddr_regs);

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
}

void
storage_init(void)
{
	mmc_init(0);
	stor.size = (unsigned long) mmc_size();
	stor.read = mmc_bread;
	stor.write = mmc_write;
}

struct storage *
get_storage(void)
{
	return &stor;
}
