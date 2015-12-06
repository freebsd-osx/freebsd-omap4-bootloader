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

#ifndef _OMAP4_PADCONF_H_
#define _OMAP4_PADCONF_H_

#define CONTROL_PADCONF_CORE_REVISION		0x4a100000
#define CONTROL_PADCONF_CORE_HWINFO		0x4a100004
#define CONTROL_PADCONF_CORE_SYSCONFIG		0x4a100010
#define CONTROL_PADCONF_GPMC_AD0		0x4a100040
#define CONTROL_PADCONF_GPMC_AD1		0x4a100042
#define CONTROL_PADCONF_GPMC_AD2		0x4a100044
#define CONTROL_PADCONF_GPMC_AD3		0x4a100046
#define CONTROL_PADCONF_GPMC_AD4		0x4a100048
#define CONTROL_PADCONF_GPMC_AD5		0x4a10004a
#define CONTROL_PADCONF_GPMC_AD6		0x4a10004c
#define CONTROL_PADCONF_GPMC_AD7		0x4a10004e
#define CONTROL_PADCONF_GPMC_AD8		0x4a100050
#define CONTROL_PADCONF_GPMC_AD9		0x4a100052
#define CONTROL_PADCONF_GPMC_AD10		0x4a100054
#define CONTROL_PADCONF_GPMC_AD11		0x4a100056
#define CONTROL_PADCONF_GPMC_AD12		0x4a100058
#define CONTROL_PADCONF_GPMC_AD13		0x4a10005a
#define CONTROL_PADCONF_GPMC_AD14		0x4a10005c
#define CONTROL_PADCONF_GPMC_AD15		0x4a10005e
#define CONTROL_PADCONF_GPMC_A16		0x4a100060
#define CONTROL_PADCONF_GPMC_A17		0x4a100062
#define CONTROL_PADCONF_GPMC_A18		0x4a100064
#define CONTROL_PADCONF_GPMC_A19		0x4a100066
#define CONTROL_PADCONF_GPMC_A20		0x4a100068
#define CONTROL_PADCONF_GPMC_A21		0x4a10006a
#define CONTROL_PADCONF_GPMC_A22		0x4a10006c
#define CONTROL_PADCONF_GPMC_A23		0x4a10006e
#define CONTROL_PADCONF_GPMC_A24		0x4a100070
#define CONTROL_PADCONF_GPMC_A25		0x4a100072
#define CONTROL_PADCONF_GPMC_NCS0		0x4a100074
#define CONTROL_PADCONF_GPMC_NCS1		0x4a100076
#define CONTROL_PADCONF_GPMC_NCS2		0x4a100078
#define CONTROL_PADCONF_GPMC_NCS3		0x4a10007a
#define CONTROL_PADCONF_GPMC_NWP		0x4a10007c
#define CONTROL_PADCONF_GPMC_CLK		0x4a10007e
#define CONTROL_PADCONF_GPMC_NADV_ALE		0x4a100080
#define CONTROL_PADCONF_GPMC_NOE		0x4a100082
#define CONTROL_PADCONF_GPMC_NWE		0x4a100084
#define CONTROL_PADCONF_GPMC_NBE0_CLE		0x4a100086
#define CONTROL_PADCONF_GPMC_NBE1		0x4a100088
#define CONTROL_PADCONF_GPMC_WAIT0		0x4a10008a
#define CONTROL_PADCONF_GPMC_WAIT1		0x4a10008c
#define CONTROL_PADCONF_C2C_DATA11		0x4a10008e
#define CONTROL_PADCONF_C2C_DATA12		0x4a100090
#define CONTROL_PADCONF_C2C_DATA13		0x4a100092
#define CONTROL_PADCONF_C2C_DATA14		0x4a100094
#define CONTROL_PADCONF_C2C_DATA15		0x4a100096
#define CONTROL_PADCONF_HDMI_HPD		0x4a100098
#define CONTROL_PADCONF_HDMI_CEC		0x4a10009a
#define CONTROL_PADCONF_HDMI_DDC_SCL		0x4a10009c
#define CONTROL_PADCONF_HDMI_DDC_SDA		0x4a10009e
#define CONTROL_PADCONF_CSI21_DX0		0x4a1000a0
#define CONTROL_PADCONF_CSI21_DY0		0x4a1000a2
#define CONTROL_PADCONF_CSI21_DX1		0x4a1000a4
#define CONTROL_PADCONF_CSI21_DY1		0x4a1000a6
#define CONTROL_PADCONF_CSI21_DX2		0x4a1000a8
#define CONTROL_PADCONF_CSI21_DY2		0x4a1000aa
#define CONTROL_PADCONF_CSI21_DX3		0x4a1000ac
#define CONTROL_PADCONF_CSI21_DY3		0x4a1000ae
#define CONTROL_PADCONF_CSI21_DX4		0x4a1000b0
#define CONTROL_PADCONF_CSI21_DY4		0x4a1000b2
#define CONTROL_PADCONF_CSI22_DX0		0x4a1000b4
#define CONTROL_PADCONF_CSI22_DY0		0x4a1000b6
#define CONTROL_PADCONF_CSI22_DX1		0x4a1000b8
#define CONTROL_PADCONF_CSI22_DY1		0x4a1000ba
#define CONTROL_PADCONF_CAM_SHUTTER		0x4a1000bc
#define CONTROL_PADCONF_CAM_STROBE		0x4a1000be
#define CONTROL_PADCONF_CAM_GLOBALRESET		0x4a1000c0
#define CONTROL_PADCONF_USBB1_ULPITLL_CLK	0x4a1000c2
#define CONTROL_PADCONF_USBB1_ULPITLL_STP	0x4a1000c4
#define CONTROL_PADCONF_USBB1_ULPITLL_DIR	0x4a1000c6
#define CONTROL_PADCONF_USBB1_ULPITLL_NXT	0x4a1000c8
#define CONTROL_PADCONF_USBB1_ULPITLL_DAT0	0x4a1000ca
#define CONTROL_PADCONF_USBB1_ULPITLL_DAT1	0x4a1000cc
#define CONTROL_PADCONF_USBB1_ULPITLL_DAT2	0x4a1000ce
#define CONTROL_PADCONF_USBB1_ULPITLL_DAT3	0x4a1000d0
#define CONTROL_PADCONF_USBB1_ULPITLL_DAT4	0x4a1000d2
#define CONTROL_PADCONF_USBB1_ULPITLL_DAT5	0x4a1000d4
#define CONTROL_PADCONF_USBB1_ULPITLL_DAT6	0x4a1000d6
#define CONTROL_PADCONF_USBB1_ULPITLL_DAT7	0x4a1000d8
#define CONTROL_PADCONF_USBB1_HSIC_DATA		0x4a1000da
#define CONTROL_PADCONF_USBB1_HSIC_STROBE	0x4a1000dc
#define CONTROL_PADCONF_USBC1_ICUSB_DP		0x4a1000de
#define CONTROL_PADCONF_USBC1_ICUSB_DM		0x4a1000e0
#define CONTROL_PADCONF_SDMMC1_CLK		0x4a1000e2
#define CONTROL_PADCONF_SDMMC1_CMD		0x4a1000e4
#define CONTROL_PADCONF_SDMMC1_DAT0		0x4a1000e6
#define CONTROL_PADCONF_SDMMC1_DAT1		0x4a1000e8
#define CONTROL_PADCONF_SDMMC1_DAT2		0x4a1000ea
#define CONTROL_PADCONF_SDMMC1_DAT3		0x4a1000ec
#define CONTROL_PADCONF_SDMMC1_DAT4		0x4a1000ee
#define CONTROL_PADCONF_SDMMC1_DAT5		0x4a1000f0
#define CONTROL_PADCONF_SDMMC1_DAT6		0x4a1000f2
#define CONTROL_PADCONF_SDMMC1_DAT7		0x4a1000f4
#define CONTROL_PADCONF_ABE_MCBSP2_CLKX		0x4a1000f6
#define CONTROL_PADCONF_ABE_MCBSP2_DR		0x4a1000f8
#define CONTROL_PADCONF_ABE_MCBSP2_DX		0x4a1000fa
#define CONTROL_PADCONF_ABE_MCBSP2_FSX		0x4a1000fc
#define CONTROL_PADCONF_ABE_MCBSP1_CLKX		0x4a1000fe
#define CONTROL_PADCONF_ABE_MCBSP1_DR		0x4a100100
#define CONTROL_PADCONF_ABE_MCBSP1_DX		0x4a100102
#define CONTROL_PADCONF_ABE_MCBSP1_FSX		0x4a100104
#define CONTROL_PADCONF_ABE_PDM_UL_DATA		0x4a100106
#define CONTROL_PADCONF_ABE_PDM_DL_DATA		0x4a100108
#define CONTROL_PADCONF_ABE_PDM_FRAME		0x4a10010a
#define CONTROL_PADCONF_ABE_PDM_LB_CLK		0x4a10010c
#define CONTROL_PADCONF_ABE_CLKS		0x4a10010e
#define CONTROL_PADCONF_ABE_DMIC_CLK1		0x4a100110
#define CONTROL_PADCONF_ABE_DMIC_DIN1		0x4a100112
#define CONTROL_PADCONF_ABE_DMIC_DIN2		0x4a100114
#define CONTROL_PADCONF_ABE_DMIC_DIN3		0x4a100116
#define CONTROL_PADCONF_UART2_CTS		0x4a100118
#define CONTROL_PADCONF_UART2_RTS		0x4a10011a
#define CONTROL_PADCONF_UART2_RX		0x4a10011c
#define CONTROL_PADCONF_UART2_TX		0x4a10011e
#define CONTROL_PADCONF_HDQ_SIO			0x4a100120
#define CONTROL_PADCONF_I2C1_SCL		0x4a100122
#define CONTROL_PADCONF_I2C1_SDA		0x4a100124
#define CONTROL_PADCONF_I2C2_SCL		0x4a100126
#define CONTROL_PADCONF_I2C2_SDA		0x4a100128
#define CONTROL_PADCONF_I2C3_SCL		0x4a10012a
#define CONTROL_PADCONF_I2C3_SDA		0x4a10012c
#define CONTROL_PADCONF_I2C4_SCL		0x4a10012e
#define CONTROL_PADCONF_I2C4_SDA		0x4a100130
#define CONTROL_PADCONF_MCSPI1_CLK		0x4a100132
#define CONTROL_PADCONF_MCSPI1_SOMI		0x4a100134
#define CONTROL_PADCONF_MCSPI1_SIMO		0x4a100136
#define CONTROL_PADCONF_MCSPI1_CS0		0x4a100138
#define CONTROL_PADCONF_MCSPI1_CS1		0x4a10013a
#define CONTROL_PADCONF_MCSPI1_CS2		0x4a10013c
#define CONTROL_PADCONF_MCSPI1_CS3		0x4a10013e
#define CONTROL_PADCONF_UART3_CTS_RCTX		0x4a100140
#define CONTROL_PADCONF_UART3_RTS_SD		0x4a100142
#define CONTROL_PADCONF_UART3_RX_IRRX		0x4a100144
#define CONTROL_PADCONF_UART3_TX_IRTX		0x4a100146
#define CONTROL_PADCONF_SDMMC5_CLK		0x4a100148
#define CONTROL_PADCONF_SDMMC5_CMD		0x4a10014a
#define CONTROL_PADCONF_SDMMC5_DAT0		0x4a10014c
#define CONTROL_PADCONF_SDMMC5_DAT1		0x4a10014e
#define CONTROL_PADCONF_SDMMC5_DAT2		0x4a100150
#define CONTROL_PADCONF_SDMMC5_DAT3		0x4a100152
#define CONTROL_PADCONF_MCSPI4_CLK		0x4a100154
#define CONTROL_PADCONF_MCSPI4_SIMO		0x4a100156
#define CONTROL_PADCONF_MCSPI4_SOMI		0x4a100158
#define CONTROL_PADCONF_MCSPI4_CS0		0x4a10015a
#define CONTROL_PADCONF_UART4_RX		0x4a10015c
#define CONTROL_PADCONF_UART4_TX		0x4a10015e
#define CONTROL_PADCONF_USBB2_ULPITLL_CLK	0x4a100160
#define CONTROL_PADCONF_USBB2_ULPITLL_STP	0x4a100162
#define CONTROL_PADCONF_USBB2_ULPITLL_DIR	0x4a100164
#define CONTROL_PADCONF_USBB2_ULPITLL_NXT	0x4a100166
#define CONTROL_PADCONF_USBB2_ULPITLL_DAT0	0x4a100168
#define CONTROL_PADCONF_USBB2_ULPITLL_DAT1	0x4a10016a
#define CONTROL_PADCONF_USBB2_ULPITLL_DAT2	0x4a10016c
#define CONTROL_PADCONF_USBB2_ULPITLL_DAT3	0x4a10016e
#define CONTROL_PADCONF_USBB2_ULPITLL_DAT4	0x4a100170
#define CONTROL_PADCONF_USBB2_ULPITLL_DAT5	0x4a100172
#define CONTROL_PADCONF_USBB2_ULPITLL_DAT6	0x4a100174
#define CONTROL_PADCONF_USBB2_ULPITLL_DAT7	0x4a100176
#define CONTROL_PADCONF_USBB2_HSIC_DATA		0x4a100178
#define CONTROL_PADCONF_USBB2_HSIC_STROBE	0x4a10017a
#define CONTROL_PADCONF_UNIPRO_TX0		0x4a10017c
#define CONTROL_PADCONF_UNIPRO_TY0		0x4a10017e
#define CONTROL_PADCONF_UNIPRO_TX1		0x4a100180
#define CONTROL_PADCONF_UNIPRO_TY1		0x4a100182
#define CONTROL_PADCONF_UNIPRO_TX2		0x4a100184
#define CONTROL_PADCONF_UNIPRO_TY2		0x4a100186
#define CONTROL_PADCONF_UNIPRO_RX0		0x4a100188
#define CONTROL_PADCONF_UNIPRO_RY0		0x4a10018a
#define CONTROL_PADCONF_UNIPRO_RX1		0x4a10018c
#define CONTROL_PADCONF_UNIPRO_RY1		0x4a10018e
#define CONTROL_PADCONF_UNIPRO_RX2		0x4a100190
#define CONTROL_PADCONF_UNIPRO_RY2		0x4a100192
#define CONTROL_PADCONF_USBA0_OTG_CE		0x4a100194
#define CONTROL_PADCONF_USBA0_OTG_DP		0x4a100196
#define CONTROL_PADCONF_USBA0_OTG_DM		0x4a100198
#define CONTROL_PADCONF_FREF_CLK1_OUT		0x4a10019a
#define CONTROL_PADCONF_FREF_CLK2_OUT		0x4a10019c
#define CONTROL_PADCONF_SYS_NIRQ1		0x4a10019e
#define CONTROL_PADCONF_SYS_NIRQ2		0x4a1001a0
#define CONTROL_PADCONF_SYS_BOOT0		0x4a1001a2
#define CONTROL_PADCONF_SYS_BOOT1		0x4a1001a4
#define CONTROL_PADCONF_SYS_BOOT2		0x4a1001a6
#define CONTROL_PADCONF_SYS_BOOT3		0x4a1001a8
#define CONTROL_PADCONF_SYS_BOOT4		0x4a1001aa
#define CONTROL_PADCONF_SYS_BOOT5		0x4a1001ac
#define CONTROL_PADCONF_DPM_EMU0		0x4a1001ae
#define CONTROL_PADCONF_DPM_EMU1		0x4a1001b0
#define CONTROL_PADCONF_DPM_EMU2		0x4a1001b2
#define CONTROL_PADCONF_DPM_EMU3		0x4a1001b4
#define CONTROL_PADCONF_DPM_EMU4		0x4a1001b6
#define CONTROL_PADCONF_DPM_EMU5		0x4a1001b8
#define CONTROL_PADCONF_DPM_EMU6		0x4a1001ba
#define CONTROL_PADCONF_DPM_EMU7		0x4a1001bc
#define CONTROL_PADCONF_DPM_EMU8		0x4a1001be
#define CONTROL_PADCONF_DPM_EMU9		0x4a1001c0
#define CONTROL_PADCONF_DPM_EMU10		0x4a1001c2
#define CONTROL_PADCONF_DPM_EMU11		0x4a1001c4
#define CONTROL_PADCONF_DPM_EMU12		0x4a1001c6
#define CONTROL_PADCONF_DPM_EMU13		0x4a1001c8
#define CONTROL_PADCONF_DPM_EMU14		0x4a1001ca
#define CONTROL_PADCONF_DPM_EMU15		0x4a1001cc
#define CONTROL_PADCONF_DPM_EMU16		0x4a1001ce
#define CONTROL_PADCONF_DPM_EMU17		0x4a1001d0
#define CONTROL_PADCONF_DPM_EMU18		0x4a1001d2
#define CONTROL_PADCONF_DPM_EMU19		0x4a1001d4
#define CONTROL_PADCONF_WAKEUPEVENT_1		0x4a1001dc
#define CONTROL_PADCONF_WAKEUPEVENT_2		0x4a1001e0
#define CONTROL_PADCONF_WAKEUPEVENT_3		0x4a1001e4
#define CONTROL_PADCONF_WAKEUPEVENT_4		0x4a1001e8
#define CONTROL_PADCONF_WAKEUPEVENT_5		0x4a1001ec
#define CONTROL_PADCONF_WAKEUPEVENT_6		0x4a1001f0

#define CONTROL_PADCONF_GLOBAL			0x4a1005a2
#define CONTROL_PADCONF_MODE			0x4a1005a4
#define CONTROL_SMART1IO_PADCONF_0		0x4a1005a8
#define CONTROL_SMART1IO_PADCONF_1		0x4a1005ac
#define CONTROL_SMART2IO_PADCONF_0		0x4a1005b0
#define CONTROL_SMART2IO_PADCONF_1		0x4a1005b4
#define CONTROL_SMART3IO_PADCONF_0		0x4a1005b8
#define CONTROL_SMART3IO_PADCONF_1		0x4a1005bc
#define CONTROL_SMART3IO_PADCONF_2		0x4a1005c0
#define CONTROL_USBB_HSIC			0x4a1005c4
#define CONTROL_SLIMBUS				0x4a1005c8
#define CONTROL_PBIASLITE			0x4a100600
#define CONTROL_I2C_0				0x4a100604
#define CONTROL_CAMERA_RX			0x4a100608
#define CONTROL_AVDAC				0x4a10060c
#define CONTROL_HDMI_TX_PHY			0x4a100610
#define CONTROL_MMC2				0x4a100614
#define CONTROL_DSIPHY				0x4a100618
#define CONTROL_MCBSPLP				0x4a10061c
#define CONTROL_USB2PHYCORE			0x4a100620
#define CONTROL_I2C_1				0x4a100624
#define CONTROL_MMC1				0x4a100628
#define CONTROL_HSI				0x4a10062c
#define CONTROL_USB				0x4a100630
#define CONTROL_HDQ				0x4a100634
#define CONTROL_PADCONF_WKUP_REVISION		0x4a31e000
#define CONTROL_PADCONF_WKUP_HWINFO		0x4a31e004
#define CONTROL_PADCONF_WKUP_SYSCONFIG		0x4a31e010
#define CONTROL_WKUP_PAD0_SIM_IO		0x4a31e040
#define CONTROL_WKUP_PAD1_SIM_CLK		0x4a31e042
#define CONTROL_WKUP_PAD0_SIM_RESET		0x4a31e044
#define CONTROL_WKUP_PAD1_SIM_CD		0x4a31e046
#define CONTROL_WKUP_PAD0_SIM_PWRCTRL		0x4a31e048
#define CONTROL_WKUP_PAD1_SR_SCL		0x4a31e04a
#define CONTROL_WKUP_PAD0_SR_SDA		0x4a31e04c
#define CONTROL_WKUP_PAD1_FREF_XTAL_IN		0x4a31e04e
#define CONTROL_WKUP_PAD0_FREF_SLICER_IN	0x4a31e050
#define CONTROL_WKUP_PAD1_FREF_CLK_IOREQ	0x4a31e052
#define CONTROL_WKUP_PAD0_FREF_CLK0_OUT		0x4a31e054
#define CONTROL_WKUP_PAD1_FREF_CLK3_REQ		0x4a31e056
#define CONTROL_WKUP_PAD0_FREF_CLK3_OUT		0x4a31e058
#define CONTROL_WKUP_PAD1_FREF_CLK4_REQ		0x4a31e05a
#define CONTROL_WKUP_PAD0_FREF_CLK4_OUT		0x4a31e05c
#define CONTROL_WKUP_PAD1_SYS_32K		0x4a31e05e
#define CONTROL_WKUP_PAD0_SYS_NRESPWRON		0x4a31e060
#define CONTROL_WKUP_PAD1_SYS_NRESWARM		0x4a31e062
#define CONTROL_WKUP_PAD0_SYS_PWR_REQ		0x4a31e064
#define CONTROL_WKUP_PAD1_SYS_PWRON_RESET	0x4a31e066
#define CONTROL_WKUP_PAD0_SYS_BOOT6		0x4a31e068
#define CONTROL_WKUP_PAD1_SYS_BOOT7		0x4a31e06a
#define CONTROL_WKUP_PAD0_JTAG_NTRST		0x4a31e06c
#define CONTROL_WKUP_PAD1_JTAG_TCK		0x4a31e06d
#define CONTROL_WKUP_PAD0_JTAG_RTCK		0x4a31e070
#define CONTROL_WKUP_PAD1_JTAG_TMS_TMSC		0x4a31e072
#define CONTROL_WKUP_PAD0_JTAG_TDI		0x4a31e074
#define CONTROL_WKUP_PAD1_JTAG_TDO		0x4a31e076
#define CONTROL_PADCONF_WAKEUPEVENT_0		0x4a10007c
#define CONTROL_SMART1NOPMIO_PADCONF_0		0x4a31e5a0
#define CONTROL_SMART1NOPMIO_PADCONF_1		0x4a31e5a4
#define CONTROL_XTAL_OSCILLATOR			0x4a31e5ac
#define CONTROL_CONTROL_I2C_2			0x4a31e604
#define CONTROL_CONTROL_JTAG			0x4a31e608
#define CONTROL_CONTROL_SYS			0x4a31e60c
#define CONTROL_WKUP_CONTROL_SPARE_RW		0x4a31e614
#define CONTROL_WKUP_CONTROL_SPARE_R		0x4a31e618
#define CONTROL_WKUP_CONTROL_SPARE_R_C0		0x4a31e61c

#endif /* !_OMAP4_PADCONF_H_ */
